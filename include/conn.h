#ifndef __CONN_H
#define __CONN_H

#include <stdint.h>

enum conn_state {
	CONN_ST_RCV = 1,
	CONN_ST_SND = 2
};

struct conn {
	int cn_fd;
	uint32_t cn_id;
	int cn_state;
	struct packet_queue *pq_rcv;
	struct packet_queue *pq_snd;
	struct conn *cq_next;
	struct conn *cq_prev;
};

struct conn *conn_new(void);
void conn_free(struct conn *conn);

#endif
