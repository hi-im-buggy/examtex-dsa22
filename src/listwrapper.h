#ifndef __INCLUDE_LIST_WRAPPER_H
#define __INCLUDE_LIST_WRAPPER_H
// Will generate a set of wrapper functions given the data type

#include "list.h"

#define CAT_EXPAND(a, b) a##b
#define CAT(a, b)                                                              \
	CAT_EXPAND(a, b) // indirection required to force macro expansion

#define GENERATE_LIST_WRAPPER(DATA_TYPE)                                       \
	void CAT(DATA_TYPE, ListAppend)(list * self, DATA_TYPE data)               \
	{                                                                          \
		listAppend(self, &data);                                               \
	}                                                                          \
                                                                               \
	void CAT(DATA_TYPE, ListInsertAt)(list * self, unsigned index,             \
									  DATA_TYPE data)                          \
	{                                                                          \
		listInsertAt(self, index, &data);                                      \
	}                                                                          \
                                                                               \
	void CAT(DATA_TYPE, listDeleteAt)(list * self, unsigned index)             \
	{                                                                          \
		listDeleteAt(self, index);                                             \
	}                                                                          \
                                                                               \
	DATA_TYPE CAT(DATA_TYPE, ListAt)(list * self, unsigned index)              \
	{                                                                          \
		return *(DATA_TYPE *)listAt(self, index);                              \
	}

// ALL wrapper functions must be generated here in order to prevent double
// declaration of functions. Make sure that the specidied data type is
// accessible from this file (include if necessary)
GENERATE_LIST_WRAPPER(int);

typedef struct __test_struct {
	int a;
	char c;
} test_struct;

GENERATE_LIST_WRAPPER(test_struct);

#endif // __INCLUDE_LIST_WRAPPER_H