#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <features.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>		/* htons */
#include <unistd.h>
#include <errno.h>

#include <inttypes.h>

#include <libcalmmedia/mininl.h>
#include <linux/calm.h>

#include <msg.h>
#include <calmfast.h>

#define VERSION		"1.0"

#define ETH_P_FAST	0x1111
#define ETH_PROTOCOL	ETH_P_FAST

#define	SA_NWREF	0
#define MINNWREF	1
#define MAXNWREF	251

#define HASHBITS	6
#define	HASHSIZE	(1 << HASHBITS)

typedef unsigned long	sid_t;

typedef struct cid {
    sid_t		sid;
    int			nwref;
    CF_server		*server;
    struct cid		*next;
    struct cid		*prev;
    struct cid		*nexts;
    struct cid		*prevs;
    char		url[64];
    int			repeat;
    int			ticks;
    unsigned char	*sadata;
    int			sasize;
} cid_t;


static unsigned char	broadcastmac[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
static unsigned char	fastprotocol[2] = { 0x11, 0x11 };
static unsigned char	mymac[6] = { 0 };

static cid_t	*bynwref[256] = { 0 };
static cid_t	*sidhash[HASHSIZE] = { 0 };
static cid_t	*usednwref = 0;
static cid_t	*freenwref = 0;
static cid_t	*freenwreflast = 0;

static int FastSAdecode(unsigned char *mac, unsigned char *msg , int mlen);
static void FastReceive(int tnwref, int snwref, unsigned char *mac, unsigned char *data, size_t size);
static void incomingFastSA(int sid, unsigned char *mac, int nwref, unsigned char *data, size_t size);

static void initNwRef();
static void createNwRef(CF_server *server);
static void destroyNwRef(cid_t *nwref);
static void setNwRefSid(cid_t *nwref, sid_t sid);

static int		verbose = 0;
static int		mustdaemonize = 1;

static void ParseOptions(int argc, char *argv[])
{
    int c;
    extern char *optarg;
    extern int optind, optopt;
    while ((c = getopt(argc, argv, "vV")) != -1) {
        switch(c) {
        case 'v':
	    verbose = 1;
	    mustdaemonize = 0;
            break;
        case 'V':
	    printf("SPITS/FREILOT calmd version %s\n", VERSION);
	    exit(0);
            break;
        case '?':
            fprintf(stderr, "Unrecognized option: -%c\n", optopt);
	    exit(1);
        }
    }
}

static void daemonize(void)
{
    pid_t pid, sid;

    /* already a daemon */
    if ( getppid() == 1 ) return;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(1);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        exit(0);
    }

    /* At this point we are executing as the child process */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        exit(1);
    }

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        exit(1);
    }

    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/dev/null", "w", stderr);
}

/*
 * Create a hash value out of a service-id.
 */
static int sidHash(sid_t sid)
{
    int cnt;
    int	result = 0;

    for (cnt = 0; cnt < sizeof(sid_t)*8; cnt += HASHBITS) {
	result ^= sid & ((1 << HASHBITS) -1);
	sid >>= HASHBITS;
    }

    return result;
}

/*
 * Destroy all data structures related to nwref, and initialise it cleanly.
 */
static void destroyNwRef(cid_t *nwref)
{
    if (nwref == NULL) {
	return;
    }

    /* close the incoming connection if available */
    if (nwref->server != NULL) {
	cf_dispose(nwref->server);
	nwref->server = NULL;
    }

    /* take off the used list */
    if (nwref->next != NULL) {
	nwref->next->prev = nwref->prev;
    }
    if (nwref->prev != NULL) {
	nwref->prev->next = nwref->next;
    } else {
	usednwref = nwref->next;	/* first on the list, update the list head */
    }

    /* insert at the end of the free list */
    if (freenwreflast != NULL) {
	freenwreflast->next = nwref;
    } else {
	freenwref = nwref;	/* last = 0, so the list must be empty */
    }
    nwref->prev = freenwreflast;
    freenwreflast = nwref;

    /* clear the nwref table */
    bynwref[nwref->nwref] = NULL;

    setNwRefSid(nwref, 0);
}

/*
 * Initialise the incoming nwref switch table.
 */
static void initNwRef()
{
    int	cnt;
    
    for (cnt = 1; cnt <= MAXNWREF; cnt++) {
	cid_t	*nwref = calloc(1, sizeof(cid_t));
	if (nwref == NULL) {
	    perror("calloc");
	    exit(1);
	}
	nwref->nwref = cnt;
	destroyNwRef(nwref);
    }
}

/*
 * Search the nwref switch table for a free entry.
 * If a free entry is found the server is connected to it, if not,
 * the server is disposed.
 */
static void createNwRef(CF_server *server)
{
    cid_t	*nwref;

    if (server == NULL) {
	return;
    }

    /* take from the head of the free list */
    if (freenwref == NULL) {
	cf_dispose(server);
	return;
    }
    nwref = freenwref;
    if (freenwref->next != NULL) {
	freenwref->next->prev = NULL;
	freenwref = freenwref->next;
    } else {
	freenwref = 0;
	freenwreflast = 0;
    }

    /* put on the used list */
    nwref->prev = 0;
    nwref->next = usednwref;
    if (usednwref != NULL) {
	usednwref->prev = nwref;
    }
    usednwref = nwref;

    /* enter the nwref table */
    bynwref[nwref->nwref] = nwref;

    nwref->server = server;
}

/*
 * Set the service-id for an existing nwref structure.
 * The incoming sid switch hash table is setup to point to the
 * given nwref.
 */
static void setNwRefSid(cid_t *nwref, sid_t sid)
{
    int hash;

    /* take off the sid hash list */
    if (nwref->nexts != NULL) {
	nwref->nexts->prevs = nwref->prevs;
    }
    if (nwref->prevs != NULL) {
	nwref->prevs->nexts = nwref->nexts;
    } else if (nwref->sid > 0) {
	sidhash[sidHash(nwref->sid)] = nwref->next;
    }
    nwref->nexts = NULL;
    nwref->prevs = NULL;
    nwref->sid = 0;

    if (sid <= 0) {
	return;
    }

    /* insert into the hash list */
    nwref->sid = sid;
    hash = sidHash(sid);
    nwref->prevs = NULL;
    nwref->nexts = sidhash[hash];
    sidhash[hash] = nwref;
    if (nwref->nexts != NULL) {
	nwref->nexts->prevs = nwref;
    }
}

/*
 * Create a raw socket.
 */
int CreateRawSocket(int protocol_to_sniff)
{
    int rawsock;

    if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff)))== -1)
    {
	perror("Error creating raw socket: ");
	return -1;
    }

    return rawsock;
}

/*
 * Bind an existing raw socket to a given device and protocol.
 * If macaddr is not NULL it is filled with the MAC address of the device.
 */
int BindRawSocketToInterface(char *device, int rawsock, int protocol, char *macaddr)
{
	
    struct sockaddr_ll sll;
    struct ifreq ifr;
    struct packet_mreq	pr;

    bzero(&sll, sizeof(sll));
    bzero(&ifr, sizeof(ifr));
    bzero(&pr, sizeof(pr));
	
    strncpy((char *)ifr.ifr_name, device, IFNAMSIZ-1);

    if (macaddr != NULL) {
	if((ioctl(rawsock, SIOCGIFHWADDR, &ifr)) == -1) {
	    fprintf(stderr, "Error getting MAC address !\n");
	    return -1;
	}
	memcpy(macaddr, ifr.ifr_hwaddr.sa_data, 6);
    }

    /* Bind our raw socket to this interface */
    if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1) {
	fprintf(stderr, "Error getting Interface index !\n");
	return -1;
    }

    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(protocol); 

    if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1) {
	perror("Error binding raw socket to interface\n");
	return -1;
    }

    return 0;
}

void PrintHexLine(unsigned char *data, int len)
{
    int	idx;

    for (idx = 0; idx < 16; idx++) {
	if (idx == 8) {
	    printf(" ");
	}
	if (idx < len) {
	    printf("%02x ", data[idx]);
	} else {
	    printf("   ");
	}
    }
    printf("  ");
    for (idx = 0; idx < 16; idx++) {
	if (idx == 8) {
	    printf(" ");
	}
	if (idx < len) {
	    printf("%c", data[idx] >= ' ' ? data[idx] : '.');
	} else {
	    printf(" ");
	}
    }
    printf("\n");
}

void PrintPacketInHex(unsigned char *packet, int len)
{
    unsigned char *p = packet;

    printf("----- data dump %d bytes -----\n", len);
    while(len > 0)
    {
	PrintHexLine(p, len);
	len -= 16;
	p += 16;
    }
    printf("------ end ------\n");
}


static void PrintInHex(char *mesg, unsigned char *p, int len)
{
    printf("%s", mesg);

    while(len--)
    {
	printf("%.2X ", *p);
	p++;
    }
}


/*
 * Parse an incoming Ethernet packet.
 * Incoming service advertisements are decoded.
 * Incoming FAST packets are processed.
 */
static void ParseEthernetHeader(unsigned char *packet, int len)
{
    int			snwref;
    int			tnwref;
    unsigned char	smac[6];
    unsigned char	*data;
    size_t		size;

    if (len < 16) {
	return;
    }

    if (packet[12] != 0x11 || packet[13] != 0x11) { /* not a FAST packet */
	return;
    }

    memcpy(smac, &packet[6], 6);
    snwref = packet[14];
    tnwref = packet[15];
    data = &packet[16];
    size = len - 16;

    if (tnwref == SA_NWREF) {
	FastSAdecode(smac, data, size);
	return;
    }
    if (tnwref >= MINNWREF && tnwref <= MAXNWREF) {
	FastReceive(tnwref, snwref, smac, data, size);
    }
}

/*
 * Decode a FAST service advertisement.
 */
static int FastSAdecode(unsigned char *mac, unsigned char *msg , int mlen)
{
    int ret;
    int i, j;

    struct fsta fsta, gsta;
    struct fipp * fipp;
    struct fs * fs;
    struct fis * fis;
    struct fch * fch;

    struct fstc fstc, gstc;
    struct fc * fc;
    struct fic * fic;

    uint8_t ack, msgc;

    ret = fast_get_sta(&gsta, msg, mlen);
    if (ret < 0)
        return 1;
    
#if 0
    printf("Encoded STA:\n");
    printf("|-> ServerID: '%.4s'\n", gsta.fsta_sid);
    printf("|-> IP Prefixes (%d):\n", gsta.fsta_ippnum);
    for (i = 0; i < gsta.fsta_ippnum; i++) {
        printf("|   |-> PrefixInfo: %.*s/%u\n", gsta.fsta_ipp[i].fipp_alen, gsta.fsta_ipp[i].fipp_addr, gsta.fsta_ipp[i].fipp_len); 
    }
#endif

    for (i = 0; i < gsta.fsta_fsnum; i++) {
	int nwref = -1;

        if (gsta.fsta_fs[i].fs_nwref != 255) {
	    nwref = gsta.fsta_fs[i].fs_nwref;
        }

	incomingFastSA(gsta.fsta_fs[i].fs_sid, mac, nwref, gsta.fsta_fs[i].fs_data, gsta.fsta_fs[i].fs_dlen);

#if 0
        if (gsta.fsta_fs[i].fs_chid) {
            printf("|   ");
            if (i+1 != gsta.fsta_fsnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Service Channel: %u\n", gsta.fsta_fs[i].fs_chid);
            for (j = 0; j < gsta.fsta_chnum; j++) {
                if (gsta.fsta_ch[j].fch_id == gsta.fsta_fs[i].fs_chid) {
                    printf("|   ");
                    if (i+1 != gsta.fsta_fsnum)
                        printf("|");
                    else
                        printf(" ");
                    printf("       |-> Medtype: ");
                    switch(gsta.fsta_ch[j].fch_medtype) {
                        case CALM_MED_21212 : printf("21212"); break;
                        case CALM_MED_21213 : printf("21213"); break;
                        case CALM_MED_21214 : printf("21214"); break;
                        case CALM_MED_21215 : printf("21215"); break;
                        case CALM_MED_21216 : printf("21216"); break;
                        case CALM_MED_LAN_FAST : printf("LAN FAST"); break;
                        case CALM_MED_LAN_IP : printf("LAN IP"); break;
                    }
                    printf("\n");
                    printf("|   ");
                    if (i+1 != gsta.fsta_fsnum)
                        printf("|");
                    else
                        printf(" ");
                    printf("       |-> Channel Parameters: '%.*s'\n", gsta.fsta_ch[j].fch_plen, gsta.fsta_ch[j].fch_params);
                }
            }
        }
#endif
    }

#if 0
    printf("|-> IP Services (%u):\n", gsta.fsta_isnum);
    for (i = 0; i < gsta.fsta_isnum; i++) {
        printf("    |-> Service ID: %u\n", gsta.fsta_is[i].fis_sid);
        if (gsta.fsta_is[i].fis_data) {
            printf("    ");
            if (i+1 != gsta.fsta_isnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Service Data: %d bytes\n", gsta.fsta_is[i].fis_dlen);
        }
        printf("    ");
        if (i+1 != gsta.fsta_isnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> IP address type: ");
        switch(gsta.fsta_is[i].fis_ipa.fipa_type) {
            case AT_udpIpv4 : printf("UDP & IPv4"); break;
            case AT_udpIpv6 : printf("UDP & IPv6"); break;
            case AT_tcpIpv4 : printf("TCP & IPv4"); break;
            case AT_tcpIpv6 : printf("TCP & IPv6"); break;
        }
        printf("\n");
        printf("    ");
        if (i+1 != gsta.fsta_isnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> IP address: %.*s\n", gsta.fsta_is[i].fis_ipa.fipa_alen, gsta.fsta_is[i].fis_ipa.fipa_addr);
        if (gsta.fsta_is[i].fis_chid) {
            printf("    ");
            if (i+1 != gsta.fsta_isnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Service Channel: %u\n", gsta.fsta_is[i].fis_chid);
            for (j = 0; j < gsta.fsta_chnum; j++) {
                if (gsta.fsta_ch[j].fch_id == gsta.fsta_is[i].fis_chid) {
                    printf("    ");
                    if (i+1 != gsta.fsta_fsnum)
                        printf("|");
                    else
                        printf(" ");
                    printf("       |-> Medtype: ");
                    switch(gsta.fsta_ch[j].fch_medtype) {
                        case CALM_MED_21212 : printf("21212"); break;
                        case CALM_MED_21213 : printf("21213"); break;
                        case CALM_MED_21214 : printf("21214"); break;
                        case CALM_MED_21215 : printf("21215"); break;
                        case CALM_MED_21216 : printf("21216"); break;
                        case CALM_MED_LAN_FAST : printf("LAN FAST"); break;
                        case CALM_MED_LAN_IP : printf("LAN IP"); break;
                    }
                    printf("\n");
                    printf("    ");
                    if (i+1 != gsta.fsta_fsnum)
                        printf("|");
                    else
                        printf(" ");
                    printf("       |-> Channel Parameters: '%.*s'\n", gsta.fsta_ch[j].fch_plen, gsta.fsta_ch[j].fch_params);
                }
            }
        }
    }
#endif

    fsta_free(&gsta);
    return 0;
}


static int FastEncodeCAM(unsigned char *cam, int camlen, unsigned char *msg, int msglen)
{
    int ret;
    int i, j;

    struct fsta fsta, gsta;
    struct fs * fs;

    struct fstc fstc, gstc;
    struct fc * fc;
    struct fic * fic;

    uint8_t ack, msgc;

    memcpy(fsta.fsta_sid, "TEST", 4);

    fsta.fsta_ipp = NULL;
    fsta.fsta_ippnum = 0;

    fsta.fsta_fs = fs = malloc(sizeof(struct fs) * 1);
    fsta.fsta_fsnum = 1;
    
    fs[0].fs_sid = 32;
    fs[0].fs_nwref = 1;
    fs[0].fs_data = cam;
    fs[0].fs_dlen = camlen;
    fs[0].fs_chid = 0;

    fsta.fsta_is = NULL;
    fsta.fsta_isnum = 0;

    fsta.fsta_ch = NULL;
    fsta.fsta_chnum = 0;

    ret = fast_create_sta(&fsta, msg, msglen);
    if (verbose) printf("===> fast_create_sta returned with %d.\n", ret);
    free(fs);
    return ret;
}

static int tick;

#define MAXFSNUM	10

static void SendBeacons(int sock)
{
    int			ret;

    struct fsta		fsta;
    struct fs		*fs;

    cid_t		*currcid;
    int			fscnt = 0;
    unsigned char	packet[1500];
    unsigned char	*msg;
    int			msglen;

    tick++;
    if (verbose && tick % 10 == 0) {
	    printf("!\n");
	    fflush(stdout);
    }

    memcpy(&packet[0], broadcastmac, 6);
    memcpy(&packet[6], mymac, 6);
    packet[12] = 0x11;	/* FAST */
    packet[13] = 0x11;	/* FAST */
    packet[14] = 0;	/* source nwref */
    packet[15] = 0;	/* target nwref */
    msg = &packet[16];

    memcpy(fsta.fsta_sid, "TEST", 4);

    fsta.fsta_ipp = NULL;
    fsta.fsta_ippnum = 0;

    fsta.fsta_is = NULL;
    fsta.fsta_isnum = 0;

    fsta.fsta_ch = NULL;
    fsta.fsta_chnum = 0;

    fsta.fsta_fs = fs = calloc(MAXFSNUM, sizeof(struct fs));
    fsta.fsta_fsnum = fscnt;

    for (currcid = usednwref; currcid != NULL; currcid = currcid->next) {
	if (currcid->server == NULL || currcid->repeat < 0) continue;
	if (--currcid->ticks > 0) continue;
	
	fs[fscnt].fs_sid = currcid->sid;
	fs[fscnt].fs_nwref = currcid->nwref;
	fs[fscnt].fs_data = currcid->sadata;
	fs[fscnt].fs_dlen = currcid->sasize;
	fs[fscnt].fs_chid = 0;
	fsta.fsta_fsnum = ++fscnt;

	if (currcid->repeat <= 0) {
	    currcid->repeat = -1;	/* one shot advertisement, switch off */
	} else {
	    currcid->ticks = currcid->repeat;
	}
    }
    if (fscnt == 0) {
	free(fs);
    	return;
    }

    msglen = fast_create_sta(&fsta, msg, sizeof(packet) - 16);
    free(fs);
    if (verbose) printf("===> fast_create_sta returned with %d.\n", msglen);
    if (msglen > 0) {
	int result = send(sock, packet, msglen + 16, MSG_DONTWAIT);
	if (verbose) printf("===> send returned with %d.\n", result);
	if (result < 0) {
	    perror("SendBeacons");
	}
    }
}

static void SendBeacon(int sock, cid_t *currcid)
{
    int			ret;

    struct fsta		fsta;
    struct fs		*fs;

    int			fscnt = 0;
    unsigned char	packet[1500];
    unsigned char	*msg;
    int			msglen;

    if (currcid->server == NULL) return;

    memcpy(&packet[0], broadcastmac, 6);
    memcpy(&packet[6], mymac, 6);
    packet[12] = 0x11;	/* FAST */
    packet[13] = 0x11;	/* FAST */
    packet[14] = 0;	/* source nwref */
    packet[15] = 0;	/* target nwref */
    msg = &packet[16];

    memcpy(fsta.fsta_sid, "TEST", 4);

    fsta.fsta_ipp = NULL;
    fsta.fsta_ippnum = 0;

    fsta.fsta_is = NULL;
    fsta.fsta_isnum = 0;

    fsta.fsta_ch = NULL;
    fsta.fsta_chnum = 0;

    fsta.fsta_fs = fs = calloc(MAXFSNUM, sizeof(struct fs));
    fsta.fsta_fsnum = fscnt;

    fs[fscnt].fs_sid = currcid->sid;
    fs[fscnt].fs_nwref = currcid->nwref;
    fs[fscnt].fs_data = currcid->sadata;
    fs[fscnt].fs_dlen = currcid->sasize;
    fs[fscnt].fs_chid = 0;
    fsta.fsta_fsnum = ++fscnt;

    if (currcid->repeat <= 0) {
	currcid->repeat = -1;	/* one shot advertisement, switch off */
    } else {
	currcid->ticks = currcid->repeat;
    }

    msglen = fast_create_sta(&fsta, msg, sizeof(packet) - 16);
    free(fs);
    if (verbose) printf("===> fast_create_sta returned with %d.\n", msglen);
    if (msglen > 0) {
	int result = send(sock, packet, msglen + 16, MSG_DONTWAIT);
	if (verbose) printf("===> immediate send returned with %d.\n", result);
	if (result < 0) {
	    perror("SendBeacon (immediately)");
	}
    }
}

static void FastReceive(int tnwref, int snwref, unsigned char *mac, unsigned char *data, size_t size)
{
    cid_t	*curr;
    char	url[128];

    sprintf(url, "fast://0x%02x%02x%02x%02x%02x%02x:%d", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], snwref);

    if (verbose) printf("FastReceive tnwref=%d, url=%s, datasize=%d\n", tnwref, url, size);

    curr = bynwref[tnwref];
    if (curr != NULL && curr->server != NULL) {
	cf_sendserver(curr->server, url, data, size);
    }
}

static void incomingFastSA(int sid, unsigned char *mac, int nwref, unsigned char *data, size_t size)
{
    cid_t	*curr;
    char	url[128];

    sprintf(url, "fast://0x%02x%02x%02x%02x%02x%02x:%d", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], nwref);

    if (verbose) printf("incomingFastSA sid=%d, url=%s, datasize=%d\n", sid, url, size);

    for (curr = sidhash[sidHash(sid)]; curr != NULL; curr = curr->next) {
	if (curr->sid == sid && curr->server != NULL) {
	    cf_service(curr->server, url, data, size);
	}
    }
}


/****************** incoming client connection handling *********************/

static cid_t		*currcid;
static int		raw;

static int calm_open(CF_server *server, int sid, char **serverurl)
{
    if (verbose) printf("Open sid=%d\n", sid);
    currcid->sid = sid;
    sprintf(currcid->url, "fast://:%d", currcid->nwref);
    *serverurl = currcid->url;
    return 1;
}

static int calm_close(CF_server *server)
{
    if (verbose) printf("Close\n");
    destroyNwRef(currcid);
    return 1;
}

static int calm_send(CF_server *server, char *tourl, unsigned char *data, size_t size)
{
    unsigned char	mac[6];
    int			nwref;
    int			intmac[6];
    unsigned char	packet[1500];
    unsigned char	*msg;
    int			result;

    if (verbose) printf("Send url=%s, datasize=%d\n", tourl, size);

    if (currcid->server == NULL) {
	return 0;
    }

    if (sscanf(tourl, "fast://0x%02x%02x%02x%02x%02x%02x:%d", &intmac[0], &intmac[1], &intmac[2], &intmac[3],
    	&intmac[4], &intmac[5], &nwref) < 7) {
	return 0;
    }

    mac[0] = (unsigned char) intmac[0];
    mac[1] = (unsigned char) intmac[1];
    mac[2] = (unsigned char) intmac[2];
    mac[3] = (unsigned char) intmac[3];
    mac[4] = (unsigned char) intmac[4];
    mac[5] = (unsigned char) intmac[5];
    if (verbose) printf("fast://0x%02x%02x%02x%02x%02x%02x:%d\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], nwref);

    memcpy(&packet[0], mac, 6);
    memcpy(&packet[6], mymac, 6);
    packet[12] = 0x11;	/* FAST */
    packet[13] = 0x11;	/* FAST */
    packet[14] = currcid->nwref;	/* source nwref */
    packet[15] = nwref;	/* target nwref */
    msg = &packet[16];
    memcpy(msg, data, size);
    result = send(raw, packet, size + 16, MSG_DONTWAIT);
    if (verbose) {
	printf("calm_send result = %d\n", result);
	fflush(stdout);
    }
    return result;
}

static int calm_publish(CF_server *server, unsigned char *data, size_t size, long interval)
{
    if (verbose) printf("Publish datasize=%d, interval=%ld\n", size, interval);
    currcid->repeat = interval;
    if (currcid->sasize < size) {
    	if (currcid->sadata != NULL) {
	    free(currcid->sadata);
	}
	currcid->sadata = calloc(1, size);
    }
    currcid->sasize = size;
    memcpy(currcid->sadata, data, currcid->sasize);

    if (interval == 0) { /* immediate beacon without repeating it */
	SendBeacon(raw, currcid);
    }

    return 1;
}

static int calm_unpublish(CF_server *server)
{
    if (verbose) printf("Unpublish\n");
    if (currcid->sadata != NULL) {
	free(currcid->sadata);
	currcid->sadata = NULL;
    }
    currcid->sasize = 0;
    currcid->repeat = 0;
    return 1;
}

static int calm_monitor(CF_server *server)
{
    if (verbose) printf("Monitor\n");
    setNwRefSid(currcid, currcid->sid);
    return 1;
}

static int calm_unmonitor(CF_server *server)
{
    if (verbose) printf("Unmonitor\n");
    setNwRefSid(currcid, 0);
    return 1;
}

static void addms(struct timeval *tv, int ms)
{
    tv->tv_usec += ms * 1000;
    tv->tv_sec += tv->tv_usec / 1000000;
    tv->tv_usec %= 1000000;
}

static int tvdiff(struct timeval *last, struct timeval *first, struct timeval *diff)
{
    int udiff = 0;

    diff->tv_sec = 0;
    diff->tv_usec = 0;
    if (last->tv_sec < first->tv_sec)
	return 0;
    diff->tv_sec = last->tv_sec - first->tv_sec;
    udiff = last->tv_usec - first->tv_usec;
    if (udiff < 0) {
	udiff += 1000000;
	if (diff->tv_sec == 0) {
	    return 0;
	}
	diff->tv_sec -= 1;
    }
    diff->tv_usec = udiff;
    return 1;
}


int main(int argc, char *argv[])
{
    CF_server_cb	tcb = {
	.open = calm_open,
	.close = calm_close,
	.send = calm_send,
	.publish = calm_publish,
	.unpublish = calm_unpublish,
	.monitor = calm_monitor,
	.unmonitor = calm_unmonitor
    };

    int			lsock = -1;
    fd_set		rfds;
    struct timeval	tvto;
    struct timeval	tvnext;
    int			retval;
    int			fdmax = 0;
    const char		*rawif = "wlan0";

    void fd_start()
    {
	FD_ZERO(&rfds);
	fdmax = 0;
    }

    void fd_add(int sock)
    {
	if (sock < 0) return;
	FD_SET(sock, &rfds);
	if (sock >= fdmax) fdmax = sock + 1;
    }

    ParseOptions(argc, argv);
    if (optind < argc) {
	rawif = argv[optind];
    }

    initNwRef();

    /* create the raw socket */

    raw = CreateRawSocket(ETH_PROTOCOL);

    /* Bind socket to interface */
    do {
	sleep(1);
    	retval = BindRawSocketToInterface(rawif, raw, ETH_PROTOCOL, (char *) mymac);
    } while (retval < 0);

    lsock = listen_socket(1234);

    if (mustdaemonize) {
	daemonize();
    }

    gettimeofday(&tvnext, NULL);
    addms(&tvnext, 100);
    while (lsock >= 0 && raw >= 0) {

	struct timeval	now;
	int		timeout;
	cid_t		*nextcid;

	gettimeofday(&now, NULL);
	timeout = tvdiff(&tvnext, &now, &tvto);
	
	fd_start();
	fd_add(lsock);
	fd_add(raw);
	for (currcid = usednwref; currcid != NULL; currcid = currcid->next) {
	    if (currcid->server != NULL) {
		fd_add(currcid->server->socket);
	    }
	}
	// printf("select TO sec=%d, usec=%d\n", tvto.tv_sec, tvto.tv_usec);
	retval = select(fdmax, &rfds, NULL, NULL, &tvto);
	if (retval == -1) {
	    perror("select");
	    close(lsock);
	    lsock = -1;
	    continue;
	}

	if ((timeout == 0 || retval == 0)) {
	    SendBeacons(raw);
	    addms(&tvnext, 100);
	}

	if (FD_ISSET(raw, &rfds)) {
	    int			len;
	    unsigned char	packet_buffer[2048];
	    struct sockaddr_ll	packet_info;
	    socklen_t		packet_info_size = sizeof(packet_info);

	    if((len = recvfrom(raw, packet_buffer, 2048, 0, (struct sockaddr*)&packet_info, &packet_info_size)) == -1) {
		perror("Recv from returned -1: ");
		exit(-1);
	    } else {
		ParseEthernetHeader(packet_buffer, len);
	    }
	}

	currcid = usednwref;
	while (currcid != NULL) {
	    nextcid = currcid->next;
	    if (currcid->server != NULL && FD_ISSET(currcid->server->socket, &rfds)) {
		if (cf_recvserver(currcid->server, &tcb) < 0 || currcid->server->socket < 0) {
		    if (verbose) printf("Disposing of server connection\n");
		    destroyNwRef(currcid);
		}
	    }
	    currcid = nextcid;
	}

	if (FD_ISSET(lsock, &rfds)) {
	    createNwRef(cf_accept(lsock));
	}

    }

    exit(0);

}

