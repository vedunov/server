#include <conn.h>
#include <conn_queue.h>
#include <stdlib.h>

struct conn_queue *conn_queue_new(void)
{
	struct conn_queue *connq;
	connq = (struct conn_queue *)calloc(1, sizeof(struct conn_queue));
	return connq;
}

void conn_queue_put(struct conn_queue *connq, struct conn *conn)
{
	if (connq->cq_num == 0) {
		connq->cq_first = conn;
		connq->cq_last = conn;
	}
	connq->cq_last->cq_prev = conn;
	conn->cq_prev = NULL;
	conn->cq_next = connq->cq_last;
	connq->cq_last = conn;
	connq->cq_num++;
}

struct conn *conn_queue_get(struct conn_queue *connq)
{
	struct conn *last = connq->cq_last;
	if (connq->cq_num == 0)
		return NULL;
	last->cq_prev->cq_next = NULL;
	last->cq_prev = last->cq_next = NULL;
	connq->cq_num--;
	return last;
}

void conn_queue_free(struct conn_queue *connq)
{
	int i;
	if (connq->cq_num == 0)
		return;
	for (i = 0; i < connq->cq_num; i++) {
		struct conn *conn = connq->cq_last;
		connq->cq_last = conn->cq_next;
		conn_free(conn);
		connq->cq_num--;
	}
	free(connq);
}

