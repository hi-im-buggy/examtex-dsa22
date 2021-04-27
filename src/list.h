#ifndef __INCLUDE_LIST_H
#define __INCLUDE_LIST_H

#include <stdbool.h>
#include <stddef.h>

#define INIT_BUF_SIZE 8

typedef struct __list list;
struct __list {
	void *buf; // actual pointer to the memory
	size_t mem; // memory used
	size_t size_elem; // the size of a single element
	unsigned num_elems; // number of elements
	bool empty; // boolean flag

};

void listInit(list *, size_t); // initialize the list
void listDestroy(list *); // free all memory associated with the list
void listAppend(list *, void *); // add an element at the end of the list
void listInsertAt(list *, unsigned, void *); // insert an element at given index
void listDeleteAt(list *, unsigned); // delete an element at the given index
void *listAt(list *, unsigned); // return a pointer to element at an index
void listExpand(list *); // increase the memory for the container if needed
void listShrink(list *); // decrease the memory for the container if needed

// the do-while construct only runs once, and makes sure the macro doesn't face
// issues with semicolons placed after it when it is called
#define NULL_ERROR(name) \
	do { fprintf(stderr, "Error: %s called with invalid list!\n", #name); } while (0)

#endif // __INCLUDE_LIST_H
