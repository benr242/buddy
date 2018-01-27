#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "node.h"
#include "dllist.h"
#include "location.h"

//get the list node, searching from the front
static NodePtr getListNodeForward (List l, int i);
//get the list node, searching from the back
static NodePtr getListNodeBackward (List l, int i);

static void printList (List l);
static void print (NodePtr node);

//the 3 special cases
static void addToEmptyList (List l, Data d);
static void addToEndList (List l, Data d);
static void addToBeginningList (List l, Data d);

static void putNode (Data d, NodePtr n);
static void insNode (List l, Data d, NodePtr n);

static void printList (List l)
{
	DLListPtr dll = (DLListPtr)l;

	if (dll)
	{
		printf("SIZE::%d::", ((DLListPtr)l)->size);
		print (dll->head);
	}
}

static void print (NodePtr node)
{
	while (node)
	{
		printf(" %x  -->", ((LocationPtr)node->obj)->loc);
		node = node->next;
	}
	
	printf("\n");
}

List newList ()
{
	DLListPtr newList = malloc (sizeof(DLList));
	
	newList->head = 0;
	newList->tail = 0;
	newList->size = 0;
	
	return (List)newList;
}

void freeList (List l)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr currNode = dll->head;
	NodePtr nextNode;
	
	while (currNode)
	{
		nextNode = currNode->next;
		free (currNode);
		currNode = nextNode;
	}
	
	free (l);
}

//assume list is valid
NodePtr getListNodeForward (List l, int i)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr curr = dll->head;
	int size = dll->size;
	
	int j;

	if (i >= size)
		return 0;

	if (curr)
	{
		for (j = 0; j < i; j++)
		{
			curr = curr->next;
		}
	}
	
	return curr;
}

//assume list is valid
NodePtr getListNodeBackward (List l, int i)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr curr = dll->tail;
	int size = dll->size;
	
	int j;

	if (i == -1)
		return 0;
	
	if (-i > (size+1))
		return 0;

	if (curr)
	{
		for (j = -2; j > i; j--)
		{
			curr = curr->prev;
		}
	}
	
	return curr;
}

Data getList (List l, int i)
{
	NodePtr np;
	if (i >=0)
		np = getListNodeForward (l, i);
	else
		np = getListNodeBackward(l, i);
	
	if (np)
		return np->obj;
	else
		return 0;
}

static void addToEmptyList (List l, Data d)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr tmp = createNode(d);
	
	dll->head = tmp;
	dll->tail = tmp;
}

static void addToEndList (List l, Data d)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr tmp = createNode (d);
	tmp->prev = dll->tail;
	dll->tail->next = tmp;
	dll->tail = tmp;
}

static void addToBeginningList (List l, Data d)
{
	DLListPtr dll = (DLListPtr)l;
	NodePtr tmp = createNode (d);
	tmp->next = dll->head;
	dll->head->prev = tmp;
	dll->head = tmp;
}

/*
 * just replace the data in a node
 */
void putNode (Data d, NodePtr n)
{
	n->obj = d;
}

/*
 * insert a new node where n used to be
 */
void insNode (List l, Data d, NodePtr n)
{
	DLListPtr dll = (DLListPtr)l;
	
	NodePtr newNode = createNode (d);
	
	//the new node is not the first in the list
	if (n->prev)
		n->prev->next = newNode;
	else
		dll->head = newNode;
	
	newNode->prev = n->prev;
	newNode->next = n;
	
	n->prev = newNode;
}

int sizeList (List l)
{
	return ((DLListPtr)l)->size;
}

Data remList (List l, int i)
{
	DLListPtr dll = (DLListPtr)l;
	Data tmpData;
	
	NodePtr tmpNode, prevNode, nextNode;
	if (i >= 0)
		tmpNode = getListNodeForward (l, i);
	else
		tmpNode = getListNodeBackward (l, i);
	
	//this was a valid node
	if (tmpNode)
	{
		prevNode = tmpNode->prev;
		nextNode = tmpNode->next;

		//cut tmpNode out of list
		if (prevNode)
			prevNode->next = nextNode;
		if (nextNode)
			nextNode->prev = prevNode;
		
		//reset list head and tail if needed
		if (dll->head == tmpNode)
			dll->head = tmpNode->next;
		if (dll->tail == tmpNode)
			dll->tail = tmpNode->prev;
		
		tmpData = tmpNode->obj;
		free(tmpNode);
		
		dll->size--;
		
		printList (l);
		
		return tmpData;
	//nothing to remove
	} else
	{
		return 0;
	}
}

/*
 * You are putting into a valid list node, intending to replace something.
 * Otherwise the error happened prior to here. 
 */
void putList (List l, int i, Data d)
{
	DLListPtr dll = (DLListPtr)l;
	
	NodePtr tmpNode;
	if (i >= 0)
		tmpNode = getListNodeForward (l, i);
	else
		tmpNode = getListNodeBackward (l, i);
	
	if (tmpNode)
	{
		putNode (d, tmpNode);
	}

	printList (l);
}

/*
 * Any index is valid. If you're off in space, it will go at the 
 * beginning or the end.
 */
void insList (List l, int i, Data d)
{
	DLListPtr dll = (DLListPtr) l;
	
	NodePtr tmpNode;
	if (i >= 0)
		tmpNode = getListNodeForward (l, i);
	else
		tmpNode = getListNodeBackward (l, i);
	
	if (tmpNode)
	{
		insNode (l, d, tmpNode);
	}
	else //the list was empty, or I'm off in space
	{
		if (dll->size == 0)
			addToEmptyList (l, d);
		else if ((i >= dll->size) || (i == -1))
			addToEndList (l, d);
		else if (i <= (dll->size - 2))
			addToBeginningList (l, d);
	}

	dll->size++;
	printList (l);
}
