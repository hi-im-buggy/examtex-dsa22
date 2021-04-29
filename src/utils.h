#ifndef __UTILS_H
#define __UTILS_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

char *stripWhitespace(char *, int *);
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

struct __Question__
{
    int hashq;              // stores the hash value of the question text
    char * type;            // defaults to MCQ for version 1 (type = "MCQ")
    char * text;            // has the text of the question
    double difficulty;      // stores the difficulty level of the question (max = 1)
    int no_options;         // stores the number of options for the question
    char ** options;        // contains the options in an array of strings
    char * correct_option;  // stores the correct option of the question
};

typedef struct __Question__ Question_B; 
#define MAX_SIZE_OPTION 1000

#endif
