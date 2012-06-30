#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "message.h"

msg_t decode(const char *buffer) {
	unsigned short i;
	msg_t msg;
	memcpy(&i, buffer, 2);
	msg.type = ntohs(i);
	memcpy(&i, buffer + 2, 2);
	msg.orig_uid = ntohs(i);
	memcpy(&i, buffer + 4, 2);
	msg.dest_uid = ntohs(i);
	memcpy(&i, buffer + 6, 2);
	msg.text_len = ntohs(i);
	bzero(msg.text, 141);
	memcpy(&msg.text, buffer + 8, 140);
	msg.text[140] = '\0';
	return msg;
}

void encode(char *buffer, msg_t msg) {
	unsigned short i;
	bzero(buffer, BUFF_LEN);
	i = htons(msg.type);
	memcpy(buffer, &i, 2);
	i = htons(msg.orig_uid);
	memcpy(buffer + 2, &i, 2);
	i = htons(msg.dest_uid);
	memcpy(buffer + 4, &i, 2);
	i = htons(msg.text_len);
	memcpy(buffer + 6, &i, 2);
	memcpy(buffer + 8, &msg.text, 140);
	buffer[BUFF_LEN] = '\0'; // just to be safe
}
