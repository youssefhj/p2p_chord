#include "node.h"

/**
 * create_node - Helps initialize the node structure
 * 
 * @ip: Ip adress for this node
 * @port: Port number accociated
 * 
 * Ruturn: Created node
*/
Node create_node(char *ip, int port) {
    Node node;

    node.ip = ip;
    node.port = port;
    node.successor = node.id;
    node.predecessor = nil;

    return (node);
}

/**
 * join - Helps to the node created to join the chord
 * 
 * @node: Node that want to join
 * @trust_node: node that find the succerssor of the created node
 * 
*/
void join(Node *node, Node trust_node) {
    node->predecessor = nil;
    
    node->successor = find_successor_request(node, trust_node).id; // Ask for successor  // [ !! to handle error !! ]
}

/**
 * stabilize - Called periodicly to ensure the accuracy  
 *          of the successor of the joined node 
 *          and notify the node's successor to update his predecessor 
 * 
 * @node: Node to stabilize
 * 
*/
void stabilize(Node *node) {
    // Establish connexion with the successor
    int sockfd = start_socket_client(node->fingers[node->successor].ip, 
            node->fingers[node->successor].port);

    int successor_predecessor = get_predecessor_request(node->successor, sockfd);  // Ask for successor predecessor // [ !! to handle error !! ]

    if (successor_predecessor > node->id && successor_predecessor < node->successor)
        node->successor = successor_predecessor;
    
    
    notify_request(node, sockfd); // [ !! to handle error !! ]
    socket_close(sockfd);
}

/**
 * notify - Called after stabilize to ensure that
 *        tthe node think might be the predecessor of his successor
 * 
 * @node: Node that will update its predecessor with id
 * @id: Id of node that send notify request
 * 
 * 
*/
void notify(Node *node, int id) {

    if (node->predecessor = nil || (id > node->predecessor && id < node->id))
        node->predecessor = id;
}

/**
 * fix_fingers - Called periodicly to fix the list of fingers
 * 
 * @node: Node that will fixe its list
 * 
*/
void fix_fingers(Node *node) {

    next++;
    if (next > m) {
        next = 1;
    }

    Node *nextNode;
    nextNode->id = (node->id) + power(2, next - 1);
    if (nextNode->id > power(2, m))
        nextNode->id %= power(2, m);

    Node n = find_successor_request(nextNode, trustNode);
   
    node->fingers[next].node_id = n.id;
    node->fingers[next].ip = n.ip;
    node->fingers[next].port = n.port;
}

/**
 * check_predecessor - Check predecessor if failed
 * 
 * @node: Node that check its predecessor
 * 
*/
// void check_predecessor(Node *node) {
//     if(node->predecessor ) 
//         node->predecessor = nil;
// }