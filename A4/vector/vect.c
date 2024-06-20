/**
 * Vector implementation.
 *
 * - Implement each of the functions to create a working growable array (vector).
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your vector 
 *   functions.
 *
 * IMPORTANT: The initial capacity and the vector's growth factor should be 
 * expressed in terms of the configuration constants in vect.h
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/** Main data structure for the vector. */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

/** Construct a new empty vector. */
vect_t *vect_new() {

  // Instantiate a new empty vector with an allocated memory of vect_t
  vect_t *v = malloc(sizeof(vect_t));
  // Size starts out at 0
  v->size = 0;
  // Initial capacity is a variable in vect.h
  v->capacity = VECT_INITIAL_CAPACITY;
  // Instantiate the data, which will have an allocated memory of v->capacity number of char*'s
  v->data = malloc(sizeof(char*) * v->capacity);
  // Before program terminates, free the vector (assuming the data has already been deleted/freed)
  if(v->data == 0) {
	free(v);
  }
  // Return the vector
  return v;
}

/** Delete the vector, freeing all memory it occupies. */
void vect_delete(vect_t *v) {
	
	// Free each index of the data (must free each index because it is a string (aka each index
	// is a char pointer)
	for(int i = 0; i < v->size; i++) {
		free(v->data[i]);
	}
	// Free the data memory itself
	free(v->data);
	// Free the vector
	free(v);


}

/** Get the element at the given index. */
const char *vect_get(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  // Assuming the index is valid, return that char* at that index in the data
  if (v->size > idx) {
	return v->data[idx];
  }
}

/** Get a copy of the element at the given index. The caller is responsible
 *  for freeing the memory occupied by the copy. */
char *vect_get_copy(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

 // Allocate new memory for the copy of the element
 char *element = malloc(sizeof(char*));
 // If the index is valid, copy the element at that index in data and put this copy at the element
 // variable we just created
  if (v->size > idx) {
	strcpy(element, v->data[idx]);
  }
  // Return then free the copy
  return element;
  free(element);
}

/** Set the element at the given index. */
void vect_set(vect_t *v, unsigned int idx, const char *elt) {
  assert(v != NULL);
  assert(idx < v->size);

  // Wrap the given element as a char*
  char* newelement = (char*) elt;
  // If the index is valid, free the pre-existing memory at that index in data, and then allocate 
  // space, copy the given element and place it at the index  
  if (v->size > idx) {
		free(v->data[idx]);
		// Allocate space for elt in data at idx
		v->data[idx] = malloc(strlen(newelement) + 1);
		// Copy the new string
		strcpy(v->data[idx], newelement);
		
	}
}

/** Add an element to the back of the vector. */
void vect_add(vect_t *v, const char *elt) {
  assert(v != NULL);

  // If the size is equal to the capacity, then we must reallocate space in the data array
  if(v->size == v->capacity){
	// Double the capacity of the vector (this increase is arbitrary)  
  	v->capacity = v->capacity * 2;
	// Reallocate space in v->data
	// i.e double the capacity and thus double length of the array, add more memory available for
	// the data array
	v->data = realloc(v->data, sizeof(char *) * v->capacity);
  }
  // Now to add the new element
  // Allocate space for elt in data at index v->size (last spot)
  v->data[v->size] = malloc(strlen(elt) + 1);
  // Copy the string
  strcpy(v->data[v->size], elt);
  // Increase the size of vector by 1 since we added a new element
  v->size = v->size + 1;
}
	

/** Remove the last element from the vector. */
void vect_remove_last(vect_t *v) {
  assert(v != NULL);

  	// Free the element of the last spot in the data array, and delete it
	free(v->data[v->size - 1]);
	// Reduce the size of the vector by 1 to signify the new number of elements in data array
	v->size = v->size - 1;
}

/** The number of items currently in the vector. */
unsigned int vect_size(vect_t *v) {
  assert(v != NULL);

  // Return the size of the given vector
  return v->size;
}

/** The maximum number of items the vector can hold before it has to grow. */
unsigned int vect_current_capacity(vect_t *v) {
  assert(v != NULL);

  // Return the capacity of the given vector
  return v->capacity;
}

