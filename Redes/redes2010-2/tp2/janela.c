#include "janela.h"

int windowInitAtivo(char *host,int porto){

    tp_init();
    if ((idsocket_ = tp_socket(0)) < 0)
        return -1;

    if (tp_build_addr(&endereco_,host,porto) < 0 )
        return -2;

    srand(time(NULL));
    numero_ = 0;
    acksrecebidos_ = 0;
    acksenviados_ = 0;
    pacotesrecebidos_ = 0;
    pacotesenviados_ = 0;
    pacotesdescartados_ = 0;
    reenvios_ = 0;

    setTimer(2);
//    setTimer(0);
    return idsocket_;
}

int windowInitPassivo(int porto,int tambuffer, int tamjanela){

    tp_init();
    if ((idsocket_ = tp_socket(porto)) < 0)
        return -1;

    numero_ = 0;
    ultimoack_=0;
    tamjanela_ = tamjanela;
    tamatual_ = 0;
    offset_ = 0;
    acksrecebidos_ = 0;
    acksenviados_ = 0;
    pacotesrecebidos_ = 0;
    pacotesenviados_ = 0;
    reenvios_ = 0;

    int i;
    buffer_ = (char**)malloc(sizeof(char*)*tamjanela);
    for(i=0;i<tamjanela;i++){   
        buffer_[i] = (char*)malloc(sizeof(char)*(tambuffer+CABECALHO));
    }

    return idsocket_;
}

int windowSend(char *buffer, int tambuffer){

   //Verifica se a janela está cheia
   char pacote[tambuffer+CABECALHO];
   char pacotetmp[tambuffer+CABECALHO];
   char pacoteack[tambuffer+CABECALHO];
   int recebeuack = -1;
   
   makePkg(pacote,numero_,DADOS,buffer,tambuffer);
   
   if( tamatual_ == tamjanela_ ){

        recebeuack = tp_recvfrom(idsocket_, pacoteack, tambuffer+CABECALHO, (so_addr*)&endereco_);

        //Nao recebeu
        while(recebeuack == -1)
        {
          int i;
          for(i=offset_; i<tamjanela_; i++)
          {
            makePkg(pacotetmp,numPacote(buffer_[i%tamjanela_]),DADOS,buffer_[i]+CABECALHO,tambuffer);
            tp_sendto(idsocket_, pacotetmp, tambuffer+CABECALHO, (so_addr*)&endereco_);
            pacotesenviados_++;
            reenvios_++;
          }
          recebeuack = tp_recvfrom(idsocket_, pacoteack, tambuffer+CABECALHO, (so_addr*)&endereco_);
        }
        acksrecebidos_++;


        //Recebeu ack errado
        if(numPacote(pacoteack) != ultimoack_)
        {
          tamatual_ -= numPacote(pacoteack)-ultimoack_-1;
          ultimoack_=numPacote(pacoteack);
        }

       ultimoack_++;
       
       strcpy(buffer_[offset_],pacote);
       offset_ = (offset_ + 1) % tamjanela_;
    }
    else{
        tamatual_++;
        strcpy(buffer_[(tamatual_-1+offset_)%tamjanela_],pacote);
    }

    int enviados = 0;
    enviados = tp_sendto(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
    pacotesenviados_++;

    numero_++;
    return enviados;
    
}

//int counter_ = 0;
int windowReceive(char *buffer, int tambuffer){

    char pacote[tambuffer+CABECALHO];
    char pacoteack[tambuffer+CABECALHO];

    int recebidos = 0;
    recebidos = tp_recvfrom(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
    pacotesrecebidos_++;

//    counter_ = rand()%10;
//    if(counter_ < 5){
    while(numPacote(pacote) != numero_){
        makePkg(pacoteack,numPacote(pacote),ACK, pacote+CABECALHO,tambuffer); 
        tp_sendto(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
        acksenviados_++;
    
        recebidos = tp_recvfrom(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
        pacotesdescartados_++;
    }
//    }
    makePkg(pacoteack,numPacote(pacote),ACK, pacote+CABECALHO,tambuffer); 

    if(pacote[CABECALHO-2]==FINAL){
        makePkg(pacoteack,numPacote(pacote),FINAL, pacote+CABECALHO,tambuffer); 
//        tp_sendto(idsocket_, pacoteack, tambuffer+CABECALHO, (so_addr*)&endereco_);
    }
    
//    if(counter_ < 3){
        tp_sendto(idsocket_, pacoteack, tambuffer+CABECALHO, (so_addr*)&endereco_);
//    }
        acksenviados_++;
    
    numero_++;

    
    
    strncpy(buffer,pacote+CABECALHO,tambuffer);

    return recebidos-CABECALHO;

}

int checksum(char *buffer, int tambuffer){

    int i;
    int sum = 0;
    for(i=0;i<tambuffer;i++){
        sum += buffer[i];
        sum = sum % 128;
    }

    return sum;
}

int windowSendFinal(int tambuffer){

    char pacote[CABECALHO];
    makePkg(pacote,numero_,FINAL,NULL,0);
    
    tp_sendto(idsocket_, pacote, CABECALHO, (so_addr*)&endereco_);
    pacotesenviados_++;

//   tp_recvfrom(idsocket_, pacote, CABECALHO, (so_addr*)&endereco_);
    int recebeuack = 0;
    recebeuack = tp_recvfrom(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
    acksrecebidos_++;
    
    while(pacote[CABECALHO-2]!=FINAL ){
        recebeuack = tp_recvfrom(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
        acksrecebidos_++;
    }

    //Ack final
   
    
    printf("Reenvios: %d\nPacotes enviados %d\nPacotes recebidos %d\nACKs enviados %d\nACKs recebidos %d\n",reenvios_,pacotesenviados_,pacotesrecebidos_,acksenviados_,acksrecebidos_);
    acksrecebidos_ = 0;
    acksenviados_ = 0;
    pacotesrecebidos_ = 0;
    pacotesenviados_ = 0;
    reenvios_ = 0;

    numero_ = 0;
    ultimoack_=0;
    tamatual_ = 0;
    offset_ = 0;
  
    setTimer(0);
    return 0;
}

void makePkg(char* pacote,int numero,int tipo, char *buffer,int tambuffer){
    
    memcpy(pacote, &numero, 4);
    pacote[4] = tipo;
    pacote[5] = checksum(buffer,tambuffer);
    strncpy(pacote+CABECALHO,buffer,tambuffer);
} 

void windowClose(){
    printf("Reenvios: %d\nPacotes enviados %d\nPacotes recebidos %d\nACKs enviados %d\nPacotes descartados %d\n",reenvios_,pacotesenviados_,pacotesrecebidos_,acksenviados_,pacotesdescartados_);
    close(idsocket_);
}

int windowReceiveName(char *buffer, int tambuffer){

    char pacote[tambuffer+CABECALHO];
    
    int recebidos = 0;    
    recebidos = tp_recvfrom(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
    pacotesrecebidos_++;

    strncpy(buffer,pacote+CABECALHO,tambuffer);

    setTimer(1);
//    setTimer(0);
    
    return recebidos-CABECALHO;
}

int windowSendName(char *buffer, int tambuffer){

    char pacote[tambuffer+CABECALHO];
    makePkg(pacote,numero_,DADOS,buffer,tambuffer);

    int enviados = 0;
    enviados = tp_sendto(idsocket_, pacote, tambuffer+CABECALHO, (so_addr*)&endereco_);
    pacotesenviados_++;

    return enviados;
    
}

void setTimer(int segundos){

    struct timeval tv;
    tv.tv_sec = segundos;
    tv.tv_usec = 0;

    setsockopt(idsocket_, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&tv, sizeof(struct timeval));

}

int numPacote(char* pacote){

    int numero;
    memcpy(&numero, &pacote[0], 4);

    return numero;
}


