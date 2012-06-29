#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "message.h"

msg_t decode(const char *buffer) {
	msg_t msg;
	bzero(msg.text, 141);
	memcpy(&msg.type, buffer, 2);
	memcpy(&msg.orig_uid, buffer + 2, 2);
	memcpy(&msg.dest_uid, buffer + 4, 2);
	memcpy(&msg.text_len, buffer + 6, 2);
	memcpy(&msg.text, buffer + 8, 140);
	msg.text[140] = '\0';
	return msg;
}

void encode(char *buffer, msg_t msg) {
	bzero(buffer, BUFF_LEN);
	memcpy(buffer, &msg.type, 2);
	memcpy(buffer + 2, &msg.orig_uid, 2);
	memcpy(buffer + 4, &msg.dest_uid, 2);
	memcpy(buffer + 6, &msg.text_len, 2);
	memcpy(buffer + 8, &msg.text, 140);
	buffer[BUFF_LEN] = '\0';
}
