#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <pthread.h>

#include "queue.h"
#include "message.h"


#define SIZE_BUFFER		sizeof(msg_t)
#define T_BUFFER_CHECK	0.1


static void usage(void) {
    fprintf(stderr, "\n"
		"usage: client [-h] [options]"
		"\n"
		"options:\n"
		"    -h  show this message\n"
		"    -d  ipv4 address of server (default: 155.230.107.136)\n"
		"    -p  port number of server (default: 9734)\n"
		"\n"
	);
	exit(1);
}

queue tx_buffer, rx_buffer;

typedef struct _client_cfg_t {
	int sockfd;
} client_cfg_t;

typedef struct _client_arg_t {
	int sockfd;
} client_arg_t;

void init_client(client_cfg_t *client_cfg, char *ipv4_address, int port_number);
void run_client(client_cfg_t *client_cfg);

void get_msg_from_buffer(queue *buffer, msg_t *msg);
void push_msg_to_buffer(queue *buffer, msg_t *msg);

void *transmit(void *arg);
void *receive(void *arg);
void *process(void *arg);

#endif // CLIENT_H