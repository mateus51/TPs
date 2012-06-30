/*
 * Lê informações da linha de comando
 */
void get_info(int argc, char **argv, unsigned short int *uid, char *addr, int *port);

/*
 * Conecta ao servidor. retorna o socket a ser utilizado
 * para interagir com o servidor.
 */
int connect_to_server (char *server_name, int port, unsigned short int uid);

/*
 * Desconecta do servidor
 */
void disconnect_from_server(int sock, unsigned short int uid);
