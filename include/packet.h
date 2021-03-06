#ifndef __PACKET_H
#define __PACKET_H

#include <stdint.h>
#define PKT_BUFF_SIZE 256
struct packet {
	char pkt_data[PKT_BUFF_SIZE];
	int pkt_pos;
	struct packet *pq_next;
	struct packet *pq_prev;
};

struct packet *packet_new(void);
void packet_free(struct packet *pkt);
int packet_set(struct packet *pkt, char *buf, int num);

#endif
