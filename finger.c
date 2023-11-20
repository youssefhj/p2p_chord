#include "finger.h"

/**
 * insert_finger - Inserssion iside the fingers table
 * 
 * @node: node that contains the fingers table
 * @n: Node that contains the information of the refrenced node
 * @pos: Position of adding
 * 
 * 
*/
void insert_finger(Node *node, Node n, int pos) {

    node->fingers[next].node_id = n.id;
    node->fingers[next].ip = n.ip;
    node->fingers[next].port = n.port;

}