#ifndef __CONN_QUEUE_H
#define __CONN_QUEUE_H

#include <conn.h>

struct conn_queue {
	struct conn *cq_first;
	struct conn *cq_last;
	int cq_num;
};

struct conn_queue *conn_queue_new(void);
void conn_queue_put(struct conn_queue *connq, struct conn *conn);
struct conn *conn_queue_get(struct conn_queue *connq);
void conn_queue_free(struct conn_queue *connq);

#endif

