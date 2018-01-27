#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node.h"
#include "dllist.h"
#include "location.h"

const unsigned int *base;
//unsigned int *trace;

List *availList;

unsigned char *bitmap;

int l, u;
int poolSize;

int power (int base, int n)
{
	int p, i; 
	
	p = 1;
	for (i = 0; i < n; i++)
		p = (p * base);
	
	return p;
}

int intToByte (int conv)
{
	return conv / 4;
}

/* initialize the available lists. this will mean all are empty
 * except the highest one (which will have at least 1 */
void initAvailList ()
{
	availList = (List *) malloc (sizeof(DLList)*(u-l));
	unsigned int *trace;
	
	int i;
	for (i = l; i < u; i++)
	{
		availList[i-l] = newList();
	}

	//ratio of pool size to highest denomination
	float rat = (float)poolSize / (float)(power(2,u));
	trace = base;
	
	/* this needs to be done, but something in here screws everything else up
	 * either this works, or returned blocks finding their size does */
	//add items to the biggest denomination if the poolsize is greater
	/*
	while (rat > 0)
	{
		printf("*********************************\n");

		LocationPtr tmp = (LocationPtr) malloc (sizeof(Location));
		tmp->loc = trace;
		
		//add to the end of the list
		insList (availList[u-l-1], 32, tmp);

		//printf("atmpTrace = %x\n", trace);
		trace += (intToByte(power (2, u)));
		//printf("btmpTrace = %x\n", trace);

		rat -= 1;
	}
	*/
}

void printAvailLists ()
{
	int i;
	for (i = l; i < u; i++)
	{
		printf("avail list: size %d = %d\n", i, sizeList(availList[i-l]));
	}
}

void initBitmap ()
{
	int i;
	for (i = l; i < u; i++)
	{
		bitmap[i-l] = 0x0;
	}
}

char *getBitmap (int size)
{
	return bitmap[size];
}

char getMask (int pos)
{
	unsigned char tmp = 0x80 >> pos;
}

void dummySetAlloc (int *add, int size)
{
	int pos = findBitPos (base, add, size);
	printf("bit position: %d\n", pos);
		
	unsigned char mask = getMask(pos);
	
	bitmap[size-l] = bitmap[size-l] | mask;
	//printf("bitmap for %d: %x\n", size, bitmap[size-1]);
	//printf("bitmap for size 5: %x\n", bitmap[0]);

}

int byteToInt (int conv)
{
	return conv * 4;
}

int findBlockSize (int base, int address)
{
	int i, pos;
	for (i = l; i <= u; i++)
	{
		pos = findBitPos(base, address, i);
		
		if (bitmap[i-l] & getMask(pos))
		{
			printf("found it-----------------------%d\n", i);
			return i;
		}
	}

	return 0;
}

int findBitPos (int base, int address, int size)
{
	return (address - base) / power(2, size) / 2;
}

int main(int argc, char *argv[]) 
{	
	l = atoi(argv[1]);
	u = atoi(argv[2]);
	bitmap = (char *)malloc(sizeof(char) * (u - l));
	unsigned int *trace;
	
	poolSize = (power(2,10))*3.5;
	base = trace = malloc (poolSize);
	
	initAvailList();
	initBitmap();

	
	//printf("base: %x\n", base);
	
	//set up some addresses
	int address0 = trace;
	//32 bytes later (2^5)
	trace += intToByte(32); 	
	int address1 = trace;
	trace += intToByte(32);
	int address2 = trace;
	trace += intToByte(32);
	int address3 = trace;
	trace += intToByte(32); 
	int address4 = trace;
	trace += intToByte(32); 
	int address5 = trace;
	trace += intToByte(32);
	int address6 = trace;
	trace += intToByte(32);
	int address7 = trace;
	trace += intToByte(32);
	int address8 = trace;
	
	//pretend these are allocated
	dummySetAlloc(address6, 5);
	printf("bitmap for size 5: %x\n", bitmap[0]);
	dummySetAlloc(address0, 5);
	printf("bitmap for size 5: %x\n", bitmap[0]);
	dummySetAlloc(address4, 5);
	printf("bitmap for size 5: %x\n", bitmap[0]);
	
	
	//printAvailLists ();

	printf("finding the size: %d\n", findBlockSize(base, address5));
	//three will not, since its buddy is not allocated
	printf("finding the size: %d\n", findBlockSize(base, address3));
	printf("finding the size: %d\n", findBlockSize(base, address1));
	
	return 0;
}
