#include <packet.h>
#include <stdlib.h>
#include <string.h>

struct packet *packet_new(void)
{
	struct packet *pkt = calloc(1, sizeof(struct packet));
	return pkt;
}

void packet_free(struct packet *pkt)
{
	free(pkt);
}

int packet_set(struct packet *pkt, char *buf, int num)
{
	if (num > PKT_BUFF_SIZE)
		num = PKT_BUFF_SIZE;
	memcpy(pkt->pkt_data, buf, num);
	pkt->pkt_pos = num;
	return num;
}
