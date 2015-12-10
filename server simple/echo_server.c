#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants
#include <stdio.h> //ISO C99 Standard: 7.19 Input/output
#include <stdlib.h> //ISO C99 Standard: 7.20 General utilities
#include <math.h> //ISO C99 Standard: 7.12 Mathematics
#include <errno.h> //ISO C99 Standard: 7.5 Errors
#include <netinet/in.h> //Standard well-defined IP protocols
#include <string.h> //original is strings.h I changed to string.h. ISO C99 Standard: 7.21 String handling
#include "ev.h"

#define PORT 8333
#define BUFFER_SIZE 1024

//gcc -o echo_server echo_server.c -lm ev.o

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	char buffer[BUFFER_SIZE];
	ssize_t read;
	
	if(EV_ERROR & revents) {
		printf("error event in read\n");
		return;
	}
	
	read = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
	if(read < 0) {
		perror("read error: ");
		return;
	}
	
	if(read == 0) {
		perror("some one disconnected : ");
		ev_io_stop(loop, watcher);
		free(watcher);
		return;
	}
	
	printf("get the message : %s\n", buffer);
	send(watcher->fd, buffer, read, 0);
	bzero(buffer, read);	
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	//Structure describing an Internet socket address
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_sd;
	
	struct ev_io *w_client = (struct ev_io *)malloc(sizeof(struct ev_io));
	if(w_client == NULL) {
		printf("error event in accept\n");
		return;
	}
	
	client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);
	if(client_sd < 0) {
		printf("accept error\n");
		return;
	}
	
	printf("some one connected.\n");
	
	ev_io_init(w_client, read_cb, client_sd, EV_READ);
	ev_io_start(loop, w_client);	
}

static void timeout_cb(struct ev_loop *loop, ev_timer *w, int revents)
{
	puts("timeout");
}

int main()
{
	struct ev_loop *loop = ev_default_loop(0);
	int sd;
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	struct ev_io socket_watcher;
	ev_timer timeout_watcher;
	
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if(sd < 0) {
		perror("socket error : ");
		return -1;
	}
	
	bzero(&addr, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sd, (struct sockaddr *)&addr, addr_len) != 0) {
		perror("bind error : ");
		return -1;
	}
	
	if(listen(sd, 2) < 0) {
		printf("listen error\n");
		return -1;
	}
	
	printf("ev_loop begin\n");
	
	ev_io_init(&socket_watcher, accept_cb, sd, EV_READ);
	ev_io_start(loop, &socket_watcher);
	
	ev_timer_init(&timeout_watcher, timeout_cb, 2, 1);
	ev_timer_start(loop, &timeout_watcher);
	
	while(1) {
		printf("ev_loop\n");
		ev_loop(loop, 0);
	}
	
	return 0;
	
	
	
	
}

