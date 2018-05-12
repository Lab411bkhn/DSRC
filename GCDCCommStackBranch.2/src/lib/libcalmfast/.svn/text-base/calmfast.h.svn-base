#ifndef _CALMFAST_H_
#define _CALMFAST_H_

#include <unistd.h>

typedef enum CF_STATE {
	CF_CLOSED = 0,
	CF_OPENING,
	CF_OPEN,
	CF_CLOSING
} CF_STATE;

typedef struct CF_server {
	int			socket;
	long			serial;
	CF_STATE		state;
	struct CF_server	*next;
	unsigned char		*buffer;
	unsigned int		size;
	unsigned char		*cursor;
} CF_server;

typedef struct CF_client {
	int			socket;
	long			serial;
	CF_STATE		state;
	struct CF_client	*next;
	unsigned char		*buffer;
	unsigned int		size;
	unsigned char		*cursor;
} CF_client;

typedef struct CF_client_cb {
	int (* recv)(CF_client *client, char *fromurl, unsigned char *data, size_t size);
	int (* service)(CF_client *client, char *servurl, unsigned char *data, size_t size);
	int (* fault)(CF_client *client, char *txt);
} CF_client_cb;

typedef struct CF_server_cb {
	int (* open)(CF_server *server, int sid, char **serverurl);
	int (* close)(CF_server *server);
	int (* send)(CF_server *server, char *tourl, unsigned char *data, size_t size);
	int (* publish)(CF_server *server, unsigned char *data, size_t size, long interval);
	int (* unpublish)(CF_server *server);
	int (* monitor)(CF_server *server);
	int (* unmonitor)(CF_server *server);
} CF_server_cb;

/****** Client side API ******/

/* The cf_connect call will block until the connection is established */
extern CF_client	*cf_connect(char *servername, int port);
extern void		cf_disconnect(CF_client *client);

/* These calls will send data to the CF_client socket, and will block if the socket is not ready */
extern int cf_open(CF_client *client, int sid);
extern int cf_close(CF_client *client);
extern int cf_send(CF_client *client, char *url, unsigned char *data, size_t size);
extern int cf_publish(CF_client *client, unsigned char *data, size_t size, int interval);
extern int cf_unpublish(CF_client *client);

/* These calls will read data from the CF_client socket, and will block if the socket is not ready */
extern int cf_recv(CF_client *client, CF_client_cb *cb);

extern int listen_socket(int listen_port);
extern CF_server *cf_accept(int lsock);
extern void cf_dispose(CF_server *server);
extern int cf_recvserver(CF_server *server, CF_server_cb *cb);
extern int cf_sendserver(CF_server *server, char *fromurl, unsigned char *data, size_t size);
extern int cf_service(CF_server *server, char *fromurl, unsigned char *data, size_t size);

#endif
