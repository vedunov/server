#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/poll.h>
#include <server.h>
#include <packet.h>

struct server {
	struct conn_queue *cq_conn;
	struct packet_queue *pq_client;
	int listen_fd;
	int ctl_fd;
	int bquit;
} srv ;

void init_server(struct server *srv)
{
	srv->cq_conn = conn_queue_new();
	srv->pq_client = packet_queue_new();
	srv->ctl_fd = open_user_chan();
	srv->bquit = 0;
}

void destroy_server(struct server *srv)
{
	conn_queue_free(srv->cq_conn);
	packet_queue_free(srv->pq_client);
	close_user_chan(srv->ctl_fd);
}

int open_user_chan(void)
{
	if (mkfifo(FIFO_FILE, O_CREAT | O_EXCL | S_IRUSR | S_IWGRP) == -1)
		return -1;
	return open(FIFO_FILE, O_RDONLY | O_NONBLOCK);
}

int close_user_chan(int ctl_fd)
{
	close(ctl_fd);
	unlink(FIFO_FILE);
}

int reopen_user_chan(int ctl_fd)
{
	close(ctl_fd);
	return open(FIFO_FILE, O_RDONLY | O_NONBLOCK);
}

void process_conns(void)
{
}

void process_client_reqs(void)
{
}

void process_user_reqs(struct pollfd *pfd, int *ctl_fd)
{
	if (pfd->revents & POLLHUP) {
		*ctl_fd = reopen_user_chan(*ctl_fd);
		return;
	}
	struct packet *pkt = packet_new();
	int n;
	n = read(pfd->fd, pkt->pkt_data, PKT_BUFF_SIZE);
	if (n == 0)
		*ctl_fd = reopen_user_chan(*ctl_fd);
	printf("read %d bytes from user\n", n);
}

int serve(struct server *srv)
{
	const static int CONTROL_PFD = 0;
	struct pollfd pfd[1];
	memset(&pfd, 0, sizeof(pfd));

	pfd[CONTROL_PFD].fd = srv->ctl_fd;
	pfd[CONTROL_PFD].events = POLLIN;

	while (! srv->bquit) {
		int n = poll(pfd, sizeof(pfd)/sizeof(struct pollfd), -1);
		if (n < 0) {
			fprintf(stderr, "poll error\n");
			return -1;
		}
		else if (n == 0) {
		}
		else {
			process_conns();
			process_client_reqs();
			process_user_reqs(&pfd[CONTROL_PFD], &pfd[CONTROL_PFD].fd);
		}
	}
}

void on_sigint(int signo)
{
	srv.bquit = 1;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, on_sigint);
	init_server(&srv);
	serve(&srv);
	destroy_server(&srv);
	return 0;
}
