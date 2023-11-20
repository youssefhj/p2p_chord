#include "node.h"

/**
 * closest_preceding_node - Find the closest preceding node
 * 
 * @node: The node to talk with
 * @id: Id of node that we need to find preceding node
 * 
 * Return: The closest preceding node
*/
Node closest_preceding_node(Node node, int id) {
    int m;

    for (m = 32; m >= 0 ; m--) {
        if (node.fingers[m].node_id > node.id && node.fingers[m].node_id < id) {
            Node n = {
                .id = node.fingers[m].node_id,
                .ip = node.fingers[m].ip, 
                .port = node.fingers[m].port
                
            };

            return (n);
        }
    }

    return (node);
}

/**
 * find_successor_request - Tell the node with trust_node to find our successor
 *                          and do that recursively 
 * 
 * @node: Node demanding to find his direct successor
 * @trust_node: The node that is responsible to find our successor
 * 
 * Return: Node successor
*/
Node find_successor_request(Node *node, Node trust_node) {
    char FNDS[1024];
    
    int sockfd = start_socket_client(trust_node.ip, trust_node.port);

    socket_send(sockfd, "FINDS");

    memset(FNDS, 0, 1024);
    socket_read(sockfd, FNDS, 1024);

    int successor, port;
    char *ip;

    sscanf(FNDS, "SUCCE %d %s %d", successor, ip, port);

    Node n;
    n.id = successor;
    n.ip = ip;
    n.port = port;

    if (node->id > trust_node.id && node->id <= successor)
        return (n);

    Node next_trusted_node = closest_preceding_node(trust_node, node->id);
    return find_successor_request(node, next_trusted_node);
}

/**
 * get_predecessor_request - Demande the predecessor from the successor
 * 
 * @node: Node demanding this information
 * @sockfd: Socket file descriptor
 * 
 * Return: Successor predecessor
 * 
*/
int get_predecessor_request(Node *node, int sockfd) {
    
    char PRED[1024];  // send paquet PRED <node>

    sprintf(PRED, "GETP");

    socket_send(sockfd, PRED);

    memset(PRED, 0, 1024);
    socket_read(sockfd, PRED, 1024);

    int predecessor;
    sscanf(PRED, "PRED %d", predecessor);

    return (predecessor);

}

/**
 * notify_request - request sent to successor to do notify
 * 
 * @Node: Node that will send the notify request
 * @sockfd: Socket file descriptor
 * 
*/
void notify_request(Node *node, int sockfd) {

    char NTFY[1024];  // send paquet NTFY <node_id>

    sprintf(NTFY, "NTFY %d", node->id);

    socket_send(sockfd, NTFY);
}