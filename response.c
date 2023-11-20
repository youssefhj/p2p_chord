#include "node.h"

/**
 * find_successor_response - Find successor for this node
 * 
 * @node: Node that will responde
 * @buffer: Buffer contains GETP
 * 
*/
void find_successor_response(Node *node, void *buffer) {

    memset(buffer, 0, 1024);
    sprintf(buffer, "SUCCE %d %s %d", node->id, node->ip, node->port); // Prepare the packet SUCCE <id ip port>

}

/**
 * get_predecessor_response - Response to get predecessor request
 * 
 * @node: Node that will responde
 * @buffer: Buffer contains GETP
 * 
*/
void get_predecessor_response(Node *node, void *buffer) {
    
    memset(buffer, 0, 1024);
    sprintf(buffer, "PRED %d", node->predecessor); // Prepare the packet PRED <predecessor>
}

/**
 * notify_response - Response to notify request
 * 
 * @node: Node that will responde
 * @buffer: Buffer contain NTFY <node_id>
 * 
*/
void notify_response(Node *node, void *buffer) {
    
    // Get the slot node_id from NTFY
    int id;
    sscanf(buffer, "NTFY %d", id);

    // Start the notify mehod
    notify(node, id);
}

/**
 * response - Response of any kind of request
 * 
 * @node: Node that will responde
 * 
*/
void response(Node *node) {
    char buffer[1024];

    int sockfd = start_socket_server(node->port);

    socket_read(sockfd, buffer, 1024);

    if (! strncmp(buffer, "GETP", 5)) { // GETP
        get_predecessor_response(node, buffer);
        socket_send(sockfd, buffer);
    }

    if (! strncmp(buffer, "NTFY", 5)) // NTFY <node_id>
        notify_response(node, buffer);
    
    if (! strncmp(buffer, "FNDS", 5)) { // FNIDS
        find_successor_response(node, buffer);
        socket_send(sockfd, buffer);
    }

    socket_close(sockfd);
}