#ifndef _FINGER_H_
#define _FINGER_H_

/**
 * struct finger - Finger structre
 * 
 * @node_id: Node identifier
 * @ip: Ip adress of node_id
 * @port: Port number accociated to node_id
 * 
 * Description: This structure represente a reference node's
 *              reference in the ring
*/
struct Finger {

    int node_id;
    char *ip;
    int port;

};

typedef struct Finger Finger;

#endif