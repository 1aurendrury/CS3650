#define _DEFAULT_SOURCE
#define _BSD_SOURCE 
#include <malloc.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <debug.h> // definition of debug_printf


// using linked list of blocks
typedef struct block {
   size_t size;
   struct block *next;
   int free;
} block_t;


// global vars for head and tail of linked list, initialize to null
block_t *head = NULL;
block_t *tail = NULL;


// use first fit implementation to find a block with sufficient memory
block_t *firstFit(size_t s) {
   
   // working block for recurring, set it equal to the head at first (null or first block in list)
   block_t *workingBlock = head;
   // recur, check if it fits, if not keep going
   while(workingBlock) {
     if(workingBlock->free && workingBlock->size >= s) {
         return workingBlock;
     }
     // keep recurring if the size is not sufficient
     workingBlock = workingBlock->next; 
   }
   // return null if nothing works
   return NULL;
}


void *mymalloc(size_t s) {

 // if the size is null, stop here
 if(!s) {
     return NULL;
  }

 // set the newblock equal to result of our first fit function
 block_t *newBlock;
 newBlock = firstFit(s);
 // if first fit isn't null, then we have the new block of memory, return it and make it no longer free
 if(newBlock != NULL) {
   newBlock->free = 0;
    debug_printf("malloc %zu bytes\n", s);
   return (void*)(newBlock + 1);
 }
 // else, first fit returned null, we need to allocate a new block for the list
 else if(newBlock == NULL) {
 // new memory we will need
 size_t newSize;
 newSize = sizeof(block_t) + s;
 // temporary void to act as casing for calling sbrk
 void *tmp;
 // make sure to use the new size when we allocate the memory
 tmp = sbrk(newSize);
 
 // if sbrk didn't work (error), return null
 if (tmp == (void*) -1) {
   return NULL;
 }
 // else, it worked, add newBlock here at the bottom, instantiate its fields
 newBlock = tmp;
 newBlock->size = s;
 newBlock->free = 0;
 newBlock->next = NULL;
 // if the head is null, set it equal to newBlock
 if (!head) {
   head = newBlock;
 }
 // if the tail isn't null, set its next to newBlock for a loop
 if (tail) {
   // tail = newBlock;
   tail->next = newBlock;
 }
 // set the tail equal to newBlock (assumes its null);
 tail = newBlock;
 debug_printf("malloc %zu bytes\n", s);
 // return the newBlock
 return (void*)(newBlock + 1);
 }
}
 
void *mycalloc(size_t nmemb, size_t s) {
 // make sure neither of the inputs are null
 if(!nmemb || !s) {
     return NULL;
  }
  // get the new size by multiplying s and nmemb   
  size_t newSize;
  newSize = nmemb * s;
    // new temporary block, void for casing, will hold the position of the newBlock;
  void *tmp;
  tmp = mymalloc(newSize);
  // if the malloc failed, return null
  if(!tmp) {
      return NULL;
  }
  // using memset here to add 0s where necessary
  memset(tmp, 0, newSize);
  debug_printf("calloc %zu bytes\n", s);
  return tmp;
}


void myfree(void *ptr) {
  // make sure the given pointer is valid, if not stop func
  if(!ptr) {
     return;
  }
  // make a workingBlock, instantiate it to the block that we want to free
  block_t *workingBlock;
  workingBlock = (block_t*)ptr - 1;
  // use this temporary block to fix the connections of our linked list as we free one of the blocks
  block_t *fixCons;
  // start at the head
  fixCons = head;
  // while its not null, recur and make sure the list is linked correctly
  while(fixCons) {
    // if the next block after head is tail, set tail equal to the head (or the cons), this will fix the connections
    if (fixCons->next == tail) {
	 tail = fixCons;
    }
    // recur for the next block in list (after the head)
    fixCons = fixCons->next;
  }
  // for mem freed, print out mem size of working block (the one freed)
  debug_printf("Freed %zu bytes\n", workingBlock->size);
  workingBlock->free = 1;
}
