#ifndef _msg_t_H
#define _msg_t_H

#define    OI 0
#define TCHAU 1
#define   MSG 2

typedef struct
{
  unsigned short int type;
  unsigned short int orig_uid;
  unsigned short int dest_uid;
  unsigned short int text_len;;
  unsigned char      text[141];
} msg_t;

short int getType(msg_t *msg);

char* getText(msg_t *msg);

short int getLen(msg_t *msg);

short int getOrig(msg_t *msg);

short int getDest(msg_t *msg);

void setMsg(msg_t *msg, short int type, short int orig, short int dest, short int len, char* text);

#endif
