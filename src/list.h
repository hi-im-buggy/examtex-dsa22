#ifndef __INCLUDE_LIST_H
#define __INCLUDE_LIST_H

#include <stddef.h>
#define INIT_BUF_SIZE 8

typedef struct __list list;
struct __list {
	void *buf; // actual pointer to the memory
	size_t mem; // memory used
	size_t size_elem; // the size of a single element
	unsigned num_elems; // number of elements
	char empty; // 1 byte flag

};

// function pointers for abstraction
void list_init(list *, size_t); // initialize the list
void list_destroy(list *); // free all memory associated with the list
void list_append(list *, void *); // add an element at the end of the list
void list_insertAt(list *, unsigned, void *); // insert an element at given index
void list_deleteAt(list *, unsigned); // delete an element at the given index
void *list_at(list *, unsigned); // return a pointer to element at an index
void list_expand(list *); // increase the memory for the container if needed
void list_shrink(list *); // decrease the memory for the container if needed

// the do-while construct only runs once, and makes sure the macro doesn't face
// issues with semicolons placed after it when it is called
#define NULL_ERROR(name) \
	do { fprintf(stderr, "Error: %s called with invalid list!\n", #name); } while (0)

#endif // __INCLUDE_LIST_H
