#ifndef LIST_H
#define LIST_H

typedef void *List;
typedef void *Data;

extern List newList(void); 
extern void freeList(List l);
extern int sizeList(List l);
extern Data getList(List l, int i);
extern Data remList(List l, int i); 
extern void putList(List l, int i, Data d);
extern void insList(List l, int i, Data d); 
#endif
