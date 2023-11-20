#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


/**
 * struct Socket - Structure of socket client or server
 * 
 * @sockfd: File descriptor of the newly created socket
 * @address: Structures for handling internet addresses
 * @port: Port number
 * @buffer: Buffer
 * 
 * Description: Each node socket [client | server] has this attributes
*/
struct Socket {
    int sockfd;
    struct sockaddr_in address;
    int port;
    char buffer[1024];
};

typedef struct Socket Socket;

int start_socket_server(int);
int start_socket_client(char *, int);

ssize_t socket_read(int, void *, size_t);
ssize_t socket_send(int, void *);

void socket_close(int);

#endif