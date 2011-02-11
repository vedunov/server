#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <server.h>
#include <packet.h>


enum error_tags { ERR_OPENCHAN = 1, ERR_WRITECHAN, ERR_LAST };
struct error {
	char desc[32];
} errors[ERR_LAST] = { [ERR_OPENCHAN] = { "Error opening channel" },
		       [ERR_WRITECHAN] = { "Error write channel" } };

void msg_exit(int error)
{
	fprintf(stderr, "%s\n", errors[error].desc);
	exit(error);
}

int open_user_chan(void)
{
	return open(FIFO_FILE, O_WRONLY | O_NONBLOCK);
}

void close_user_chan(int fd)
{
	close(fd);
}

int write_user_chan(int fd, struct packet *pkt)
{
	int n = write(fd, pkt->pkt_data, pkt->pkt_pos);
	return n;
}

int main(int argc, char *argv[])
{
	int n;
	int fd = open_user_chan();

	if (fd == -1)
		msg_exit(ERR_OPENCHAN);
	struct packet *pkt = packet_new();
	packet_set(pkt, "Hello", 5);
	n = write_user_chan(fd, pkt);

	close_user_chan(fd);

	return n;
}
