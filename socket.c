#include "socket.h"

/**
 * start_socket_server- Start the socket if the node act as server 
 * 
 * @port: Port number
 * 
 * Return: Socket file descriptor
*/
int start_socket_server(int port) {

    struct sockaddr_in address;
    socklen_t addrlen;
    int sockfd, asockfd, opt = 1;

    addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-] socket failed.");
        return (-1);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("[-] setsockopt");
        return (-1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
 
    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("[-] bind failed.");
        return (-1);
    }

    if (listen(sockfd, 3) < 0) {
        perror("[-] listen");
        return (-1);
    }

    if ((asockfd = accept(sockfd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("[-] accept.");
        return (-1);
    }
    
    close(sockfd);
    return (asockfd);
}

/**
 * start_socket_client - Start the socket if the node act as client 
 * 
 * @server_ip: Ip adresse of the server
 * @port: Port number of the server
 * 
 * Return: Socket file desctiptor
 * 
*/
int start_socket_client(char *server_ip, int port) {
    
    struct sockaddr_in address;
    int sockfd;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-] socket failed.");
        return (-1);
    }


    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &address.sin_addr) <= 0) {
        perror("[-] Invalid address Address not supported.");
        return (-1);
    }
 
    if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("[-] Connection Failed.");
        return (-1);
    }

    return (sockfd);
}

/**
 * socket_read - Read from socket
 * @sockfd: Socket file descriptor
 * @buffer: Buffer
 * @buffer_size: Buffer size
 * 
 * Return: -1 on failure | size data read
*/
ssize_t socket_read(int sockfd, void *buffer, size_t buffer_size) {
    
    // Clear the buffer
    memset(buffer, 0, buffer_size * sizeof(buffer));

    if (sockfd == -1) return (-1);

    return read(sockfd, buffer, buffer_size - 1);
    
}

/**
 * socket_send - Write to socket
 * @sockfd: Socket file descriptor
 * @msg: Message to send
 * 
 * Return: -1 failure | number of bytes sent
*/
ssize_t socket_send(int sockfd, void *msg) {
    if (sockfd == -1) return (-1);
    
    return send(sockfd, msg, strlen(msg), 0);
}

/**
 * socket_close - End the connection
 * 
 * @sockfd: Socket file descriptor
 * 
*/
void socket_close(int sockfd) {
    close(sockfd);
}