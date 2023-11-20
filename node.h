#ifndef _NODE_H_
#define _NODE_H

#include "socket.h"
#include "finger.h"
#include "hash.h"
#include "utility.h"

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
    Finger fingers[4];
    //HashTable ht[]; 

};

typedef struct Node Node;

#define nil ((void *) 0) // To respect terminologie; its equivalent to NULL

Node trustNode = {.ip = "192.168.92.254", .port = 4170};

int next = 0; // Used in fix_fingers
int m = 4; // max entry in fingers; max node in this case is 2^m

Node create_node(char *, int);
void join(Node *, Node);
void stabilize(Node *);
void notify(Node*, int);
void fix_fingers(Node *);
void check_predecessor(Node *);

Node closest_preceding_node(Node, int);

// Interaction with other node

Node find_successor_request(Node *, Node);
int get_predecessor_request(Node *, int);
void notify_request(Node *, int);

void find_successor_response(Node *, void *);
void get_predecessor_response(Node *, void *);
void notify_response(Node *, void *);
void response(Node *); 

#endif
