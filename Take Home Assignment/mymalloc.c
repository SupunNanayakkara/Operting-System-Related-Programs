#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"

//create new memory block allocation by splitting a free memory block according to the requested memory size
void SplitCell(struct LinkBlock *f_slot, size_t size)
{
	struct LinkBlock *NewCell = (void*)((void*)f_slot + size + sizeof(struct LinkBlock));
	NewCell->size = (f_slot->size)-(size+sizeof(struct LinkBlock));
	NewCell->avail = 1;
	NewCell->next = f_slot->next;
	f_slot->size = size;
	f_slot->avail = 0;
	f_slot->next = NewCell;
	
}

//create MyMalloc function for allocate requested memory
void *MyMalloc(size_t MemSize)
{
	struct LinkBlock *cptr = StartMemory;
	void *mem_allocate;
	
	if(!(StartMemory->size))
	{
		StartMemory->size = sizeof(MyMemory) - sizeof(struct LinkBlock);
		StartMemory->avail = 1;
		StartMemory->next = NULL;
		printf("Memory is Ready...\n");
		printf("Size of MyMemory=%d\n\n",sizeof(MyMemory));
	}
	
	cptr = StartMemory;
	while(((cptr->size < MemSize)||(cptr->avail == 0)) && (cptr->next!=NULL))
	{
		cptr = cptr->next;
	}
	
	if(cptr->size == MemSize)
	{
		cptr->avail = 0;
		mem_allocate = (void*)(++cptr);
		printf("%u size block allocated from %d to %d\n",MemSize,mem_allocate,(mem_allocate+MemSize));
		return mem_allocate;
	}
	else if(cptr->size >= (MemSize + sizeof(struct LinkBlock)))
	{
		SplitCell(cptr,MemSize);
		mem_allocate = (void*)(++cptr);
		printf("%u size block allocated from %d to %d\n",MemSize,mem_allocate,(mem_allocate+MemSize));
		return mem_allocate;
	}
	else
	{
		mem_allocate = NULL;
		printf("No sufficient Memory.");
		return mem_allocate;
	}
}

//create MyFree function for deallocates the memory previously allocated by a call to MyMalloc
void MyFree(void *freeptr)
{
	void *mem_allocate;
	if(((void*)MyMemory)<=freeptr && freeptr<=((void*)MyMemory + sizeof(MyMemory)))
	{
		
		struct LinkBlock *cptr = freeptr;
		mem_allocate = (void*)(cptr);
		--cptr;
		cptr->avail = 1;
		printf("%u size block free from %d to %d\n",cptr->size,mem_allocate,(mem_allocate+cptr->size));	
		struct LinkBlock *sptr = StartMemory;
		//merge the consecutive free blocks by removing the LinkBlock in the middle
		while(sptr->next!=NULL)
		{
			if(sptr->avail==1 && sptr->next->avail==1)
			{
				sptr->size = sptr->size + sptr->next->size + sizeof(struct LinkBlock);
				sptr->next = sptr->next->next;
			}
			sptr = sptr->next;
		}
	}
	else
	{
		printf("Invalid Pointer.");
	}
}

int main()
{
	return 1;
}


