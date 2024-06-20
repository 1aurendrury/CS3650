/*
 * Queue implementation.
 *
 * - Implement each of the functions to create a working circular queue.
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your queue 
 *   functions. 
 *
 */
#include <assert.h>
#include <stdlib.h>

#include "queue.h"
 
/* The main data structure for the queue. */
struct queue{
  unsigned int back;      /* The next free position in the queue
                           * (i.e. the end or tail of the line) */
  unsigned int front;     /* Current 'head' of the queue
                           * (i.e. the front or head of the line) */
  unsigned int size;      /* How many total elements we currently have enqueued. */
  unsigned int capacity;  /* Maximum number of items the queue can hold */
  long *data;             /* The data our queue holds  */
};

/** 
 * Construct a new empty queue.
 *
 * Returns a pointer to a newly created queue.
 * Return NULL on error
 */
queue_t *queue_new(unsigned int capacity) {

  // Instantiate q, and allocate memory based on size of queue_t
  queue_t *q = malloc(sizeof(queue_t));
  // Instantiate the data field, and allocate memory based on the size of each index (a long)
  // and the number of indices (the capacity)
  q->data = malloc(sizeof(long) * capacity);

  // Call this before the program terminates
  // i.e. delete the queue allocated memory if the data is empty/has been freed
  if(q->data == 0) {
	queue_delete(q);
  }
  // Use parameter to instantiate capacity
  q->capacity = capacity;
  // Set everything equal to 0 as it is an empty queue
  q->back = 0;
  q->front = 0;
  q->size = 0;

  return q;
  queue_delete(q);
}

/**
 * Check if the given queue is empty.
 *
 * Returns a non-0 value if the queue is empty, 0 otherwise.
 */
int queue_empty(queue_t *q) {
  assert(q != NULL);

  if (q->size == 0) {
	// Return 1 if the queue is empty
  	  return 1;
  }
  else {
	  // Return 0 if the queue is not empty
	return 0;
  }
 
}

/**
 * Check if the given queue is full.
 *
 * Returns a non-0 value if the queue is full, 0 otherwise.
 */
int queue_full(queue_t *q) {
  assert(q != NULL);

  if (q->capacity == q->size) {
	// Return 1 when queue is full
	  return 1;
  }
  else {
	  // Return 0 if the queue is not full
	return 0;
  }
 
}

/** 
 * Enqueue a new item.
 *
 * Push a new item into our data structure.
 */
void queue_enqueue(queue_t *q, long item) {
  assert(q != NULL);
  assert(q->size < q->capacity);

  // Increase the size by 1
  q->size = q->size + 1;
  // Set the last item in the queue to be the new item
  q->data[q->back] = item;
  // Change the index of the back to the added item. Use modulo here because it will set the back 
  // index to be (q->back + 1) as long as it is within the capacity of the queue (which must be the
  // case based on assertion).
  q->back = (q->back + 1) % q->capacity;
	
}


/**
 * Dequeue an item.
 *
 * Returns the item at the front of the queue and removes an item from the 
 * queue.
 *
 * Note: Removing from an empty queue is an undefined behavior (i.e., it could 
 * crash the program)
 */
long queue_dequeue(queue_t *q) {
  assert(q != NULL);
  assert(q->size > 0);
	
  	// get the item at the front of the queue
	long item = q->data[q->front];
	// Move front up by one. Use modulo here because if the capacity is greater than the next 
	// element (q->front + 1) (which should always be the case), 
	// then it will correctly set the next element as the new front. 
	q->front = (q->front + 1) % q->capacity;
	// Reduce the size by 1
	q->size = q->size - 1;
	// Return the dequeued item
	return item;
  	
}

/** 
 * Queue size.
 *
 * Queries the current size of a queue (valid size must be >= 0).
 */
unsigned int queue_size(queue_t *q) {
  assert(q != NULL);
	// Return the size of the given queue q
	return q->size;
}

/** 
 * Delete queue.
 * 
 * Remove the queue and all of its elements from memory.
 *
 * Note: This should be called before the proram terminates.
 */
void queue_delete(queue_t* q) {
  assert(q != NULL);

    // Free both the data inside inside q and q itself. Don't need to free each element of data
    // because each index isn't a pointer (unlike strings/char*'s)
    free(q->data);
    free(q);
}

