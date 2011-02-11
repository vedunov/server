#include <conn.h>
#include <stdlib.h>
#include <packet_queue.h>

struct conn *conn_new(void)
{
	return (struct conn *)calloc(1, sizeof(struct conn));
}

void conn_free(struct conn *conn)
{
	packet_queue_free(conn->pq_rcv);
	packet_queue_free(conn->pq_snd);
	free(conn);
}
