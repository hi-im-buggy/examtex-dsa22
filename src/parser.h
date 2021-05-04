#ifndef __INCLUDE__PARSER_H
#define __INCLUDE__PARSER_H

#include <stdbool.h>

#define INIT_STRING_SIZE 10
#define MAX_LINE_SIZE 200
#define MAX_NUM_QUESTIONS 100
#define QN_STRING "\\question"
#define TOKEN_DELIMITERS "="

typedef struct __parser_state parser_state;
struct __parser_state {
	bool in_question;
	int line_number;
};

#endif // __INCLUDE__PARSER_H
