#ifndef __INCLUDE__PARSER_H
#define __INCLUDE__PARSER_H

#include <stdbool.h>

#define INIT_STRING_SIZE 10
#define QN_STRING "\\question"
#define MAX_LINE_SIZE 200

typedef struct __parser_state parser_state;
struct __parser_state {
	bool in_question;
	int line_number;
};

#endif // __INCLUDE__PARSER_H
