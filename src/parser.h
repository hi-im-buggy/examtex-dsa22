#ifndef __INCLUDE__PARSER_H
#define __INCLUDE__PARSER_H

#include <stdbool.h>
#define INIT_STRING_SIZE 10
#define QN_STRING = "question"
#define LEN_QUESTION_STRING 8

typedef struct __parser_state parser_state;
struct __parser_state {
	bool in_question;
	bool in_braces;
};

#endif // __INCLUDE__PARSER_H
