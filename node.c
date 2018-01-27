#include "node.h"

NodePtr createNode(void *obj)
{
    NodePtr newNode = (NodePtr) malloc (sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->obj = obj;
        
    return newNode;
}

void setNodeObj (NodePtr n, void *obj)
{
	n->obj = obj;
}

/*
Data freeNode (NodePtr node)
{
        free(node);
}
*/
