#include <string.h>
#include "mensagem.h"

short int getType(msg_t *msg){
  return msg->type;
}

char* getText(msg_t *msg){
  return msg->text;
}

short int getLen(msg_t *msg){
  return msg->text_len;
}

short int getOrig(msg_t *msg){
  return msg->orig_uid;
}

short int getDest(msg_t *msg){
  return msg->dest_uid;
}

void setMsg(msg_t *msg, short int type, short int orig, short int dest, short int len, char* text){
  msg->type = type;
  msg->orig_uid = orig;
  msg->dest_uid = dest;
  msg->text_len = len;
  strcpy(msg->text,text);
}
