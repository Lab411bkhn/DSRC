/*
 * $Id: msg.c $
 *
 * This file is part of the CALM FAST Message Library.
 * 
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 *
 * Copyright 2006-2009 Ramsys Zrt
 *
 * CALM FAST Message Library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU LEsser General Public
 * License as published by the Free Software Foundation; version 3 of
 * the License.
 *
 * CALM FAST Message Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CALM FAST Message Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <inttypes.h>

#include <calm/calmmedia/mininl.h>
#include <linux/calm.h>

#include "Sta.h"
#include "Stc.h"
#include "Request.h"
#include "Response.h"
#include "constraints.h"

#include "msg.h"

inline void fs_p_free(struct fs * fs)
{
    fs_free(fs);
    free(fs);
}

inline void fs_free(struct fs * fs)
{
    if ((fs->fs_dlen > 0) && fs->fs_data)
        free(fs->fs_data);
}

inline void fipa_p_free(struct fipa * fipa)
{
    fipa_free(fipa);
    free(fipa);
}

inline void fipa_free(struct fipa * fipa)
{
    if ((fipa->fipa_alen > 0) && fipa->fipa_addr)
        free(fipa->fipa_addr);
}

inline void fis_p_free(struct fis * fis)
{
    fis_free(fis);
    free(fis);
}

inline void fis_free(struct fis * fis)
{
    if ((fis->fis_dlen > 0) && fis->fis_data)
        free(fis->fis_data);
    fipa_free(&fis->fis_ipa);
}

inline void fch_p_free(struct fch * fch)
{
    fch_free(fch);
    free(fch);
}

inline void fch_free(struct fch * fch)
{
    if ((fch->fch_plen > 0) && fch->fch_params)
        free(fch->fch_params);
}

static inline uint8_t fch_get_medtype(long medium)
{
    switch(medium) {
        case MedType_calm21212 :    return CALM_MED_21212;
        case MedType_calm21213 :    return CALM_MED_21213;
        case MedType_calm21214 :    return CALM_MED_21214;
        case MedType_calm21215 :    return CALM_MED_21215;
        case MedType_calm21216 :    return CALM_MED_21216;
        case MedType_lanFast :      return CALM_MED_LAN_FAST;
        case MedType_lanIP :        return CALM_MED_LAN_IP;
    }

    return 0;
}

static inline long fch_set_medtype(uint8_t medtype)
{
    switch(medtype) {
        case CALM_MED_21212 :   return MedType_calm21212;
        case CALM_MED_21213 :   return MedType_calm21213;
        case CALM_MED_21214 :   return MedType_calm21214;
        case CALM_MED_21215 :   return MedType_calm21215;
        case CALM_MED_21216 :   return MedType_calm21216;                                                                                                                                                        
        case CALM_MED_LAN_FAST :return MedType_lanFast;
        case CALM_MED_LAN_IP :  return MedType_lanIP;
    }

    return 0;
}

inline void fipp_p_free(struct fipp * fipp)
{
    fipp_free(fipp);
    free(fipp);
}

inline void fipp_free(struct fipp * fipp)
{
    if ((fipp->fipp_alen > 0) && fipp->fipp_addr)
        free(fipp->fipp_addr);
}

inline void fc_p_free(struct fc * fc)
{
    fc_free(fc);
    free(fc);
}

inline void fc_free(struct fc * fc)
{
    if ((fc->fc_dlen > 0) && fc->fc_data)
        free(fc->fc_data);
}

inline void fic_p_free(struct fic * fic)
{
    fic_free(fic);
    free(fic);
}

inline void fic_free(struct fic * fic)
{
    if ((fic->fic_dlen > 0) && fic->fic_data)
        free(fic->fic_data);
    fipa_free(&fic->fic_ipa);
}

inline void fsta_p_free(struct fsta * fsta)
{
    fsta_free(fsta);
    free(fsta);
}

inline void fsta_free(struct fsta * fsta)
{
    int i;

    if (fsta->fsta_ipp) {
        for (i = 0; i < fsta->fsta_ippnum; i++)
            fipp_free(&fsta->fsta_ipp[i]);
        free(fsta->fsta_ipp);
    }
    if (fsta->fsta_fs) {
        for(i = 0; i < fsta->fsta_fsnum; i++)
            fs_free(&fsta->fsta_fs[i]);
        free(fsta->fsta_fs);
    }
    if (fsta->fsta_is) {
        for(i = 0; i < fsta->fsta_isnum; i++)
            fis_free(&fsta->fsta_is[i]);
        free(fsta->fsta_is);
    }
    if (fsta->fsta_ch) {
        for(i = 0; i < fsta->fsta_chnum; i++)
            fch_free(&fsta->fsta_ch[i]);
        free(fsta->fsta_ch);
    }
}

inline void fstc_p_free(struct fstc * fstc)
{
    fstc_free(fstc);
    free(fstc);
}

inline void fstc_free(struct fstc * fstc)
{
    int i;

    if (fstc->fstc_ipp) {
        for (i = 0; i < fstc->fstc_ippnum; i++)
            fipp_free(&fstc->fstc_ipp[i]);
        free(fstc->fstc_ipp);
    }
    if (fstc->fstc_fc) {
        for(i = 0; i < fstc->fstc_fcnum; i++)
            fc_free(&fstc->fstc_fc[i]);
        free(fstc->fstc_fc);
    }
    if (fstc->fstc_ic) {
        for(i = 0; i < fstc->fstc_icnum; i++)
            fic_free(&fstc->fstc_ic[i]);
        free(fstc->fstc_ic);
    }
}

int fast_create_sta(struct fsta * fsta, unsigned char buf[], size_t blen)
{
    int retval = 0;
    int i, j;
    int ok;

    struct Sta asta; 
    struct IpPrefix * aprefix;
    struct FastService * aserv;
    struct IpService * aipserv;
    struct ServiceChannel * asch;

    char errbuf[512];
    size_t errlen = 512;
    asn_enc_rval_t enc;
    unsigned char buffer[blen - sizeof(size_t)];
    size_t bufferlen = blen - sizeof(size_t);

    //struct asn_per_data_s * ds;
    size_t * nbits;

    /* Parameter checking */
    if ( (buf == NULL) || (blen < sizeof(size_t)) )
        return -FAST_ERR_STA_BUF;

    if (fsta == NULL)
        return -FAST_ERR_STA_BUF;

    if ( (fsta->fsta_fsnum == 0) && (fsta->fsta_isnum == 0) )
        return -FAST_ERR_STA_EMPTY;

    //if (strlen((char *)fsta->fsta_sid) < 4)
    //    return -FAST_ERR_STA_SERVERID;

    /* Test IP prefixes */
    for (i = 0; i < fsta->fsta_ippnum; i++) {
        if ( (fsta->fsta_ipp[i].fipp_addr == NULL) || (fsta->fsta_ipp[i].fipp_alen == 0) ||
                (fsta->fsta_ipp[i].fipp_len == 0) )
            return -FAST_ERR_STA_PREFIX;
    }

    /* Test FAST services */
    for (i = 0; i < fsta->fsta_fsnum; i++) {
        if (fsta->fsta_fs[i].fs_sid == 0)
            return -FAST_ERR_STA_SID;
    
        if (fsta->fsta_fs[i].fs_nwref == 0)
            return -FAST_ERR_STA_NWREF;

        if ( (fsta->fsta_fs[i].fs_data == NULL) && (fsta->fsta_fs[i].fs_dlen > 0) )
            return -FAST_ERR_STA_DATA;

        if (fsta->fsta_fs[i].fs_chid > 0) {
            ok = 0;
            for (j = 0; j < fsta->fsta_chnum; j++) {
                if (fsta->fsta_ch[j].fch_id == fsta->fsta_fs[i].fs_chid) {
                    ok = 1;
                    break;
                }
            }
            if (! ok)
                return -FAST_ERR_STA_CHID;
        }
    }
 
    /* Test IP services */
    for (i = 0; i < fsta->fsta_isnum; i++) {
        if (fsta->fsta_is[i].fis_sid == 0)
            return -FAST_ERR_STA_SID;
    
        if ( (fsta->fsta_is[i].fis_data == NULL) && (fsta->fsta_is[i].fis_dlen > 0) )
            return -FAST_ERR_STA_DATA;

        if ( (fsta->fsta_is[i].fis_ipa.fipa_addr == NULL) || (fsta->fsta_is[i].fis_ipa.fipa_alen == 0) )
            return -FAST_ERR_STA_IPADDR;

        if ( (fsta->fsta_is[i].fis_ipa.fipa_type != AT_udpIpv4) && (fsta->fsta_is[i].fis_ipa.fipa_type != AT_udpIpv6) &&
                (fsta->fsta_is[i].fis_ipa.fipa_type != AT_tcpIpv4) && (fsta->fsta_is[i].fis_ipa.fipa_type != AT_tcpIpv6) )
            return -FAST_ERR_STA_IPTYPE;

        if (fsta->fsta_is[i].fis_chid > 0) {
            ok = 0;
            for (j = 0; j < fsta->fsta_chnum; j++) {
                if (fsta->fsta_ch[j].fch_id == fsta->fsta_is[i].fis_chid) {
                    ok = 1;
                    break;
                }
            }
            if (! ok)
                return -FAST_ERR_STA_CHID;
        }
    }   

    /* Test service Channels */
    for (i = 0; i < fsta->fsta_chnum; i++) {
        if (fsta->fsta_ch[i].fch_id == 0)
            return -FAST_ERR_STA_CHID;

        if ( (fsta->fsta_ch[i].fch_medtype != CALM_MED_21212) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_21213) &&
                (fsta->fsta_ch[i].fch_medtype != CALM_MED_21214) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_21215) &&
                (fsta->fsta_ch[i].fch_medtype != CALM_MED_21216) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_LAN_FAST) &&
                (fsta->fsta_ch[i].fch_medtype != CALM_MED_LAN_IP) )
            return -FAST_ERR_STA_MEDTYPE;

         if ( (fsta->fsta_ch[i].fch_params == NULL) || (fsta->fsta_ch[i].fch_plen == 0) )
            return -FAST_ERR_STA_CHPARAMS;
         
         ok = 0;
         for (j = 0; j < fsta->fsta_fsnum; j++) {
             if (fsta->fsta_fs[j].fs_chid == fsta->fsta_ch[i].fch_id) {
                 ok = 1;
                 break;
             }
         }
         if (! ok) {
             for (j = 0; j < fsta->fsta_isnum; j++) {
                 if (fsta->fsta_is[j].fis_chid == fsta->fsta_ch[i].fch_id) {
                     ok = 1;
                     break;
                 }
             }
             if (! ok)
                 return -FAST_ERR_STA_CHUNUSED;
         }
    }
    
    retval = -FAST_ERR_STA_NOMEM;
    
    /* Init ASN.1 STA stuct. Fill with zero, and create padding */
    memset(&asta, 0, sizeof(struct Sta));
    asta.fill.buf = malloc(1);
    if (! asta.fill.buf)
        goto c_sta_free;
    memset(asta.fill.buf, 0, 1);
    asta.fill.size = 1;
    asta.fill.bits_unused = 3;

    /* Setup type == STA */
    asta.messageType = MessageType_sta;

    /* Setup serverID */
    asta.serverID.buf = malloc(4);
    if (! asta.serverID.buf) {
        goto c_sta_free;
    }
    memset(asta.serverID.buf, 0, 4);
    asta.serverID.size = 4;
    memcpy(asta.serverID.buf, fsta->fsta_sid, 4);

    /* Setup IP prefixes if neccesary */
    if (fsta->fsta_ippnum > 0) {
        /* Create IPPrefixList buffer */
        asta.ipPrefixList = malloc(sizeof(struct IpPrefixList));
        if (! asta.ipPrefixList)
            goto c_sta_free;
        memset(asta.ipPrefixList, 0, sizeof(struct IpPrefixList));

        /* Iterate the prefixes */
        for (i = 0; i < fsta->fsta_ippnum; i++) {
            aprefix = malloc(sizeof(struct IpPrefix));
            if (! aprefix)
                goto c_sta_free;
            memset(aprefix, 0, sizeof(struct IpPrefix));
            aprefix->prefix.buf = malloc(fsta->fsta_ipp[i].fipp_alen);
            if (! aprefix->prefix.buf)
                goto c_sta_free;
            memset(aprefix->prefix.buf, 0, fsta->fsta_ipp[i].fipp_alen);
            aprefix->prefix.size = fsta->fsta_ipp[i].fipp_alen;
            memcpy(aprefix->prefix.buf, fsta->fsta_ipp[i].fipp_addr, fsta->fsta_ipp[i].fipp_alen);
            aprefix->prefixLen = fsta->fsta_ipp[i].fipp_len;
            ASN_SEQUENCE_ADD(asta.ipPrefixList, aprefix);
        }
    }

    /* Add FAST services if neccesary */
    if (fsta->fsta_fsnum > 0) {
        /* Create FAST Service List buffer, and the array of services */
        asta.serviceList = malloc(sizeof(struct ServiceList));
        if (! asta.serviceList)
            goto c_sta_free;
        memset(asta.serviceList, 0, sizeof(struct ServiceList));
        
        /* Iterate the services */
        for (i = 0; i < fsta->fsta_fsnum; i++) {
            /* Allocate the buffer */
            aserv = malloc(sizeof(struct FastService));
            if (! aserv)
                goto c_sta_free;
            memset(aserv, 0, sizeof(struct FastService));

            /* Init the service buffer: padding */
            aserv->fill.buf = malloc(1);
            if (! aserv->fill.buf)
                goto c_sta_free;
            memset(aserv->fill.buf, 0, 1);
            aserv->fill.size = 1;
            aserv->fill.bits_unused = 3;

            /* Setup serviceID */
            aserv->serviceID = fsta->fsta_fs[i].fs_sid;

            /* Setup serviceData */
            if (fsta->fsta_fs[i].fs_data) {
                aserv->serviceData = malloc(sizeof(struct OCTET_STRING));
                if (! aserv->serviceData)
                    goto c_sta_free;
                memset(aserv->serviceData, 0, sizeof(struct OCTET_STRING));
                aserv->serviceData->buf = malloc(fsta->fsta_fs[i].fs_dlen);
                if (! aserv->serviceData->buf)
                    goto c_sta_free;
                memset(aserv->serviceData->buf, 0, fsta->fsta_fs[i].fs_dlen);
                memcpy(aserv->serviceData->buf, fsta->fsta_fs[i].fs_data, fsta->fsta_fs[i].fs_dlen);
                aserv->serviceData->size = fsta->fsta_fs[i].fs_dlen;
            }

            /* Setup serverNWref */
            if (fsta->fsta_fs[i].fs_nwref != 255) {
                aserv->serverNWref = malloc(sizeof(long));
                if (! aserv->serverNWref)
                    goto c_sta_free;
                memset(aserv->serverNWref, 0, sizeof(long));
                *aserv->serverNWref = fsta->fsta_fs[i].fs_nwref;
            }   

            /* Setup channel ID */
            if (fsta->fsta_fs[i].fs_chid > 0) {
                aserv->serviceChannel = malloc(sizeof(long));
                if (! aserv->serviceChannel)
                    goto c_sta_free;
                memset(aserv->serviceChannel, 0, sizeof(long));
                *aserv->serviceChannel = fsta->fsta_fs[i].fs_chid;
            }

            /* Add service to the list */
            ASN_SEQUENCE_ADD(asta.serviceList, aserv);
        }
    }

    /* Add IP services if neccesary */
    if (fsta->fsta_isnum > 0) {
        /* Create IP Service List buffer, and the array of services */
        asta.ipServList = malloc(sizeof(struct IpServList));
        if (! asta.ipServList)
            goto c_sta_free;
        memset(asta.ipServList, 0, sizeof(struct IpServList));

        /* Iterate the IP services */
        for (i = 0; i < fsta->fsta_isnum; i++) {
            /* Allocate the buffer */
            aipserv = malloc(sizeof(struct IpService));
            if (! aipserv)
                goto c_sta_free;
            memset(aipserv, 0, sizeof(struct IpService));

            /* Init the service buffer: padding */
            aipserv->fill.buf = malloc(1);
            if (! aipserv->fill.buf)
                goto c_sta_free;
            memset(aipserv->fill.buf, 0, 1);
            aipserv->fill.size = 1;
            aipserv->fill.bits_unused = 2;

            /* Setup serviceID */
            aipserv->serviceID = fsta->fsta_is[i].fis_sid;

            /* Setup serviceData */
            if (fsta->fsta_is[i].fis_data) {
                aipserv->serviceData = malloc(sizeof(struct OCTET_STRING));
                if (! aipserv->serviceData)
                    goto c_sta_free;
                memset(aipserv->serviceData, 0, sizeof(struct OCTET_STRING));
                aipserv->serviceData->buf = malloc(fsta->fsta_is[i].fis_dlen);
                if (! aipserv->serviceData->buf)
                    goto c_sta_free;
                memset(aipserv->serviceData->buf, 0, fsta->fsta_is[i].fis_dlen);
                memcpy(aipserv->serviceData->buf, fsta->fsta_is[i].fis_data, fsta->fsta_is[i].fis_dlen);
                aipserv->serviceData->size = fsta->fsta_is[i].fis_dlen;
            }

            /* Setup IP adress */
            aipserv->ipInfo.address.address.buf = malloc(fsta->fsta_is[i].fis_ipa.fipa_alen);
            if (! aipserv->ipInfo.address.address.buf)
                goto c_sta_free;
            memset(aipserv->ipInfo.address.address.buf, 0, fsta->fsta_is[i].fis_ipa.fipa_alen);
            memcpy(aipserv->ipInfo.address.address.buf, fsta->fsta_is[i].fis_ipa.fipa_addr, fsta->fsta_is[i].fis_ipa.fipa_alen);
            aipserv->ipInfo.address.address.size = fsta->fsta_is[i].fis_ipa.fipa_alen;
            aipserv->ipInfo.address.addressType = fsta->fsta_is[i].fis_ipa.fipa_type;

            /* Setup channel ID */
            if (fsta->fsta_is[i].fis_chid > 0) {
                aipserv->serviceChannel = malloc(sizeof(long));
                if (! aipserv->serviceChannel)
                    goto c_sta_free;
                memset(aipserv->serviceChannel, 0, sizeof(long));
                *aipserv->serviceChannel = fsta->fsta_is[i].fis_chid;
            }

            /* Add IP service to the list */
            ASN_SEQUENCE_ADD(asta.ipServList, aipserv);
        }
    }

    /* Add service Channel details if neccesary */
    if (fsta->fsta_chnum > 0) {
        /* Create service Channel List buffer, and the array of services */
        asta.channelList = malloc(sizeof(struct ChannelList));
        if (! asta.channelList)
            goto c_sta_free;
        memset(asta.channelList, 0, sizeof(struct ChannelList));

        /* Iterate the service Channels */
        for (i = 0; i < fsta->fsta_chnum; i++) {
            /* Allocate the buffer */
            asch = malloc(sizeof(struct ServiceChannel));
            if (! asch)
                goto c_sta_free;
            memset(asch, 0, sizeof(struct ServiceChannel));

            /* Setup channel ID */
            asch->serviceChannel = fsta->fsta_ch[i].fch_id;
            
            /* Setup media */
            asch->medium = fch_set_medtype(fsta->fsta_ch[i].fch_medtype);

            /* Setup channel parameters */
            asch->schParams.buf = malloc(fsta->fsta_ch[i].fch_plen);
            if (! asch->schParams.buf)
                goto c_sta_free;
            memset(asch->schParams.buf, 0, fsta->fsta_ch[i].fch_plen);
            memcpy(asch->schParams.buf, fsta->fsta_ch[i].fch_params, fsta->fsta_ch[i].fch_plen);
            asch->schParams.size = fsta->fsta_ch[i].fch_plen;


            /* Add service Channel to the list */
            ASN_SEQUENCE_ADD(asta.channelList, asch);

        }
    }

	retval = -FAST_ERR_STA_CONSTRAINTS;

    /* Check constraints */
   	if (__LIBFAST__asn_check_constraints(&asn_DEF_Sta, &asta, errbuf, &errlen)) {
		printf("Error in expression: %s\n", errbuf);
        goto c_sta_free;
	}
	
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- STA --- ---\n");
    __LIBFAST__xer_fprint(stdout, &asn_DEF_Sta, &asta);    
    fprintf(stdout, "\n--- --- STA done --- ---\n");
    #endif

    /* Encoding */
    memset(buffer, 0, bufferlen);
	enc = __LIBFAST__uper_encode_to_buffer(&asn_DEF_Sta, &asta, buffer, bufferlen);
	if (enc.encoded == -1) {
        retval = -FAST_ERR_STA_BLEN;
        if (errno == 0)
            goto c_sta_free;
        
        #ifdef LIBFAST_DEBUG                                                                           
		fprintf(stdout, "Can't encode: %s (%s)\n", enc.failed_type->name, strerror(errno));
        #endif
		retval = -FAST_ERR_STA_ENCODE;
        goto c_sta_free;
	}

    memset(buf, 0, blen);
    //ds = (struct asn_per_data_s *)buf;
    //ds->nboff = htonl(0),
    //ds->nbits = htonl(enc.encoded);
    //memcpy(ds + 1, buffer, bufferlen);
    nbits = (size_t *)buf;
    *nbits = htonl(enc.encoded);
    memcpy(nbits + 1, buffer, bufferlen);

    //retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(struct asn_per_data_s);
    retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(size_t);

    #ifdef LIBFAST_DEBUG
    //printf("retval is %d, bufferlen is %d, nboff is %d, nbits is %d\n", retval, bufferlen, ds->nboff, ds->nbits);
    printf("retval is %d, bufferlen is %d, nbits is %d\n", retval, bufferlen, enc.encoded);
    #endif

c_sta_free:
    /* Free STA buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	asn_DEF_Sta.free_struct(&asn_DEF_Sta, &asta, 1);
     #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    return retval;
}

int fast_get_sta(struct fsta * fsta, unsigned char buf[], size_t blen)
{
    int retval = 0;
    int i, j;
    int ok;
    int c;
    
    struct Sta * asta = NULL; 
    struct IpPrefix * aprefix;
    struct FastService * aserv;
    struct IpService * aipserv;
    struct ServiceChannel * asch;

    //struct asn_per_data_s * ds;
    size_t * nbits;
    struct asn_per_data_s ds_save;
    unsigned char * buffer;
    size_t bufferlen;
    asn_dec_rval_t dec;
    
    /* Parameter checking */
    if ( (buf == NULL) || (blen < (sizeof(size_t) + 1)) )
        return -FAST_ERR_STA_BUF;

    if (fsta == NULL)
        return -FAST_ERR_STA_BUF;

    /* Clear the STA struct */
    memset(fsta, 0, sizeof(struct fsta));

    /* Decoding */
    //ds = (struct asn_per_data_s *)buf;
    nbits = (size_t *)buf;
    buffer = (unsigned char *)(nbits + 1);
    bufferlen = blen - sizeof(size_t);
    //bufferlen = blen - sizeof(struct asn_per_data_s);
    //ds->buffer = buffer;
    
    #ifdef LIBFAST_DEBUG
    printf("blen is %d, bufferlen is %d, nbits is %d\n", blen, bufferlen, ntohl(*nbits));
    #endif

    if ( (ntohl(*nbits) > bufferlen * 8) || (ntohl(*nbits) < (bufferlen - 1) * 8) )
        return -FAST_ERR_STA_BUF;

    memset(&ds_save, 0, sizeof(ds_save));
    ds_save.nboff = 0;
    ds_save.nbits = ntohl(*nbits);
    ds_save.buffer = buffer;
    dec = asn_DEF_Sta.uper_decoder(0, &asn_DEF_Sta, NULL, (void**)&asta, &ds_save);

	if (dec.code != RC_OK) {
		#ifdef LIBFAST_DEBUG
		switch(dec.code) {
			case RC_WMORE:
				printf("Decode error: There is more data expected than it is provided.\n");
				break;
			case RC_FAIL :
				printf("Decode error: General failure to decode the buffer. (Number of consumed bytes: %d / %d)\n", dec.consumed, blen);
				break;
			default:
				printf("Decode error: Unrecognized error code: %d.\n", dec.code);
		}
		#endif
		retval =  -FAST_ERR_STA_DECODE;
        goto g_sta_free;
	}
	
	#ifdef LIBFAST_DEBUG
    fprintf(stdout, "--- --- STA --- ---\n");
	__LIBFAST__xer_fprint(stdout, &asn_DEF_Sta, asta);
    fprintf(stdout, "--- --- STA done --- ---\n");
	#endif
 
    /* Test Message Type (STA) */
    retval = -FAST_ERR_STA_MSGTYPE;
    if (asta->messageType != MessageType_sta)
        goto g_sta_free;

    /* Get serverID */
    retval = -FAST_ERR_STA_SERVERID;
    if (! asta->serverID.buf)
        goto g_sta_free;
    if (asta->serverID.size != 4)
        goto g_sta_free;
    memcpy(fsta->fsta_sid, asta->serverID.buf, 4);

    /* Get IP prefixes */
    if (asta->ipPrefixList) {
        retval = -FAST_ERR_STA_EMPTY;
        c = asta->ipPrefixList->list.count;
        if (c <= 0)
            goto g_sta_services;
        retval = -FAST_ERR_STA_NOMEM;
        fsta->fsta_ipp = malloc(sizeof(struct fipp) * c);
        if (! fsta->fsta_ipp)
            goto g_sta_free;
        memset(fsta->fsta_ipp, 0, sizeof(struct fipp) * c);
        fsta->fsta_ippnum = c;
        for (i = 0; i < c; i++) {
            retval = -FAST_ERR_STA_NOMEM;
            aprefix = asta->ipPrefixList->list.array[i];
            if (! aprefix)
                goto g_sta_free;
            retval = -FAST_ERR_STA_PREFIX;
            if (! aprefix->prefix.buf)
                goto g_sta_free;
            fsta->fsta_ipp[i].fipp_addr = malloc(aprefix->prefix.size);
            retval = -FAST_ERR_STA_NOMEM;
            if (! fsta->fsta_ipp[i].fipp_addr)
                goto g_sta_free;
            memset(fsta->fsta_ipp[i].fipp_addr, 0, aprefix->prefix.size);
            memcpy(fsta->fsta_ipp[i].fipp_addr, aprefix->prefix.buf, aprefix->prefix.size);
            fsta->fsta_ipp[i].fipp_alen = aprefix->prefix.size;
            fsta->fsta_ipp[i].fipp_len = aprefix->prefixLen;
        }
    }

g_sta_services:    
    /* Get FAST services */
    if (asta->serviceList) {
        retval = -FAST_ERR_STA_EMPTY;
        c = asta->serviceList->list.count;
        if (c <= 0)
            goto g_sta_ipservices;
        retval = -FAST_ERR_STA_NOMEM;
        fsta->fsta_fs = malloc(sizeof(struct fs) * c);
        if (! fsta->fsta_fs)
            goto g_sta_free;
        memset(fsta->fsta_fs, 0, sizeof(struct fs) * c);
        fsta->fsta_fsnum = c;
        for (i = 0; i < c; i++) {
            aserv = asta->serviceList->list.array[i];
            retval = -FAST_ERR_STA_EMPTY;
            if (! aserv)
                goto g_sta_free;

            /* Get service ID */
            fsta->fsta_fs[i].fs_sid = aserv->serviceID;
            retval = -FAST_ERR_STA_SID;
            if (fsta->fsta_fs[i].fs_sid == 0)
                goto g_sta_free;

            /* Get service Data */
            if (aserv->serviceData) {
                retval = -FAST_ERR_STA_DATA;
                if (! aserv->serviceData->buf)
                    goto g_sta_free;
                fsta->fsta_fs[i].fs_data = malloc(aserv->serviceData->size);
                retval = -FAST_ERR_STA_NOMEM;
                if (! fsta->fsta_fs[i].fs_data)
                    goto g_sta_free;
                memset(fsta->fsta_fs[i].fs_data, 0, aserv->serviceData->size);
                memcpy(fsta->fsta_fs[i].fs_data, aserv->serviceData->buf, aserv->serviceData->size);
                fsta->fsta_fs[i].fs_dlen = aserv->serviceData->size;
            }

            /* Get server NWref */
            if (aserv->serverNWref) 
                fsta->fsta_fs[i].fs_nwref = *aserv->serverNWref;
            else
                fsta->fsta_fs[i].fs_nwref = 255;

            /* Get service Channel */
            retval = -FAST_ERR_STA_CHID;
            if (aserv->serviceChannel) {
                if (! asta->channelList)
                    goto g_sta_free;
                ok = 0;
                for (j = 0; j < asta->channelList->list.count; j++) {
                    if (asta->channelList->list.array[j]->serviceChannel == *aserv->serviceChannel)
                        ok = 1;
                }
                if (! ok)
                    goto g_sta_free;

                fsta->fsta_fs[i].fs_chid = *aserv->serviceChannel;
            }
        }
    }

g_sta_ipservices:    
    /* Get IP services */
    if (asta->ipServList) {
        retval = -FAST_ERR_STA_EMPTY;
        c = asta->ipServList->list.count;
        if (c <= 0)
            goto g_sta_channels;
        retval = -FAST_ERR_STA_NOMEM;
        fsta->fsta_is = malloc(sizeof(struct fis) * c);
        if (! fsta->fsta_is)
            goto g_sta_free;
        memset(fsta->fsta_is, 0, sizeof(struct fis) * c);
        fsta->fsta_isnum = c;
        for (i = 0; i < c; i++) {
            aipserv = asta->ipServList->list.array[i];
            retval = -FAST_ERR_STA_EMPTY;
            if (! aipserv)
                goto g_sta_free;

            /* Get service ID */
            fsta->fsta_is[i].fis_sid = aipserv->serviceID;
            retval = -FAST_ERR_STA_SID;
            if (fsta->fsta_is[i].fis_sid == 0)
                goto g_sta_free;

            /* Get service Data */
            if (aipserv->serviceData) {
                retval = -FAST_ERR_STA_DATA;
                if (! aipserv->serviceData->buf)
                    goto g_sta_free;
                fsta->fsta_is[i].fis_data = malloc(aipserv->serviceData->size);
                retval = -FAST_ERR_STA_NOMEM;
                if (! fsta->fsta_is[i].fis_data)
                    goto g_sta_free;
                memset(fsta->fsta_is[i].fis_data, 0, aipserv->serviceData->size);
                memcpy(fsta->fsta_is[i].fis_data, aipserv->serviceData->buf, aipserv->serviceData->size);
                fsta->fsta_is[i].fis_dlen = aipserv->serviceData->size;
            }

            /* Get IP address */
            retval = -FAST_ERR_STA_IPADDR;
            if (! aipserv->ipInfo.address.address.buf)
                goto g_sta_free;
            fsta->fsta_is[i].fis_ipa.fipa_addr = malloc(aipserv->ipInfo.address.address.size);
            retval = -FAST_ERR_STA_NOMEM;
            if (! fsta->fsta_is[i].fis_ipa.fipa_addr)
                goto g_sta_free;
            memset(fsta->fsta_is[i].fis_ipa.fipa_addr, 0, aipserv->ipInfo.address.address.size);
            memcpy(fsta->fsta_is[i].fis_ipa.fipa_addr, aipserv->ipInfo.address.address.buf, aipserv->ipInfo.address.address.size);
            fsta->fsta_is[i].fis_ipa.fipa_alen = aipserv->ipInfo.address.address.size;
            fsta->fsta_is[i].fis_ipa.fipa_type = aipserv->ipInfo.address.addressType;
            retval = -FAST_ERR_STA_IPTYPE;
            if ( (fsta->fsta_is[i].fis_ipa.fipa_type != AT_udpIpv4) && (fsta->fsta_is[i].fis_ipa.fipa_type != AT_udpIpv6) &&
                    (fsta->fsta_is[i].fis_ipa.fipa_type != AT_tcpIpv4) && (fsta->fsta_is[i].fis_ipa.fipa_type != AT_tcpIpv6) )
                goto g_sta_free;

            /* Get service Channel */
            retval = -FAST_ERR_STA_CHID;
            if (aipserv->serviceChannel) {
                if (! asta->channelList)
                    goto g_sta_free;
                ok = 0;
                for (j = 0; j < asta->channelList->list.count; j++) {
                    if (asta->channelList->list.array[j]->serviceChannel == *aipserv->serviceChannel)
                        ok = 1;
                }
                if (! ok)
                    goto g_sta_free;

                fsta->fsta_is[i].fis_chid = *aipserv->serviceChannel;
            }
        }
    }

g_sta_channels:    
    /* Get Service Chanels */
    if (asta->channelList) {
        retval = 0;
        c = asta->channelList->list.count;
        if (c <= 0)
            goto g_sta_free;
        retval = -FAST_ERR_STA_NOMEM;
        fsta->fsta_ch = malloc(sizeof(struct fch) * c);
        if (! fsta->fsta_ch)
            goto g_sta_free;
        memset(fsta->fsta_ch, 0, sizeof(struct fch) * c);
        fsta->fsta_chnum = c;
        for (i = 0; i < c; i++) {
            asch = asta->channelList->list.array[i];
            retval = -FAST_ERR_STA_EMPTY;
            if (! asch)
                goto g_sta_free;

            /* Get service Channel */
            fsta->fsta_ch[i].fch_id = asch->serviceChannel;
            retval = -FAST_ERR_STA_CHID;
            if (fsta->fsta_ch[i].fch_id == 0)
                goto g_sta_free;

            /* Get Medtype */
            fsta->fsta_ch[i].fch_medtype = fch_get_medtype(asch->medium);
            retval = -FAST_ERR_STA_MEDTYPE;
            if ( (fsta->fsta_ch[i].fch_medtype != CALM_MED_21212) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_21213) &&
                    (fsta->fsta_ch[i].fch_medtype != CALM_MED_21214) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_21215) &&
                    (fsta->fsta_ch[i].fch_medtype != CALM_MED_21216) &&  (fsta->fsta_ch[i].fch_medtype != CALM_MED_LAN_FAST) &&
                    (fsta->fsta_ch[i].fch_medtype != CALM_MED_LAN_IP) )
                goto g_sta_free;

            /* Get channel Parameters */
            retval = -FAST_ERR_STA_CHPARAMS;
            if (! asch->schParams.buf)
                goto g_sta_free;
            fsta->fsta_ch[i].fch_params = malloc(asch->schParams.size);
            retval = -FAST_ERR_STA_NOMEM;
            if (! fsta->fsta_ch[i].fch_params)
                goto g_sta_free;
            memset(fsta->fsta_ch[i].fch_params, 0, asch->schParams.size);
            memcpy(fsta->fsta_ch[i].fch_params, asch->schParams.buf, asch->schParams.size);
            fsta->fsta_ch[i].fch_plen = asch->schParams.size;
        }
    }

    retval = 0;

g_sta_free:
    /* Free STA buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	asn_DEF_Sta.free_struct(&asn_DEF_Sta, asta, 0);
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    /* Free STA struct */
    if (retval)
        fsta_free(fsta);

    return retval;
}

int fast_create_stc(struct fstc * fstc, unsigned char buf[], size_t blen)
{
    int retval = 0;
    int i;

    struct Stc astc; 
    struct IpPrefix * aprefix;
    struct FastContext * actx;
    struct IpContext * aipctx;

    char errbuf[512];
    size_t errlen = 512;
    asn_enc_rval_t enc;
    unsigned char buffer[blen - sizeof(size_t)];
    size_t bufferlen = blen - sizeof(size_t);

    //struct asn_per_data_s * ds;
    size_t * nbits;

    /* Parameter checking */
    if ( (buf == NULL) || (blen < sizeof(size_t)) )
        return -FAST_ERR_STC_BUF;

    if (fstc == NULL)
        return -FAST_ERR_STC_BUF;

    if ( (fstc->fstc_fcnum == 0) && (fstc->fstc_icnum == 0) )
        return -FAST_ERR_STC_EMPTY;

    //if (strlen((char *)fstc->fstc_sid) < 4)
    //    return -FAST_ERR_STC_CLIENTID;

    /* Test IP prefixes */
    for (i = 0; i < fstc->fstc_ippnum; i++) {
        if ( (fstc->fstc_ipp[i].fipp_addr == NULL) || (fstc->fstc_ipp[i].fipp_alen == 0) ||
                (fstc->fstc_ipp[i].fipp_len == 0) )
            return -FAST_ERR_STC_PREFIX;
    }

    /* Test FAST contexts */
    for (i = 0; i < fstc->fstc_fcnum; i++) {
        if (fstc->fstc_fc[i].fc_sid == 0)
            return -FAST_ERR_STC_SID;
    
        if ( (fstc->fstc_fc[i].fc_nwref == 0) || (fstc->fstc_fc[i].fc_nwref == 255) )
            return -FAST_ERR_STC_NWREF;

        #ifdef FST_DISABLE_STC_DATA_RESTRICTION   
        if ( (fstc->fstc_fc[i].fc_data == NULL) || (fstc->fstc_fc[i].fc_dlen == 0) )
            return -FAST_ERR_STC_DATA;
        #endif
    }
 
    /* Test IP contexts */
    for (i = 0; i < fstc->fstc_icnum; i++) {
        if (fstc->fstc_ic[i].fic_sid == 0)
            return -FAST_ERR_STC_SID;
    
        #ifdef FST_DISABLE_STC_DATA_RESTRICTION   
        if ( (fstc->fstc_ic[i].fic_data == NULL) || (fstc->fstc_ic[i].fic_dlen == 0) )
            return -FAST_ERR_STC_DATA;
        #endif

        if ( (fstc->fstc_ic[i].fic_ipa.fipa_addr == NULL) || (fstc->fstc_ic[i].fic_ipa.fipa_alen == 0) )
            return -FAST_ERR_STC_IPADDR;

        if ( (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_udpIpv4) && (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_udpIpv6) &&
                (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_tcpIpv4) && (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_tcpIpv6) )
            return -FAST_ERR_STC_IPTYPE;
    }   
    
    retval = -FAST_ERR_STC_NOMEM;
    
    /* Init ASN.1 STC stuct. Fill with zero, and create padding */
    memset(&astc, 0, sizeof(struct Stc));
    astc.fill.buf = malloc(1);
    if (! astc.fill.buf)
        goto c_stc_free;
    memset(astc.fill.buf, 0, 1);
    astc.fill.size = 1;
    astc.fill.bits_unused = 2;

    /* Setup type == STC */
    astc.messageType = MessageType_stc;

    /* Setup clientID */
    astc.clientID.buf = malloc(4);
    if (! astc.clientID.buf) {
        goto c_stc_free;
    }
    memset(astc.clientID.buf, 0, 4);
    astc.clientID.size = 4;
    memcpy(astc.clientID.buf, fstc->fstc_sid, 4);

    /* Setup IP prefixes if neccesary */
    if (fstc->fstc_ippnum > 0) {
        /* Create IPPrefixList buffer */
        astc.ipPrefixList = malloc(sizeof(struct IpPrefixList));
        if (! astc.ipPrefixList)
            goto c_stc_free;
        memset(astc.ipPrefixList, 0, sizeof(struct IpPrefixList));

        /* Iterate the prefixes */
        for (i = 0; i < fstc->fstc_ippnum; i++) {
            aprefix = malloc(sizeof(struct IpPrefix));
            if (! aprefix)
                goto c_stc_free;
            memset(aprefix, 0, sizeof(struct IpPrefix));
            aprefix->prefix.buf = malloc(fstc->fstc_ipp[i].fipp_alen);
            if (! aprefix->prefix.buf)
                goto c_stc_free;
            memset(aprefix->prefix.buf, 0, fstc->fstc_ipp[i].fipp_alen);
            aprefix->prefix.size = fstc->fstc_ipp[i].fipp_alen;
            memcpy(aprefix->prefix.buf, fstc->fstc_ipp[i].fipp_addr, fstc->fstc_ipp[i].fipp_alen);
            aprefix->prefixLen = fstc->fstc_ipp[i].fipp_len;
            ASN_SEQUENCE_ADD(astc.ipPrefixList, aprefix);
        }
    }
   
    /* Add FAST contexts if neccesary */
    if (fstc->fstc_fcnum > 0) {
        /* Create FAST Context List buffer, and the array of services */
        astc.servContextList = malloc(sizeof(struct ServContextList));
        if (! astc.servContextList)
            goto c_stc_free;
        memset(astc.servContextList, 0, sizeof(struct ServContextList));
        
        /* Iterate the contexts */
        for (i = 0; i < fstc->fstc_fcnum; i++) {
            /* Allocate the buffer */
            actx = malloc(sizeof(struct FastService));
            if (! actx)
                goto c_stc_free;
            memset(actx, 0, sizeof(struct FastService));

            /* Setup serviceID */
            actx->serviceID = fstc->fstc_fc[i].fc_sid;

            /* Setup contextData */
            if (fstc->fstc_fc[i].fc_dlen > 0)
                actx->contextData.buf = malloc(fstc->fstc_fc[i].fc_dlen);
            else
                actx->contextData.buf = malloc(1);
            if (! actx->contextData.buf)
                goto c_stc_free;
            if (fstc->fstc_fc[i].fc_dlen > 0) {
                memset(actx->contextData.buf, 0, fstc->fstc_fc[i].fc_dlen);
                memcpy(actx->contextData.buf, fstc->fstc_fc[i].fc_data, fstc->fstc_fc[i].fc_dlen);
                actx->contextData.size = fstc->fstc_fc[i].fc_dlen;
            } else {
                memset(actx->contextData.buf, 0, 1);
                actx->contextData.size = 0;
            } 

            /* Setup userNWref */
            actx->userNWref = fstc->fstc_fc[i].fc_nwref;

            /* Add service to the list */
            ASN_SEQUENCE_ADD(astc.servContextList, actx);
        }
    }

    /* Add IP contexts if neccesary */
    if (fstc->fstc_icnum > 0) {
        /* Create IP Context List buffer, and the array of services */
        astc.ipContextList = malloc(sizeof(struct IpContextList));
        if (! astc.ipContextList)
            goto c_stc_free;
        memset(astc.ipContextList, 0, sizeof(struct IpContextList));

        /* Iterate the IP contexts */
        for (i = 0; i < fstc->fstc_icnum; i++) {
            /* Allocate the buffer */
            aipctx = malloc(sizeof(struct IpContext));
            if (! aipctx)
                goto c_stc_free;
            memset(aipctx, 0, sizeof(struct IpContext));

            /* Setup serviceID */
            aipctx->serviceID = fstc->fstc_ic[i].fic_sid;

            /* Setup contextData */
            aipctx->contextData.buf = malloc(fstc->fstc_ic[i].fic_dlen);
            if (! aipctx->contextData.buf)
                goto c_stc_free;
            memset(aipctx->contextData.buf, 0, fstc->fstc_ic[i].fic_dlen);
            memcpy(aipctx->contextData.buf, fstc->fstc_ic[i].fic_data, fstc->fstc_ic[i].fic_dlen);
            aipctx->contextData.size = fstc->fstc_ic[i].fic_dlen;

            /* Setup IP adress */
            aipctx->ipInfo.address.address.buf = malloc(fstc->fstc_ic[i].fic_ipa.fipa_alen);
            if (! aipctx->ipInfo.address.address.buf)
                goto c_stc_free;
            memset(aipctx->ipInfo.address.address.buf, 0, fstc->fstc_ic[i].fic_ipa.fipa_alen);
            memcpy(aipctx->ipInfo.address.address.buf, fstc->fstc_ic[i].fic_ipa.fipa_addr, fstc->fstc_ic[i].fic_ipa.fipa_alen);
            aipctx->ipInfo.address.address.size = fstc->fstc_ic[i].fic_ipa.fipa_alen;
            aipctx->ipInfo.address.addressType = fstc->fstc_ic[i].fic_ipa.fipa_type;

            /* Add IP service to the list */
            ASN_SEQUENCE_ADD(astc.ipContextList, aipctx);
        }
    }

	retval = -FAST_ERR_STC_CONSTRAINTS;

    /* Check constraints */
   	if (__LIBFAST__asn_check_constraints(&asn_DEF_Stc, &astc, errbuf, &errlen)) {
		printf("Error in expression: %s\n", errbuf);
        goto c_stc_free;
	}
	
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- STC --- ---\n");
    __LIBFAST__xer_fprint(stdout, &asn_DEF_Stc, &astc);    
    fprintf(stdout, "\n--- --- STC done --- ---\n");
    #endif

    /* Encoding */
    memset(buffer, 0, bufferlen);
	enc = __LIBFAST__uper_encode_to_buffer(&asn_DEF_Stc, &astc, buffer, bufferlen);
	if (enc.encoded == -1) {
        retval = -FAST_ERR_STC_BLEN;
        if (errno == 0)
            goto c_stc_free;
        
        #ifdef LIBFAST_DEBUG                                                                           
		fprintf(stdout, "Can't encode: %s (%s)\n", enc.failed_type->name, strerror(errno));
        #endif
		retval = -FAST_ERR_STC_ENCODE;
        goto c_stc_free;
	}

    memset(buf, 0, blen);
    //ds = (struct asn_per_data_s *)buf;
    //ds->nboff = htonl(0),
    //ds->nbits = htonl(enc.encoded);
    //memcpy(ds + 1, buffer, bufferlen);
    nbits = (size_t *)buf;
    *nbits = htonl(enc.encoded);
    memcpy(nbits + 1, buffer, bufferlen);

    //retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(struct asn_per_data_s);
    retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(size_t);

    #ifdef LIBFAST_DEBUG
    //printf("retval is %d, bufferlen is %d, nboff is %d, nbits is %d\n", retval, bufferlen, ds->nboff, ds->nbits);
    printf("retval is %d, bufferlen is %d, nbits is %d\n", retval, bufferlen, enc.encoded);
    #endif

c_stc_free:
    /* Free STC buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	asn_DEF_Stc.free_struct(&asn_DEF_Stc, &astc, 1);
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    return retval;
}

int fast_get_stc(struct fstc * fstc, unsigned char buf[], size_t blen)
{
    int retval = 0;
    int i;
    int c;

    struct Stc * astc = NULL; 
    struct IpPrefix * aprefix;
    struct FastContext * actx;
    struct IpContext * aipctx;

    //struct asn_per_data_s * ds;
    struct asn_per_data_s ds_save;
    size_t * nbits;
    unsigned char * buffer;
    size_t bufferlen;
    asn_dec_rval_t dec;
    
    /* Parameter checking */
    if ( (buf == NULL) || (blen < (sizeof(size_t) + 1)) )
        return -FAST_ERR_STC_BUF;

    if (fstc == NULL)
        return -FAST_ERR_STC_BUF;

    /* Clear the STC struct */
    memset(fstc, 0, sizeof(struct fstc));

    /* Decoding */
    //ds = (struct asn_per_data_s *)buf;
    nbits = (size_t *)buf;
    buffer = (unsigned char *)(nbits + 1);
    bufferlen = blen - sizeof(size_t);
    //bufferlen = blen - sizeof(struct asn_per_data_s);
    //ds->buffer = buffer;
    
    #ifdef LIBFAST_DEBUG
    printf("blen is %d, bufferlen is %d, nbits is %d\n", blen, bufferlen, ntohl(*nbits));
    #endif

    if ( (ntohl(*nbits) > bufferlen * 8) || (ntohl(*nbits) < (bufferlen - 1) * 8) )
        return -FAST_ERR_STA_BUF;

    memset(&ds_save, 0, sizeof(ds_save));
    ds_save.nboff = 0;
    ds_save.nbits = ntohl(*nbits);
    ds_save.buffer = buffer;
   	dec = asn_DEF_Stc.uper_decoder(0, &asn_DEF_Stc, NULL, (void**)&astc, &ds_save);

	if (dec.code != RC_OK) {
		#ifdef LIBFAST_DEBUG
		switch(dec.code) {
			case RC_WMORE:
				printf("Decode error: There is more data expected than it is provided.\n");
				break;
			case RC_FAIL :
				printf("Decode error: General failure to decode the buffer. (Number of consumed bytes: %d / %d)\n", dec.consumed, blen);
				break;
			default:
				printf("Decode error: Unrecognized error code: %d.\n", dec.code);
		}
		#endif
		retval = -FAST_ERR_STC_DECODE;
        goto g_stc_free;
	}
	
	#ifdef LIBFAST_DEBUG
    fprintf(stdout, "--- --- STC --- ---\n");
	__LIBFAST__xer_fprint(stdout, &asn_DEF_Stc, astc);
    fprintf(stdout, "--- --- STC done --- ---\n");
	#endif
 
    /* Test Message Type (STC) */
    retval = -FAST_ERR_STC_MSGTYPE;
    if (astc->messageType != MessageType_stc)
        goto g_stc_free;

    /* Get clientID */
    retval = -FAST_ERR_STC_CLIENTID;
    if (! astc->clientID.buf)
        goto g_stc_free;
    if (astc->clientID.size != 4)
        goto g_stc_free;
    memcpy(fstc->fstc_sid, astc->clientID.buf, 4);

    /* Get IP prefixes */
    if (astc->ipPrefixList) {
        retval = -FAST_ERR_STC_EMPTY;
        c = astc->ipPrefixList->list.count;
        if (c <= 0)
            goto g_stc_contexts;
        retval = -FAST_ERR_STC_NOMEM;
        fstc->fstc_ipp = malloc(sizeof(struct fipp) * c);
        if (! fstc->fstc_ipp)
            goto g_stc_free;
        memset(fstc->fstc_ipp, 0, sizeof(struct fipp) * c);
        fstc->fstc_ippnum = c;
        for (i = 0; i < c; i++) {
            retval = -FAST_ERR_STC_NOMEM;
            aprefix = astc->ipPrefixList->list.array[i];
            if (! aprefix)
                goto g_stc_free;
            retval = -FAST_ERR_STC_PREFIX;
            if (! aprefix->prefix.buf)
                goto g_stc_free;
            fstc->fstc_ipp[i].fipp_addr = malloc(aprefix->prefix.size);
            retval = -FAST_ERR_STC_NOMEM;
            if (! fstc->fstc_ipp[i].fipp_addr)
                goto g_stc_free;
            memset(fstc->fstc_ipp[i].fipp_addr, 0, aprefix->prefix.size);
            memcpy(fstc->fstc_ipp[i].fipp_addr, aprefix->prefix.buf, aprefix->prefix.size);
            fstc->fstc_ipp[i].fipp_alen = aprefix->prefix.size;
            fstc->fstc_ipp[i].fipp_len = aprefix->prefixLen;
        }
    }
   
g_stc_contexts:
    /* Get FAST contexts */
    if (astc->servContextList) {
        retval = -FAST_ERR_STC_EMPTY;
        c = astc->servContextList->list.count;
        if (c <= 0)
            goto g_stc_ipcontexts;
        retval = -FAST_ERR_STC_NOMEM;
        fstc->fstc_fc = malloc(sizeof(struct fc) * c);
        if (! fstc->fstc_fc)
            goto g_stc_free;
        memset(fstc->fstc_fc, 0, sizeof(struct fc) * c);
        fstc->fstc_fcnum = c;
        for (i = 0; i < c; i++) {
            actx = astc->servContextList->list.array[i];
            retval = -FAST_ERR_STC_EMPTY;
            if (! actx)
                goto g_stc_free;

            /* Get service ID */
            fstc->fstc_fc[i].fc_sid = actx->serviceID;
            retval = -FAST_ERR_STC_SID;
            if (fstc->fstc_fc[i].fc_sid == 0)
                goto g_stc_free;

            /* Get context Data */
            retval = -FAST_ERR_STC_DATA;
            if (! actx->contextData.buf)
                goto g_stc_free;
            fstc->fstc_fc[i].fc_data = malloc(actx->contextData.size);
            retval = -FAST_ERR_STC_NOMEM;
            if (! fstc->fstc_fc[i].fc_data)
                goto g_stc_free;
            memset(fstc->fstc_fc[i].fc_data, 0, actx->contextData.size);
            memcpy(fstc->fstc_fc[i].fc_data, actx->contextData.buf, actx->contextData.size);
            fstc->fstc_fc[i].fc_dlen = actx->contextData.size;

            /* Get user NWref */
            fstc->fstc_fc[i].fc_nwref = actx->userNWref;
        }
    }

g_stc_ipcontexts:
    /* Get IP contexts */
    if (astc->ipContextList) {
        retval = 0;
        c = astc->ipContextList->list.count;
        if (c <= 0)
            goto g_stc_free;
        retval = -FAST_ERR_STC_NOMEM;
        fstc->fstc_ic = malloc(sizeof(struct fic) * c);
        if (! fstc->fstc_ic)
            goto g_stc_free;
        memset(fstc->fstc_ic, 0, sizeof(struct fic) * c);
        fstc->fstc_icnum = c;
        for (i = 0; i < c; i++) {
            aipctx = astc->ipContextList->list.array[i];
            retval = -FAST_ERR_STC_EMPTY;
            if (! aipctx)
                goto g_stc_free;

            /* Get service ID */
            fstc->fstc_ic[i].fic_sid = aipctx->serviceID;
            retval = -FAST_ERR_STC_SID;
            if (fstc->fstc_ic[i].fic_sid == 0)
                goto g_stc_free;

            /* Get context Data */
            retval = -FAST_ERR_STC_DATA;
            if (! aipctx->contextData.buf)
                goto g_stc_free;
            fstc->fstc_ic[i].fic_data = malloc(aipctx->contextData.size);
            retval = -FAST_ERR_STC_NOMEM;
            if (! fstc->fstc_ic[i].fic_data)
                goto g_stc_free;
            memset(fstc->fstc_ic[i].fic_data, 0, aipctx->contextData.size);
            memcpy(fstc->fstc_ic[i].fic_data, aipctx->contextData.buf, aipctx->contextData.size);
            fstc->fstc_ic[i].fic_dlen = aipctx->contextData.size;

            /* Get IP address */
            retval = -FAST_ERR_STC_IPADDR;
            if (! aipctx->ipInfo.address.address.buf)
                goto g_stc_free;
            fstc->fstc_ic[i].fic_ipa.fipa_addr = malloc(aipctx->ipInfo.address.address.size);
            retval = -FAST_ERR_STC_NOMEM;
            if (! fstc->fstc_ic[i].fic_ipa.fipa_addr)
                goto g_stc_free;
            memset(fstc->fstc_ic[i].fic_ipa.fipa_addr, 0, aipctx->ipInfo.address.address.size);
            memcpy(fstc->fstc_ic[i].fic_ipa.fipa_addr, aipctx->ipInfo.address.address.buf, aipctx->ipInfo.address.address.size);
            fstc->fstc_ic[i].fic_ipa.fipa_alen = aipctx->ipInfo.address.address.size;
            fstc->fstc_ic[i].fic_ipa.fipa_type = aipctx->ipInfo.address.addressType;
            retval = -FAST_ERR_STC_IPTYPE;
            if ( (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_udpIpv4) && (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_udpIpv6) &&
                    (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_tcpIpv4) && (fstc->fstc_ic[i].fic_ipa.fipa_type != AT_tcpIpv6) )
                goto g_stc_free;
        }
    }
    
    retval = 0;

g_stc_free:
    /* Free STC buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	asn_DEF_Stc.free_struct(&asn_DEF_Stc, astc, 0);
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    /* Free STC struct */
    if (retval)
        fstc_free(fstc);

    return retval;
}

#define FAST_MESSAGECOUNTER_MAX         31

#define FAST_REQUEST                    1
#define FAST_RESPONSE                   2

static int fast_create_rX(unsigned char * data, size_t dlen, uint8_t type, uint8_t ack, uint8_t msgc, unsigned char buf[], size_t blen)
{
    int retval = 0;

    struct Request req; 
    struct Response res;
    long * mc;
    struct OCTET_STRING * os;
    asn_TYPE_descriptor_t * td; 
    void * a;

    char errbuf[512];
    size_t errlen = 512;
    asn_enc_rval_t enc;
    unsigned char buffer[blen - sizeof(size_t)];
    size_t bufferlen = blen - sizeof(size_t);

    //struct asn_per_data_s * ds;
    size_t * nbits;

    /* Parameter checking */
    if ( (buf == NULL) || (blen < sizeof(size_t)) )
        return -FAST_ERR_RX_BUF;

    if (data == NULL)
        return -FAST_ERR_RX_BUF;

    if (msgc > FAST_MESSAGECOUNTER_MAX)
        return -FAST_ERR_RX_MSGCNT;

    /* Init */
    memset(&req, 0, sizeof(struct Request));
    memset(&res, 0, sizeof(struct Response));

    /* Setup msgtype */
    switch (type) {
        case FAST_REQUEST :
            if (ack)
                req.messageType = MessageType_reqNeedAck;
            else
                req.messageType = MessageType_reqNoAck;
            mc = &req.messageCounter;
            os = &req.data;
            td = &asn_DEF_Request;
            a = &req;
            break;
        case FAST_RESPONSE :
            res.messageType = MessageType_res;
            mc = &res.messageCounter;
            os = &res.data;
            td = &asn_DEF_Response;
            a = &res;
            break;
    }

    /* Setup msgCounter */
    *mc = msgc;

    /* Setup data */
    os->buf = malloc(dlen);
    if (! os->buf)
        return -FAST_ERR_RX_NOMEM;
    memset(os->buf, 0, dlen);
    memcpy(os->buf, data, dlen);
    os->size = dlen;

    retval = -FAST_ERR_RX_CONSTRAINTS;

    /* Check constraints */
   	if (__LIBFAST__asn_check_constraints(td, a, errbuf, &errlen)) {
		printf("Error in expression: %s\n", errbuf);
        goto c_rx_free;
	}
	
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- rX --- ---\n");
    __LIBFAST__xer_fprint(stdout, td, a);    
    fprintf(stdout, "\n--- --- rX done --- ---\n");
    #endif

    /* Encoding */
    memset(buffer, 0, bufferlen);
	enc = __LIBFAST__uper_encode_to_buffer(td, a, buffer, bufferlen);
	if (enc.encoded == -1) {
        retval = -FAST_ERR_RX_BLEN;
        if (errno == 0)
            goto c_rx_free;
        
        #ifdef LIBFAST_DEBUG                                                                           
		fprintf(stdout, "Can't encode: %s (%s)\n", enc.failed_type->name, strerror(errno));
        #endif
		retval = -FAST_ERR_RX_ENCODE;
        goto c_rx_free;
	}
    
    memset(buf, 0, blen);
    //ds = (struct asn_per_data_s *)buf;
    //ds->nboff = htonl(0),
    //ds->nbits = htonl(enc.encoded);
    //memcpy(ds + 1, buffer, bufferlen);
    nbits = (size_t *)buf;
    *nbits = htonl(enc.encoded);
    memcpy(nbits + 1, buffer, bufferlen);

    //retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(struct asn_per_data_s);
    retval = (enc.encoded / 8) + ((enc.encoded % 8) ? 1 : 0) + sizeof(size_t);

    #ifdef LIBFAST_DEBUG
    //printf("retval is %d, bufferlen is %d, nboff is %d, nbits is %d\n", retval, bufferlen, ds->nboff, ds->nbits);
    printf("retval is %d, bufferlen is %d, nbits is %d\n", retval, bufferlen, enc.encoded);
    #endif

c_rx_free:
    /* Free buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	td->free_struct(td, a, 1);
     #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    return retval;
}

static int fast_get_rX(unsigned char * data, size_t dlen, uint8_t type, uint8_t * ack, uint8_t * msgc, unsigned char buf[], size_t blen)
{
    int retval = 0;

    struct Request * req = NULL;
    struct Response * res = NULL;
    long * mc;
    struct OCTET_STRING * os;
    asn_TYPE_descriptor_t * td; 
    void * a;

    //struct asn_per_data_s * ds;
    struct asn_per_data_s ds_save;
    size_t * nbits;
    unsigned char * buffer;
    size_t bufferlen;
    asn_dec_rval_t dec;
    
    /* Parameter checking */
    if ( (buf == NULL) || (blen == 0) )
        return -FAST_ERR_RX_BUF;

    if (data == NULL)
        return -FAST_ERR_RX_BUF;

    /* Clear the struct */
    memset(data, 0, dlen);

    /* Type selection */
    switch (type) {
        case FAST_REQUEST :
            td = &asn_DEF_Request;
            a = req;
            break;
        case FAST_RESPONSE :
            td = &asn_DEF_Response;
            a = res;
            break;
    }

    /* Decoding */
    //ds = (struct asn_per_data_s *)buf;
    nbits = (size_t *)buf;
    buffer = (unsigned char *)(nbits + 1);
    bufferlen = blen - sizeof(size_t);
    //bufferlen = blen - sizeof(struct asn_per_data_s);
    //ds->buffer = buffer;
    
    #ifdef LIBFAST_DEBUG
    printf("blen is %d, bufferlen is %d, nbits is %d\n", blen, bufferlen, ntohl(*nbits));
    #endif

    if ( (ntohl(*nbits) > bufferlen * 8) || (ntohl(*nbits) < (bufferlen - 1) * 8) )
        return -FAST_ERR_STA_BUF;

    memset(&ds_save, 0, sizeof(ds_save));
    ds_save.nboff = 0;
    ds_save.nbits = ntohl(*nbits);
    ds_save.buffer = buffer;
   	dec = td->uper_decoder(0, td, NULL, (void**)&a, &ds_save);

	if (dec.code != RC_OK) {
		#ifdef LIBFAST_DEBUG
		switch(dec.code) {
			case RC_WMORE:
				printf("Decode error: There is more data expected than it is provided.\n");
				break;
			case RC_FAIL :
				printf("Decode error: General failure to decode the buffer. (Number of consumed bytes: %d / %d)\n", dec.consumed, blen);
				break;
			default:
				printf("Decode error: Unrecognized error code: %d.\n", dec.code);
		}
		#endif
		retval = -FAST_ERR_RX_DECODE;
        goto g_rx_free;
	}
	
	#ifdef LIBFAST_DEBUG
    fprintf(stdout, "--- --- rX --- ---\n");
	__LIBFAST__xer_fprint(stdout, td, a);
    fprintf(stdout, "--- --- rX done --- ---\n");
	#endif
 
    /* Test Message type */
    retval = -FAST_ERR_RX_MSGTYPE;
    switch (type) {
        case FAST_REQUEST :
            req = a;
            if ( (req->messageType != MessageType_reqNeedAck) && (req->messageType != MessageType_reqNoAck) )
                goto g_rx_free;
            if (ack) {
                if (req->messageType == MessageType_reqNeedAck)
                    *ack = 1;
                else
                    *ack = 0;
            }
            mc = &req->messageCounter;
            os = &req->data;
            break;
        case FAST_RESPONSE :
            res = a;
            if (res->messageType != MessageType_res)
                goto g_rx_free;
            mc = &res->messageCounter;
            os = &res->data;
            break;
    }

    /* Get message counter */
    if (msgc)
        *msgc = *mc;

    /* Get data */
    retval = -FAST_ERR_RX_DATA;
    if (! os->buf)
        goto g_rx_free;
    memcpy(data, os->buf, os->size);
    dlen = os->size;
   
    retval = dlen;

g_rx_free:
    /* Free buffer */
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing --- ---\n");
    #endif
	td->free_struct(td, a, 0);
    #ifdef LIBFAST_DEBUG                                                                           
    fprintf(stdout, "--- --- freeing done --- ---\n");
    #endif

    return retval;
}

int fast_create_req(unsigned char * data, size_t dlen, uint8_t ack, uint8_t msgc, unsigned char buf[], size_t blen)
{
    return fast_create_rX(data, dlen, FAST_REQUEST, ack, msgc, buf, blen);
}

int fast_get_req(unsigned char * data, size_t dlen, uint8_t * ack, uint8_t * msgc, unsigned char buf[], size_t blen)
{
    return fast_get_rX(data, dlen, FAST_REQUEST, ack, msgc, buf, blen);
}

int fast_create_resp(unsigned char * data, size_t dlen, uint8_t msgc, unsigned char buf[], size_t blen)
{
    return fast_create_rX(data, dlen, FAST_RESPONSE, 0, msgc, buf, blen);
}

int fast_get_resp(unsigned char * data, size_t dlen, uint8_t * msgc, unsigned char buf[], size_t blen)
{
    return fast_get_rX(data, dlen, FAST_RESPONSE, NULL, msgc, buf, blen);
}

#ifdef LIBFAST_TEST
int main()
{
    int ret;
    int i, j;

    #define MSGLEN  512
    unsigned char msg[MSGLEN];
    int mlen;

    struct fsta fsta, gsta;
    struct fipp * fipp;
    struct fs * fs;
    struct fis * fis;
    struct fch * fch;

    struct fstc fstc, gstc;
    struct fc * fc;
    struct fic * fic;

    #define DATALEN 100
    char data[DATALEN];
    uint8_t ack, msgc;

    memcpy(fsta.fsta_sid, "ABCD", 4);

    fsta.fsta_ipp = fipp = malloc(sizeof(struct fipp) * 2);
    fsta.fsta_ippnum = 2;

    fipp[0].fipp_addr = (unsigned char *)"::0";
    fipp[0].fipp_alen = 3;
    fipp[0].fipp_len = 64;
    
    fipp[1].fipp_addr = (unsigned char *)"1:1::0";
    fipp[1].fipp_alen = 6;
    fipp[1].fipp_len = 48;

    fsta.fsta_fs = fs = malloc(sizeof(struct fs) * 3);
    fsta.fsta_fsnum = 3;
    
    fs[0].fs_sid = 111;
    fs[0].fs_nwref = 11;
    fs[0].fs_data = (unsigned char *)"Hello CALM!";
    fs[0].fs_dlen =11;
    fs[0].fs_chid = 0;

    fs[1].fs_sid = 222;
    fs[1].fs_nwref = 22;
    fs[1].fs_data = NULL;
    fs[1].fs_dlen = 0;
    fs[1].fs_chid = 0;

    fs[2].fs_sid = 333;
    fs[2].fs_nwref = 255;
    fs[2].fs_data = (unsigned char *)"Libfast test data.";
    fs[2].fs_dlen = 18;
    fs[2].fs_chid = 1;

    fsta.fsta_is = fis = malloc(sizeof(struct fis) * 2);
    fsta.fsta_isnum = 2;

    fis[0].fis_sid = 555;
    fis[0].fis_data = (unsigned char *)"Hello CALM on IPv6!";
    fis[0].fis_dlen = 19;
    fis[0].fis_ipa.fipa_addr = (unsigned char *)"a:b:c:d::1";
    fis[0].fis_ipa.fipa_alen = 10;
    fis[0].fis_ipa.fipa_type = AT_udpIpv6;
    fis[0].fis_chid = 2;

    fis[1].fis_sid = 666;
    fis[1].fis_data = NULL;
    fis[1].fis_dlen = 0;
    fis[1].fis_ipa.fipa_addr = (unsigned char *)"e:f:g:h::2";
    fis[1].fis_ipa.fipa_alen = 10;
    fis[1].fis_ipa.fipa_type = AT_tcpIpv6;
    fis[1].fis_chid = 0;

    fsta.fsta_ch = fch = malloc(sizeof(struct fch) * 2);
    fsta.fsta_chnum = 2;

    fch[0].fch_id = 1;
    fch[0].fch_medtype = CALM_MED_21215;
    fch[0].fch_params = (unsigned char *)"do it!";
    fch[0].fch_plen = 6;

    fch[1].fch_id = 2;
    fch[1].fch_medtype = CALM_MED_21215;
    fch[1].fch_params = (unsigned char *)"do it!";
    fch[1].fch_plen = 6;

    ret = mlen = fast_create_sta(&fsta, msg, MSGLEN);
    printf("===> fast_create_sta returned with %d.\n", ret);
    free(fipp);
    free(fs);
    free(fis);
    free(fch);
    if (ret < 0)
        return 1;
    printf("===> Byte data: ");
    for (i = 1; i <= ret; i++) {
        printf("%02X ", msg[i-1]);
        if ( (i >= 20) && (i % 20 == 0) ) {
            printf("\n                ");
        }
    }
    printf("\n");

    ret = fast_get_sta(&gsta, msg, mlen);
    printf("===> fast_get_sta returned with %d.\n", ret);

    if (ret < 0)
        return 1;
    
    printf("Encoded STA:\n");
    printf("|-> ServerID: '%.4s'\n", gsta.fsta_sid);
    printf("|-> IP Prefixes (%d):\n", gsta.fsta_ippnum);
    for (i = 0; i < gsta.fsta_ippnum; i++)
        printf("|   |-> PrefixInfo: %.*s/%u\n", gsta.fsta_ipp[i].fipp_alen, gsta.fsta_ipp[i].fipp_addr, gsta.fsta_ipp[i].fipp_len); 
    printf("|-> FAST Services (%u):\n", gsta.fsta_fsnum);
    for (i = 0; i < gsta.fsta_fsnum; i++) {
        printf("|   |-> Service ID: %u\n", gsta.fsta_fs[i].fs_sid);
        if (gsta.fsta_fs[i].fs_data) {
            printf("|   ");
            if (i+1 != gsta.fsta_fsnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Service Data: '%.*s'\n", gsta.fsta_fs[i].fs_dlen, gsta.fsta_fs[i].fs_data);
        }
        if (gsta.fsta_fs[i].fs_nwref != 255) {
            printf("|   ");
            if (i+1 != gsta.fsta_fsnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Server NWref: %u\n", gsta.fsta_fs[i].fs_nwref);
        }
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
    }
    printf("|-> IP Services (%u):\n", gsta.fsta_isnum);
    for (i = 0; i < gsta.fsta_isnum; i++) {
        printf("    |-> Service ID: %u\n", gsta.fsta_is[i].fis_sid);
        if (gsta.fsta_is[i].fis_data) {
            printf("    ");
            if (i+1 != gsta.fsta_isnum)
                printf("|");
            else
                printf(" ");
            printf("   |-> Service Data: '%.*s'\n", gsta.fsta_is[i].fis_dlen, gsta.fsta_is[i].fis_data);
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

    fsta_free(&gsta);

    memcpy(fstc.fstc_sid, "EFGH", 4);

    fstc.fstc_ipp = fipp = malloc(sizeof(struct fipp) * 1);
    fstc.fstc_ippnum = 1;

    fipp[0].fipp_addr = (unsigned char *)"::2";
    fipp[0].fipp_alen = 3;
    fipp[0].fipp_len = 64;
    
    fstc.fstc_fc = fc = malloc(sizeof(struct fc) * 2);
    fstc.fstc_fcnum = 2;
    
    fc[0].fc_sid = 888;
    fc[0].fc_nwref = 99;
    fc[0].fc_data = (unsigned char *)"Greetings!";
    fc[0].fc_dlen = 10;

    fc[1].fc_sid = 777;
    fc[1].fc_nwref = 66;
    fc[1].fc_data = (unsigned char *)"Let's work!";
    fc[1].fc_dlen = 11;

    fstc.fstc_ic = fic = malloc(sizeof(struct fic) * 2);
    fstc.fstc_icnum = 2;

    fic[0].fic_sid = 55;
    fic[0].fic_data = NULL;
    fic[0].fic_dlen = 0;
    fic[0].fic_ipa.fipa_addr = (unsigned char *)"d:c:b:a::11";
    fic[0].fic_ipa.fipa_alen = 11;
    fic[0].fic_ipa.fipa_type = AT_udpIpv6;

    fic[1].fic_sid = 66;
    fic[1].fic_data = (unsigned char *)"Cheers!";
    fic[1].fic_dlen = 7;
    fic[1].fic_ipa.fipa_addr = (unsigned char *)"h:g:f:e::22";
    fic[1].fic_ipa.fipa_alen = 11;
    fic[1].fic_ipa.fipa_type = AT_tcpIpv6;

    ret = mlen = fast_create_stc(&fstc, msg, MSGLEN);
    printf("===> fast_create_stc returned with %d.\n", ret);
    free(fipp);
    free(fc);
    free(fic);
    if (ret < 0)
        return 1;
    printf("===> Byte data: ");
    for (i = 1; i <= ret; i++) {
        printf("%02X ", msg[i-1]);
        if ( (i >= 20) && (i % 20 == 0) ) {
            printf("\n                ");
        }
    }
    printf("\n");

    ret = fast_get_sta(&gsta, msg, mlen);
    printf("===> fast_get_sta with a stc returned with %d.\n", ret);

    if (! ret)
        return 1;

    ret = fast_get_stc(&gstc, msg, mlen);
    printf("===> fast_get_stc returned with %d.\n", ret);

    if (ret < 0)
        return 1;
    
    printf("Encoded STC:\n");
    printf("|-> ClientID: '%.4s'\n", gstc.fstc_sid);
    printf("|-> IP Prefixes (%d):\n", gstc.fstc_ippnum);
    for (i = 0; i < gstc.fstc_ippnum; i++)
        printf("|   |-> PrefixInfo: %.*s/%u\n", gstc.fstc_ipp[i].fipp_alen, gstc.fstc_ipp[i].fipp_addr, gstc.fstc_ipp[i].fipp_len); 
    printf("|-> FAST Contexts (%u):\n", gstc.fstc_fcnum);
    for (i = 0; i < gstc.fstc_fcnum; i++) {
        printf("|   |-> Service ID: %u\n", gstc.fstc_fc[i].fc_sid);
        printf("|   ");
        if (i+1 != gstc.fstc_fcnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> Context Data: '%.*s'\n", gstc.fstc_fc[i].fc_dlen, gstc.fstc_fc[i].fc_data);
        printf("|   ");
        if (i+1 != gstc.fstc_fcnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> User NWref: %u\n", gstc.fstc_fc[i].fc_nwref);
    }
    printf("|-> IP Services (%u):\n", gstc.fstc_icnum);
    for (i = 0; i < gstc.fstc_icnum; i++) {
        printf("    |-> Service ID: %u\n", gstc.fstc_ic[i].fic_sid);
        printf("    ");
        if (i+1 != gstc.fstc_icnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> Context Data: '%.*s'\n", gstc.fstc_ic[i].fic_dlen, gstc.fstc_ic[i].fic_data);
        printf("    ");
        if (i+1 != gstc.fstc_icnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> IP address type: ");
        switch(gstc.fstc_ic[i].fic_ipa.fipa_type) {
            case AT_udpIpv4 : printf("UDP & IPv4"); break;
            case AT_udpIpv6 : printf("UDP & IPv6"); break;
            case AT_tcpIpv4 : printf("TCP & IPv4"); break;
            case AT_tcpIpv6 : printf("TCP & IPv6"); break;
        }
        printf("\n");
        printf("    ");
        if (i+1 != gstc.fstc_icnum)
            printf("|");
        else
            printf(" ");
        printf("   |-> IP address: %.*s\n", gstc.fstc_ic[i].fic_ipa.fipa_alen, gstc.fstc_ic[i].fic_ipa.fipa_addr);
    }

    fstc_free(&gstc);

    ret = fast_create_req((unsigned char *)"Request a beer!", 15, 0, 1, msg, MSGLEN);
    printf("===> fast_create_req returned with %d.\n", ret);
    if (ret < 0)
        return 1;
    printf("===> Byte data: ");
    for (i = 1; i <= ret; i++) {
        printf("%02X ", msg[i-1]);
        if ( (i >= 20) && (i % 20 == 0) ) {
            printf("\n                ");
        }
    }
    printf("\n");

    ret = fast_get_req((unsigned char *)data, DATALEN, &ack, &msgc, msg, ret);
    printf("===> fast_get_req returned with %d.\n", ret);

    if (ret < 0)
        return 1;
    
    printf("Request: '%.*s'\n", ret, data);
    printf("|-> Need ack: %s\n", (ack) ? "yes" : "no");
    printf("|-> Message counter: %u\n", msgc);

    ret = fast_create_req((unsigned char *)"Request a pizza!", 16, 1, 2, msg, MSGLEN);
    printf("===> fast_create_req returned with %d.\n", ret);
    if (ret < 0)
        return 1;
    printf("===> Byte data: ");
    for (i = 1; i <= ret; i++) {
        printf("%02X ", msg[i-1]);
        if ( (i >= 20) && (i % 20 == 0) ) {
            printf("\n                ");
        }
    }
    printf("\n");

    ret = fast_get_req((unsigned char *)data, DATALEN, &ack, &msgc, msg, ret);
    printf("===> fast_get_req returned with %d.\n", ret);

    if (ret < 0)
        return 1;
    
    printf("Request with acknowledge: '%.*s'\n", ret, data);
    printf("|-> Need ack: %s\n", (ack) ? "yes" : "no");
    printf("|-> Message counter: %u\n", msgc);

    ret = fast_create_resp((unsigned char *)"It's OK.", 8, 3, msg, MSGLEN);
    printf("===> fast_create_resp returned with %d.\n", ret);
    if (ret < 0)
        return 1;
    printf("===> Byte data: ");
    for (i = 1; i <= ret; i++) {
        printf("%02X ", msg[i-1]);
        if ( (i >= 20) && (i % 20 == 0) ) {
            printf("\n                ");
        }
    }
    printf("\n");

    ret = fast_get_resp((unsigned char *)data, DATALEN, &msgc, msg, ret);
    printf("===> fast_get_resp returned with %d.\n", ret);

    if (ret < 0)
        return 1;
    
    printf("Response: '%.*s'\n", ret, data);
    printf("|-> Message counter: %u\n", msgc);

    return 0;
}
#endif

