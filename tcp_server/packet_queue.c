#include <packet_queue.h>
#include <stdlib.h>

struct packet_queue *packet_queue_new(void)
{
	return (struct packet_queue *)calloc(1, sizeof(struct packet_queue));
}

void packet_queue_put(struct packet_queue *pktq, struct packet *pkt)
{
	if (pktq->pq_num == 0) {
		pktq->pq_first = pkt;
		pktq->pq_last = pkt;
	}
	pktq->pq_last->pq_prev = pkt;
	pkt->pq_prev = NULL;
	pkt->pq_next = pktq->pq_last;
	pktq->pq_last = pkt;
	pktq->pq_num++;
}

struct packet *packet_queue_get(struct packet_queue *pktq)
{
	struct packet *last = pktq->pq_last;
	if (pktq->pq_num == 0)
		return NULL;
	last->pq_prev->pq_next = NULL;
	last->pq_prev = last->pq_next = NULL;
	pktq->pq_num--;
	return last;
}

void packet_queue_free(struct packet_queue *pktq)
{
	int i;
	if (pktq->pq_num == 0)
		return;
	for (i = 0; i < pktq->pq_num; i++) {
		struct packet *pkt = pktq->pq_last;
		pktq->pq_last = pkt->pq_next;
		packet_free(pkt);
	}
}
