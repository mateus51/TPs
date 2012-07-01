#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
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
	if (msg.text_len > 0) {
		memcpy(&msg.text, buffer + 8, msg.text_len);
		msg.text[140] = '\0';
	}
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

void send_message(int sock, unsigned short int from, unsigned short int to, const char *str) {
	msg_t msg;
	bzero(msg.text, 141);
	msg.orig_uid = from;
	msg.dest_uid = to;
	msg.type = MSG;
	int str_size = strlen(str) + 1;
	if (str_size > 141) {
		msg.text_len = 141;
		memcpy(msg.text, str, 140);
		msg.text[140] = '\0';
	}
	else {
		msg.text_len = str_size;
		memcpy(msg.text, str, str_size);
	}

	char buffer[BUFF_LEN];
	encode(buffer, msg);
	int write_resp = write (sock, buffer, MSG_SIZE(msg));
	if (write_resp < 0) {
		perror("write()");
		exit(EXIT_FAILURE);
	}
	else if (write_resp == 0) {
		// server hung up
		printf("server hung up!\n");
		exit(EXIT_SUCCESS);
	}
}
