#include<stdio.h>
#include<stddef.h>

char MyMemory[25000];

//Structure of a metadata LinkBlock
struct LinkBlock
{
	size_t size; //memory blok size
	int avail; //availability of the memory cell. if avail=1, memory cell is available. if avail=0, memory is not available.
	struct LinkBlock *next;
};

struct LinkBlock *StartMemory = (void*)MyMemory; //StartMemory pointer pointing to the main memory block which is initially empty

void *MyMalloc(size_t MemSize);
void MyFree(void *ptr);
void SplitCell(struct LinkBlock *f_slot, size_t size);
