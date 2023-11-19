#ifndef _NODE_H_
#define _NODE_H

#include "socket.h"
#include "finger.h"

/**
 * struct Node - Node structure inside the chord
 * @id: Node identifier
 * @successor: The next node
 * @predecessor: The previous node
 * @ip: Node ip adresse
 * @port: Associated port number
 * @fingers: List of the node [node_id + 2^(k-1) % 2^m, ip, port]
 *           0 <= k <= m ; 2^m maximum chord in the ring
 * 
 * Desctiption: Each node in the p2p system has this attributes
*/
struct Node {

    int id;
    int successor;
    int predecessor;
    char *ip;
    int port;
    // Finger fingers[];
    // HashTable ;

};

typedef struct Node Node;

#define nil ((void *) 0) // To respect terminologie; its equivalent to NULL

Node create_node();
void join(Node *, Node);
void stabilize(Node *);
void notify(int);

// Interaction with other node

int find_successor_request(int);
int get_predecessor_request(int);
int notify_request(void);

// int notify_response();
// int find_successor_response();
// int get_predecessor_response();

int find_successor(int);
int closest_preceding_node(int);

#endif
