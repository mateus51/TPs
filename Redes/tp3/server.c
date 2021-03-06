#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "tp_socket.h"
#include "message.h"
#include "time.h"
#include "sig_listener.h"


/* array p/ controlar clientes de recepção/envio
 *    1-999  -> exibição
 * 1001-1999 -> envio
 */
int clients[2000];

fd_set active_fd_set;


double start_time;

// Lê o número da porta passado na chamada do programa
void read_port_number(int argc, char *argv[], int *port) {
	if(argc != 2){
		printf("Usage:  %s <port>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		*port = atoi(argv[1]);
	}
}


void close_client_connection(unsigned short int uid) {
	close(clients[uid]);
	FD_CLR (clients[uid], &active_fd_set);
	clients[uid] = -1;
}


void make_status_string(char *str) {
	int i, exib = 0, env = 0;
	for (i = 1; i < 2000; i++)
		if (clients[i] != -1) {
			if (i < 1000)
				exib++;
			else
				env++;
		}
	int elapsed_minutes = (get_time() - start_time) / 60;
	sprintf(str, "[tp3-server] Clientes (exibição/envio/total): %d/%d/%d   Uptime: %dh %dm", exib, env, exib + env, elapsed_minutes / 60, elapsed_minutes % 60);
}

/*
 * Envia uma mensagem para todos os clientes conectados
 */
void broadcast_message(const char *str) {
	int i;
	for (i = 0; i < 1000; i++) {
		if (clients[i] != -1) {
			send_message(clients[i], 0, 0, str);
		}
	}
}


/*
 * Faz verificação do remetente. Verifica se ID da faixa
 * de envio, e se o socket de recebimento corresponde ao
 * socket do cliente ID
 */
int check_sender(msg_t msg, int sock) {
	if (msg.orig_uid > 1000 && msg.orig_uid < 2000 && clients[msg.orig_uid] == sock)
		return 1;
	else
		printf("\nmensagem com remetente forjado (%u)! descartando...\n", msg.orig_uid);

	return 0;
}



/*
 * Recebe dados de cliente já conectado.
 * Faz verificação do tipo de mensagem, e executa
 * a ação necessária.
 * Retorna o número de byte lidos, ou -1 caso houve
 * algum erro e a conexão precisa ser fechada/
 */
int read_from_client(int sock) {
	char buffer[BUFF_LEN];
	char str[141];
	bzero(buffer, BUFF_LEN);
	int nbytes;

	nbytes = read (sock, buffer, BUFF_LEN);
	if (nbytes < 0) {
		/* Read error. */
		perror ("read()");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0) {
		/* Cliente fechou conexão. Tratar como se fosse TCHAU */
		unsigned short int i;
		for (i = 0; i < 2000; i++) {
			if (i != 0 && i != 1000) {
				if (clients[i] == sock) {
					clients[i] = -1;

					// se for cliente de envio e tiver um cliente de exibição associado
					// desconecta o cliente de exibição.
					if (i > 1000 && clients[i - 1000] != -1) {
						close_client_connection(i - 1000);
						sprintf(str, "[tp3-server] cliente %u desconectou!", i - 1000);
						broadcast_message(str);
					}
				}
			}
		}
		return -1;
	}
	else {
		// cliente enviou dados
		msg_t msg = decode(buffer);

		switch (msg.type) {

		case OI:
		// Nova conexão de cliente:
		//   - checar disponibilidade de espaço p/ conexão
		//   - conectar cliente caso possivel
		//   - se conectou, retornar OI
		//   - se não conectou, retornar ERRO

			// se for cliente de exibição
			if (msg.orig_uid < 1000) {
				if (clients[msg.orig_uid] == -1 && clients[msg.orig_uid + 1000] == -1) {
					// espaço disponível. Retorna OI.
					clients[msg.orig_uid] = sock;
					write (sock, buffer, nbytes);
					printf("\n%s\n", str);
					// avisa clientes conectados que alguém conectou
					sprintf(str, "[tp3-server] cliente %u conectou!", msg.orig_uid);
					broadcast_message(str);
				}
				else {
					// já existe cliente conectado. Retorna ERRO.
					msg.type = ERRO;
					sprintf(msg.text, "identificador %u já está em uso!", msg.orig_uid);
					msg.text_len = (unsigned short int) strlen(msg.text) + 1;
					encode(buffer, msg);
					write (sock, buffer, MSG_SIZE(msg));
					return -1;
				}
			}

			// se for cliente de envio
			else if (msg.orig_uid > 1000 && msg.orig_uid < 2000) {
				if (clients[msg.orig_uid] == -1) {
					clients[msg.orig_uid] = sock;
					write (sock, buffer, nbytes);
					printf("\nclient %u connected!\n", msg.orig_uid);
				}
				else {
					// já existe cliente conectado. Retorna ERRO.
					msg.type = ERRO;
					sprintf(msg.text, "identificador %u já está em uso!", msg.orig_uid);
					msg.text_len = (unsigned short int) strlen(msg.text) + 1;
					encode(buffer, msg);
					write (sock, buffer, MSG_SIZE(msg));
					return -1;
				}
			}

			else {
				// identificador inválido.
				// retorna ERRO e fecha conexão
				msg.type = ERRO;
				sprintf(msg.text, "identificador %u inválido!", msg.orig_uid);
				msg.text_len = (unsigned short int) strlen(msg.text) + 1;
				encode(buffer, msg);
				write (sock, buffer, MSG_SIZE(msg));
				return -1;
			}
			break;



		case TCHAU:
		// Cliente fechando conexão:
		//   - retirar cliente da lista de clientes

			if (check_sender(msg, sock)) {
				// retira cliente da lista de clientes conectados
				clients[msg.orig_uid] = -1;

				// se for cliente de envio e tiver um cliente de exibição associado
				// desconecta o cliente de exibição.
				if (msg.orig_uid > 1000 && clients[msg.orig_uid - 1000] != -1) {
					close_client_connection(msg.orig_uid - 1000);
					sprintf(str, "[tp3-server] cliente %u desconectou!", msg.orig_uid - 1000);
					printf("\n%s\n", str);
					broadcast_message(str);
				}
				printf("\nclient %d disconnected!\n", msg.orig_uid);
			}
			else {
				// identificador inválido.
				// retornar ERRO e fechar conexão?
			}
			// retorna -1 para fechar conexão
			return -1;



		case MSG:
			// Cliente enviando mensagem:
			//   - checar origem da mensagem (descartar msg caso necessário)
			//   - enviar msg p/ destinatário (0 = broadcast)

			// Se o remetente estiver correto
			if (check_sender(msg, sock)) {

				printf("\nreceived message!\n");
				printf("  from: %u\n  to: %u\n  message: %s\n", msg.orig_uid, msg.dest_uid, msg.text);

				if (msg.dest_uid >= 1000) {
					printf("\n  mensagem não é para exibidor. descartando...\n");
					return nbytes;
				}

				// Se é broadcast
				if (msg.dest_uid == 0) {
					int i;
					for (i = 0; i < 1000; i++) {
						if (clients[i] != -1) {
							write (clients[i], buffer, nbytes);
						}
					}
				}

				// Se é cliente de exibição
				else if (msg.dest_uid < 1000) {
					write (clients[msg.dest_uid], buffer, nbytes);
				}

			}
			break;

		default:
			fprintf(stderr, "Error: unknown header sent by client %d (header: %u)\n", msg.orig_uid, msg.type);
			/* Se ocorrer mensagem inespearada, tratar como se fosse TCHAU */
			return -1;
			break;
		}
	}

	return 0;
}

int main (int argc, char **argv) {
	int serversock;
	int port;
	read_port_number(argc, argv, &port);
	int i;
	so_addr clientaddr;
	size_t size;

	/* Create the socket and set it up to accept connections. */
	serversock = tp_socket(port);
	if (listen (serversock, 1) < 0) {
		perror ("listen()");
		exit (EXIT_FAILURE);
	}

	// Inicializando array de clientes.
	for (i = 0; i < 2000; i++)
		clients[i] = -1;

	/* Initialize the set of active sockets. */
	fd_set read_fd_set;
	FD_ZERO (&active_fd_set);
	FD_SET (serversock, &active_fd_set);

	printf("Server ready to accept connections\n\n");

	start_time = get_time();

	start_signal_listener();

	while (1) {

		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
			perror ("select()");
			exit (EXIT_FAILURE);
		}

		/* Service all the sockets with input pending. */
		for (i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd_set)) {

			/* Novo cliente estabelecendo conexão TCP. */
			if (i == serversock) {
				int new;
				size = sizeof (clientaddr);
				new = accept (serversock, (struct sockaddr *) &clientaddr, &size);
				if (new < 0) {
					perror ("accept()");
					exit (EXIT_FAILURE);
				}
				/* printing host info */
				char hostname[256];
				getnameinfo((struct sockaddr *)&clientaddr, size, hostname, 256, 0, 0, 0);
				printf("Server: connection from %s, port %d.\n", hostname, ntohs(clientaddr.sin_port));
				/* Adiciona cliente à lista de sockets ativos. */
				FD_SET (new, &active_fd_set);
			}

			/* Dados chegando por conexão já estabelecida. */
			else {
				if (read_from_client (i) < 0) {
					close (i);
					FD_CLR (i, &active_fd_set);
				}
			}
		}
	}
}
