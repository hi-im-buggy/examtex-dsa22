#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void listInit(list *self, size_t size_elem)
{
	if (self == NULL) {
		NULL_ERROR(append);
		return;
	}

	self -> empty = true;
	self -> num_elems = 0;
	// initialize the list with INIT_BUF_SIZE elements worth of space self -> size_elem = size_elem;
	self -> size_elem = size_elem;
	self -> buf = calloc(INIT_BUF_SIZE, self -> size_elem);
	self -> mem = INIT_BUF_SIZE * self -> size_elem;

	if ( (self -> buf) == NULL ) {
		fprintf(stderr, "Error: malloc() returned null in init()!\n");
		return;
	}

}

void listAppend(list *self, void *data)
{
	if (self == NULL) {
		NULL_ERROR(append);
		return;
	}
	else if (data == NULL) {
		fprintf(stderr, "Error: append() called with invalid data!\n");
		return;
	}

	if (self -> empty) {
		self -> empty = false;
	}

	void *start = self -> buf + (self -> size_elem * self -> num_elems);
	void *limit = self -> buf + self -> mem;

	if (start >= limit) {
		fprintf(stderr, "Error: insufficient memory to append element while calling append()!\n");
		return;
	}

	memmove(start, data, self -> size_elem);
	self -> num_elems++;
	listExpand(self);
}

void listInsertAt(list *self, unsigned index, void *data)
{
	if (self == NULL) {
		NULL_ERROR(insertAt);
		return;
	}

	// note that if index == num_elems, it's equivalent to appending
	else if (index > self -> num_elems) {
		fprintf(stderr, "Error: invalid index used while calling insertAt()!\n");
		return;
	}

	if (self -> empty) {
		self -> empty = false;
	}

	// move elements after index to make room for the element
	void *before_move = self -> buf + (self -> size_elem * index);
	void *after_move = before_move + self -> size_elem;
	memmove(after_move, before_move, (self -> num_elems - index) * self -> size_elem);

	// copy the elements data into the space we just made
	memmove(before_move, data, self -> size_elem);
	self -> num_elems++;
	listExpand(self);
}

void listDeleteAt(list *self, unsigned index)
{
	if (self == NULL) {
		NULL_ERROR(deleteAt);
		return;
	}
	
	else if (index >= self -> num_elems) {
		fprintf(stderr, "Error: invalid index used while calling deleteAt()!\n");
		return;
	}

	// perform the deletion by moving elements right after the index back by one
	void *before_move = self -> buf + (self -> size_elem * (index + 1) );
	void *after_move = before_move - self -> size_elem;
	memmove(after_move, before_move, (self -> num_elems - index - 1) * self -> size_elem);

	self -> num_elems--;
	listShrink(self);
	
	if (self -> num_elems == 0) {
		self -> empty = true;
	}
}

void *listAt(list *self, unsigned index)
{
	if (self == NULL) {
		NULL_ERROR(at);
		return NULL;
	}

	else if (index >= self -> num_elems) {
		fprintf(stderr, "Error: invalid index used while calling at()!\n");
		return NULL;
	}

	void *retval = self -> buf + (self -> size_elem * index);
	return retval;
}

// used to maintain that the list has space for at least twice as many elements
// as the current number of elements
void listExpand(list *self)
{
	if (self == NULL) {
		NULL_ERROR(expand);
		return;
	}

	// double the list memory if needed
	if ( (self -> mem) < 2 * (self -> num_elems) * (self -> size_elem) ) {
		self -> mem = 2 * self -> mem;
		self -> buf = realloc(self -> buf, self -> mem);
	}
	if ( (self -> buf) == NULL ) {
		fprintf(stderr, "Error: malloc() returned null in expand()!\n");
		return;
	}
}

// shrink the array if it can store more than 4 times the number of elements
// as the current number of elements
void listShrink(list *self)
{
	if (self == NULL) {
		NULL_ERROR(shrink);
		return;
	}

	if ( (self -> mem) > 4 * (self -> num_elems) * (self -> size_elem) ) {
		self -> mem = self -> mem / 2;
		self -> buf = realloc(self -> buf, self -> mem);
	}

	if ( (self -> buf) == NULL ) {
		fprintf(stderr, "Error: malloc() returned null in expand()!\n");
		return;
	}
}

void listDestroy(list *self)
{
	if (self == NULL) {
		NULL_ERROR(destroy);
		return;
	}

	if (self -> buf != NULL)
		free(self -> buf);
}
