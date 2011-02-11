#ifndef __PACKET_QUEUE_H
#define __PACKET_QUEUE_H

#include <packet.h>

struct packet_queue {
	struct packet *pq_first;
	struct packet *pq_last;
	int pq_num;
};

struct packet_queue *packet_queue_new(void);
void packet_queue_put(struct packet_queue *pktq, struct packet *pkt);
struct packet *packet_queue_get(struct packet_queue *pktq);
void packet_queue_free(struct packet_queue *pktq);

#endif
