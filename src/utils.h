#ifndef __UTILS_H
#define __UTILS_H

// PSEUDOCODE //
// while(reading lines):
//     strip_whitespace(line) // strip from the ends only
//
//     check if line starts with "\question"
//            set in_question
//
//       if in_question && line starts with {
//            find '='
//                set equals_index
//            find '}'
//                set close_index
//
//            in_braces = false
//
//            // assign according to content in braces
//            assign(bef_equals, after_equals)
//
//
//    assign():
//        check bef_equals
//        call relevant function
// assign(question, string_before, string_after)

#include "interpreter.h"
typedef Question *Question_B;

void assign(Question_B question, char string_before[], char string_after[]);
void assignType(Question_B question, char *string_after);
void assignDiff(Question_B question, char *string_after);
void assignOpt(Question_B question, char *string_after);
void assignAns(Question_B question, char *string_after);
char *stripWhitespace(char *line, int *length);

#define MAX_SIZE_OPTION 1000

#endif
