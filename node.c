#include "node.h"

/**
 * create_node - Helps initialize the node structure
 * 
 * Ruturn: Created node
*/
Node create_node(void) {
    Node node;

    //[!!]
    node.successor = node.id;
    node.predecessor = nil;

    return node;
}

/**
 * join - Helps to the node created to join the chord
 * 
 * @node: Node that want to join
 * @helper_node: node that find the succerssor of the created node
*/
void join(Node *node, Node helper_node) {
    node->predecessor = nil;
    
    node->successor = find_successor_request(helper_node.id); // Ask for successor  // [ !! to handle error !! ]
}

/**
 * stabilize - Called periodicly to ensure the accuracy  
 *          of the successor of the joined node 
 *          and notify the node's successor to update his predecessor 
 * 
 * @node: Node to stabilize
*/
void stabilize(Node *node) {
    
    int successor_predecessor = get_predecessor_request(node->successor);  // Ask for successor predecessor // [ !! to handle error !! ]

    if (successor_predecessor > node->id && successor_predecessor < node->successor)
        node->successor = successor_predecessor;
    
    
    notify_request(); // [ !! to handle error !! ]
}

/**
 * notify - Called after stabilize to ensure that
 *        tthe node think might be the predecessor of his successor
*/
void notify(int id) {

    if (node.predecessor = nil || (id > node.predecessor && id < node.id))
        node.predecessor = id;
}