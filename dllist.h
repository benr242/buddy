#ifndef DLLIST_H_
#define DLLIST_H_

typedef struct dllist DLList;
typedef struct dllist *DLListPtr;

struct dllist 
{
	int size;
	NodePtr head;
	NodePtr tail;
};

#endif /*DLLIST_H_*/
