#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct node *NodePtr;

struct node {
        void *obj;
        NodePtr next;
        NodePtr prev;
};

NodePtr createNode (void *obj);

void setNodeObj (NodePtr, void *obj);


#endif
