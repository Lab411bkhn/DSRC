#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "calmfast.h"

#include "RequestMessage.h"
#include "ReplyMessage.h"

#define BUFFERSIZE	2048

/****** Support functions ******/

static int sendRequestMessage(CF_client *client, RequestMessage_t *msg)
{
    asn_enc_rval_t	ec;      /* Encoder return value  */
    int			result = 0;

    int write_out(const void *encdata, size_t size, void *app_key)
    {
	int		res;
	int		sent = 0;
	unsigned char	*data = (unsigned char *) encdata;

	while (sent < size) {
	    res = send(client->socket, &data[sent], size - sent, MSG_NOSIGNAL | MSG_DONTWAIT);
	    if (res <= 0) {
		return -1;
	    }
	    sent += res;
	    result += res;
	}
	return sent;
    }

    msg->serial = client->serial++;
    ec = der_encode(&asn_DEF_RequestMessage, msg, write_out, 0);
    if (ec.encoded == -1) {
	fprintf(stderr, "Could not encode RequestMessage (at %s)\n",
		  ec.failed_type ? ec.failed_type->name : "unknown");
	return -1;
    }

    return result;
}

static int sendReplyMessage(CF_server *server, ReplyMessage_t *msg)
{
    asn_enc_rval_t	ec;      /* Encoder return value  */
    int			result = 0;

    int write_out(const void *encdata, size_t size, void *app_key)
    {
	int		res;
	int		sent = 0;
	unsigned char	*data = (unsigned char *) encdata;

	while (sent < size) {
	    res = send(server->socket, &data[sent], size - sent, MSG_NOSIGNAL | MSG_DONTWAIT);
	    if (res <= 0) {
		return -1;
	    }
	    sent += res;
	    result += res;
	}
	return sent;
    }

    msg->serial = server->serial++;
    ec = der_encode(&asn_DEF_ReplyMessage, msg, write_out, 0);
    if (ec.encoded == -1) {
	fprintf(stderr, "Could not encode ReplyMessage (at %s)\n",
		  ec.failed_type ? ec.failed_type->name : "unknown");
	return -1;
    }
    fprintf(stderr, "Message sent OK\n");

    return result;
}


/****** Client side API ******/

/* The cf_connect call will block until the connection is established */

CF_client *cf_connect(char *servername, int port)
{
    struct sockaddr_in	addr;
    int			sock;
    CF_client		*result = NULL;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("cf_connect socket()");
        close (sock);
        return result;
    }

    memset (&addr, 0, sizeof (addr));
    addr.sin_port = htons (port);
    addr.sin_family = AF_INET;

    if (!inet_aton(servername, (struct in_addr *) &addr.sin_addr.s_addr)) {
        perror ("bad IP address format");
        close (sock);
        return result;
    }

    if (connect(sock, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
        perror ("cf_connect connect()");
        close (sock);
        return result;
    }

    result = calloc(1, sizeof(CF_client));
    if (result == NULL) {
	perror("cf_connect calloc()");
	close(sock);
	return result;
    }

    result->socket = sock;
    result->buffer = calloc(1, BUFFERSIZE);
    if (result->buffer == NULL) {
	perror("cf_connect calloc()");
	close(sock);
	free(result);
	return NULL;
    }
    result->cursor = result->buffer;

    return result;
}

void cf_disconnect(CF_client *client)
{
    if (client == NULL) {
	return;
    }

    close(client->socket);
    free(client->buffer);
    free(client);
}


/* These calls will send data to the CF_client socket, and will block if the socket is not ready */

int cf_open(CF_client *client, int sid)
{
    RequestMessage_t	msg;
    int			result;

    if (client == NULL || sid < 0 || client->socket < 0) {
	return -1;
    }

    if (client->state != CF_CLOSED) {
	return -1;
    }

    msg.payload.present = RequestMessage__payload_PR_open;
    msg.payload.choice.open.sid = sid;

    result = sendRequestMessage(client, &msg);
    if (result < 0) {
	return -1;
    }

    client->state = CF_OPENING;
    return result;
}

int cf_close(CF_client *client)
{
    RequestMessage_t	msg;
    int			result;

    if (client == NULL || client->socket < 0) {
	return -1;
    }

    if (client->state == CF_CLOSED) {
	return 0;
    }

    msg.payload.present = RequestMessage__payload_PR_close;

    result = sendRequestMessage(client, &msg);
    if (result < 0) {
	return -1;
    }

    client->state = CF_CLOSING;
    return result;
}

int cf_send(CF_client *client, char *url, unsigned char *data, size_t size)
{
    RequestMessage_t	msg;

    if (client == NULL || url == NULL || client->socket < 0) {
	return -1;
    }

    if (client->state != CF_OPEN) {
	return -1;
    }

    msg.payload.present = RequestMessage__payload_PR_send;
    msg.payload.choice.send.url.buf = (unsigned char *) url;
    msg.payload.choice.send.url.size = strlen(url);
    msg.payload.choice.send.data.buf = data;
    msg.payload.choice.send.data.size = size;

    return sendRequestMessage(client, &msg);
}

int cf_publish(CF_client *client, unsigned char *data, size_t size, int interval)
{
    RequestMessage_t	msg;

    if (client == NULL || client->socket < 0) {
	return -1;
    }

    if (client->state != CF_OPEN) {
	return -1;
    }

    msg.payload.present = RequestMessage__payload_PR_publish;
    msg.payload.choice.publish.data.buf = data;
    msg.payload.choice.publish.data.size = size;
    msg.payload.choice.publish.interval = interval;

    return sendRequestMessage(client, &msg);
}

int cf_unpublish(CF_client *client)
{
    RequestMessage_t	msg;

    if (client == NULL || client->socket < 0) {
	return -1;
    }

    if (client->state != CF_OPEN) {
	return -1;
    }

    msg.payload.present = RequestMessage__payload_PR_unpublish;

    return sendRequestMessage(client, &msg);
}


/* These calls will read data from the CF_client socket, if no more data is available -1 is returned.
 * On a successful packet reception with data the callback function is called.
 */

int cf_recv(CF_client *client, CF_client_cb *cb)
{
    asn_dec_rval_t	rc;
    ReplyMessage_t	*rpy = NULL;
    int			result = -1;
    int			rval;
    int			needmore = (client->size == 0);
    char		*txtbuf;

    do {
	if (client == NULL || client->socket < 0) {
	    return -1;
	}

	if (needmore) {
	    rval = recv(client->socket, client->cursor, BUFFERSIZE - (client->cursor - client->buffer), MSG_DONTWAIT);
	    if (rval < 0 && errno == EAGAIN) {
		return -1;
	    }
	    if (rval <= 0) {
		close(client->socket);
		client->socket = -1;
		return -1;
	    }
	    client->size += rval;
	}

	/* client->size at this point is > 0, now try to decode the message */
	rc = ber_decode(0, &asn_DEF_ReplyMessage, (void **) &rpy, client->cursor, client->size);
	switch(rc.code) {
	    case RC_OK:
		client->size -= rc.consumed;
		if (client->size <= 0) {
		    /* used up the buffer, reset it and request for more data */
		    client->size = 0;
		    client->cursor = client->buffer;
		    needmore = 1;
		} else {
		    client->cursor += rc.consumed;
		}
		switch(rpy->payload.present) {
		    case ReplyMessage__payload_PR_msg:
			if (client->state == CF_OPEN) {
			    txtbuf = calloc(1, rpy->payload.choice.msg.url.size + 1);
			    if (txtbuf != NULL) {
				strncpy(txtbuf, (char *) rpy->payload.choice.msg.url.buf, rpy->payload.choice.msg.url.size);
				result = cb->recv(client, txtbuf,
					      rpy->payload.choice.msg.data.buf, rpy->payload.choice.msg.data.size);
				free(txtbuf);
			    }
			}
			break;
		    case ReplyMessage__payload_PR_openack:
			if (client->state == CF_OPENING) {
			    client->state = CF_OPEN;
			}
			break;
		    case ReplyMessage__payload_PR_closeack:
			if (client->state == CF_CLOSING) {
			    client->state = CF_CLOSED;
			}
			break;
		    case ReplyMessage__payload_PR_fault:
			txtbuf = calloc(1, rpy->payload.choice.fault.msg.size + 1);
			if (txtbuf != NULL) {
			    strncpy(txtbuf, (char *) rpy->payload.choice.fault.msg.buf, rpy->payload.choice.fault.msg.size);
			    result = cb->fault(client, txtbuf);
			    free(txtbuf);
			}
			close(client->socket);
			client->socket = -1;
			break;
		    default:
			break;
		    }
		break;
	    case RC_WMORE:
		/* cannot decode because more data is required */
		needmore = 1;
		break;
	    default:
		/* some kind of error, close the socket */
		close(client->socket);
		client->socket = -1;
		break;
	}
	asn_DEF_ReplyMessage.free_struct (&asn_DEF_ReplyMessage, rpy, 0);
    } while (result < 0);

    return result;
}



/****** Server side API ******/

int listen_socket(int listen_port)
{
    struct sockaddr_in a;
    int s;
    int yes;
    if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket");
        return -1;
    }
    yes = 1;
    if (setsockopt
        (s, SOL_SOCKET, SO_REUSEADDR,
         (char *) &yes, sizeof (yes)) < 0) {
        perror ("setsockopt");
        close (s);
        return -1;
    }
    memset (&a, 0, sizeof (a));
    a.sin_port = htons (listen_port);
    a.sin_family = AF_INET;
    if (bind
        (s, (struct sockaddr *) &a, sizeof (a)) < 0) {
        perror ("bind");
        close (s);
        return -1;
    }
    printf ("accepting connections on port %d\n",
            (int) listen_port);
    listen (s, 10);
    return s;
}

CF_server *cf_accept(int lsock)
{
    struct sockaddr_in	client_address;
    unsigned int	cal = sizeof (client_address);
    int			asock;
    CF_server		*result = NULL;

    memset (&client_address, 0, cal);
    asock = accept (lsock, (struct sockaddr *) &client_address, &cal);
    if (asock < 0) {
	perror ("cf_accept accept()");
	return NULL;
    }
    printf ("connect from %s\n", inet_ntoa (client_address.sin_addr));

    result = calloc(1, sizeof(CF_server));
    if (result == NULL) {
	perror("cf_accept calloc()");
	close(asock);
	return result;
    }

    result->socket = asock;
    result->buffer = calloc(1, BUFFERSIZE);
    if (result->buffer == NULL) {
	perror("cf_accept calloc()");
	close(asock);
	free(result);
	return NULL;
    }
    result->cursor = result->buffer;

    return result;
}

void cf_dispose(CF_server *server)
{
    if (server == NULL) {
	return;
    }

    close(server->socket);
    free(server->buffer);
    free(server);
}

int cf_recvserver(CF_server *server, CF_server_cb *cb)
{
    asn_dec_rval_t	rc;
    RequestMessage_t	*req = NULL;
    int			result = 1;
    int			rval;
    int			needmore = (server->size == 0);
    ReplyMessage_t	rpy;
    char		*serverurl = NULL;
    const char		*faultmsg;

    do {
	if (server == NULL || server->socket < 0) {
	    return -1;
	}

	if (needmore) {
	    rval = recv(server->socket, server->cursor, BUFFERSIZE - (server->cursor - server->buffer), MSG_DONTWAIT);
	    if (rval < 0 && errno == EAGAIN) {
		return 0;
	    }
	    if (rval <= 0) {
		perror("recv");
		close(server->socket);
		server->socket = -1;
		return -1;
	    }
	    server->size += rval;
	}

	/* server->size at this point is > 0, now try to decode the message */
	rc = ber_decode(0, &asn_DEF_RequestMessage, (void **) &req, server->cursor, server->size);
	switch(rc.code) {
	    case RC_OK:
		server->size -= rc.consumed;
		if (server->size <= 0) {
		    /* used up the buffer, reset it and request for more data */
		    server->size = 0;
		    server->cursor = server->buffer;
		    needmore = 1;
		} else {
		    server->cursor += rc.consumed;
		}
		switch(req->payload.present) {
		    case RequestMessage__payload_PR_open:
			result = cb->open(server, req->payload.choice.open.sid, (char **) &serverurl);
			if (result >= 0) {
			    rpy.payload.present = ReplyMessage__payload_PR_openack;
			    if (serverurl != NULL) {
				rpy.payload.choice.openack.url.buf = (unsigned char *) serverurl;
				rpy.payload.choice.openack.url.size = strlen(serverurl);
			    } else {
				rpy.payload.choice.openack.url.buf = (unsigned char *) "";
				rpy.payload.choice.openack.url.size = 0;
			    }
			} else {
			    faultmsg = "Open failed";
			    rpy.payload.present = ReplyMessage__payload_PR_fault;
			    rpy.payload.choice.fault.msg.buf = (unsigned char *) faultmsg;
			    rpy.payload.choice.fault.msg.size = strlen(faultmsg);
			}
			sendReplyMessage(server, &rpy);
			break;
		    case RequestMessage__payload_PR_close:
			result = cb->close(server);
			if (result >= 0) {
			    rpy.payload.present = ReplyMessage__payload_PR_closeack;
			    rpy.payload.choice.closeack.data = 0;
			} else {
			    faultmsg = "Close failed";
			    rpy.payload.present = ReplyMessage__payload_PR_fault;
			    rpy.payload.choice.fault.msg.buf = (unsigned char *) faultmsg;
			    rpy.payload.choice.fault.msg.size = strlen(faultmsg);
			}
			sendReplyMessage(server, &rpy);
			break;
		    case RequestMessage__payload_PR_send:
			result = cb->send(server, (char *) req->payload.choice.send.url.buf,
					  req->payload.choice.send.data.buf, req->payload.choice.send.data.size);
			break;
		    case RequestMessage__payload_PR_publish:
			result = cb->publish(server, req->payload.choice.publish.data.buf, req->payload.choice.publish.data.size,
					     req->payload.choice.publish.interval); 
			break;
		    case RequestMessage__payload_PR_unpublish:
			result = cb->unpublish(server); 
			break;
		    case RequestMessage__payload_PR_monitor:
			result = cb->monitor(server); 
			break;
		    case RequestMessage__payload_PR_unmonitor:
			result = cb->unmonitor(server); 
			break;
		    default:
			break;
		}
		asn_DEF_RequestMessage.free_struct (&asn_DEF_RequestMessage, req, 0);
		req = NULL;
		break;
	    case RC_WMORE:
		/* cannot decode because more data is required */
		needmore = 1;
		break;
	    default:
		/* some kind of error, close the socket */
		result = -1;
		break;
	}
	needmore = (server->size == 0);
    } while (result > 0);

    close(server->socket);
    server->socket = -1;

    return result;
}

int cf_sendserver(CF_server *server, char *fromurl, unsigned char *data, size_t size)
{
    ReplyMessage_t	rpy;

    if (server == NULL || server->socket < 0) {
	return -1;
    }

    rpy.payload.present = ReplyMessage__payload_PR_msg;
    rpy.payload.choice.msg.url.buf = (unsigned char *) fromurl;
    rpy.payload.choice.msg.url.size = strlen(fromurl);
    rpy.payload.choice.msg.data.buf = data;
    rpy.payload.choice.msg.data.size = size;
    return sendReplyMessage(server, &rpy);
}

int cf_service(CF_server *server, char *fromurl, unsigned char *data, size_t size)
{
    ReplyMessage_t	rpy;

    if (server == NULL || server->socket < 0) {
	return -1;
    }

    rpy.payload.present = ReplyMessage__payload_PR_service;
    rpy.payload.choice.service.url.buf = (unsigned char *) fromurl;
    rpy.payload.choice.service.url.size = strlen(fromurl);
    rpy.payload.choice.service.data.buf = data;
    rpy.payload.choice.service.data.size = size;
    return sendReplyMessage(server, &rpy);
}


#ifdef LIBCALMFAST_TEST

static int test_open(CF_server *server, int sid, char **serverurl)
{
    printf("Open sid=%d\n", sid);
    *serverurl = "fast://url";
    return 1;
}

static int test_close(CF_server *server)
{
    printf("Close\n");
    return 1;
}

static int test_send(CF_server *server, char *tourl, unsigned char *data, size_t size)
{
    printf("Send url=%s, datasize=%d\n", tourl, size);
    return 1;
}

static int test_publish(CF_server *server, unsigned char *data, size_t size, long interval)
{
    printf("Publish datasize=%d, interval=%ld\n", size, interval);
    return 1;
}

static int test_unpublish(CF_server *server)
{
    printf("Unpublish\n");
    return 1;
}


int main(int argc, char *argv[])
{
    CF_server_cb	tcb = {
	.open = test_open,
	.close = test_close,
	.send = test_send,
	.publish = test_publish,
	.unpublish = test_unpublish
    };

    int			lsock = -1;
    CF_server		*server = NULL;
    fd_set		rfds;
    struct timeval	tv;
    int			retval;
    int			fdmax = 0;

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

    lsock = listen_socket(1234);

    while (lsock >= 0) {
	tv.tv_sec = 0;
	tv.tv_usec = 100000;

	fd_start();
	fd_add(lsock);
	if (server != NULL) {
	    fd_add(server->socket);
	}
	retval = select(fdmax, &rfds, NULL, NULL, &tv);
	if (retval == -1) {
	    perror("select");
	    close(lsock);
	    lsock = -1;
	    continue;
	}

	if (retval == 0 && server != NULL) {
	    unsigned char indata[] = { 6, 8, 9, 0 };

	    fprintf(stderr, "Sending data\n");
	    cf_sendserver(server, "fast://incoming", indata, sizeof(indata));
	}
	if (server != NULL && FD_ISSET(server->socket, &rfds)) {
	    if (cf_recvserver(server, &tcb) < 0 || server->socket < 0) {
		fprintf(stderr, "Disposing of server connection\n");
		cf_dispose(server);
		server = NULL;
	    }
	}

	if (FD_ISSET(lsock, &rfds)) {
	    server = cf_accept(lsock);
	}

    }

    exit(0);

}

#endif
