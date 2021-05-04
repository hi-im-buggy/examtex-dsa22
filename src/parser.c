#include "utils.h"
#include "parser.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

parser_state state;

Question_Bank parse_file(FILE *fstream)
{
	state.in_question = false;
	state.line_number = 0;

	Question_Bank ret_qb;
	ret_qb.no_questions = 0;
	ret_qb.questions = malloc( sizeof(Question *) * MAX_NUM_QUESTIONS);
	// Currently, the limit on the number of questions is hard-coded


	Question *cur_qn;

	size_t line_size = MAX_LINE_SIZE;
	char *line = (char *) malloc( line_size * sizeof(char) );

	do {
		// read a line from the file and find brackets
		fgets(line, line_size, fstream);
		state.line_number++;
		
		// we're in the question if question string was found at start of line
		if ( (state.in_question == false) && (strstr(line, QN_STRING) == line) ) {
			state.in_question = true;

			// allocate memory for the current qn
			cur_qn = (Question *) malloc( sizeof(Question) );
		}

		// we're out of the question if we encounter a blank line
		else if ( isBlankLine(line) && (state.in_question == true) ) {
			state.in_question = false;

			// once we're out of the question, add it to the question bank
			*(ret_qb.questions + ret_qb.no_questions) = cur_qn;
			ret_qb.no_questions++;

			// and invalidate cur_qn now
			cur_qn = NULL;
		}

		else {
			char *bracket_open = strchr(line, '{');
			char *bracket_close = strchr(line, '}');

			if (bracket_open == NULL || bracket_close == NULL || bracket_open > bracket_close) {
				fprintf(stderr, "Error: mismatched/missing brackets on line %d!\n", state.line_number);
				exit(EXIT_FAILURE);
			}

			// generate the substring in between {}
			size_t sublen = (size_t) (bracket_close - bracket_open + 1);
			char *substr = malloc( (sublen + 1) * sizeof(char));
			// +1 in first line because close and open point to the start of each char
			// +1 in the second line to account for null terminator

			memcpy(substr, bracket_open, sublen);
			substr[sublen] = '\0'; // null terminate

			// tokenize the substring, before and after delim
			char *pre_token = strtok(line, TOKEN_DELIMITERS);
			char *post_token = strtok(NULL, TOKEN_DELIMITERS);

			if (cur_qn == NULL) {
				fprintf(stderr, "Error: unexpected error occured at line %d!\n", state.line_number);
				exit(EXIT_FAILURE);
			}

			// clean the substrings and call assign
			else {
				int pre_token_length = strlen(pre_token), post_token_length = strlen(post_token);
				char *pre_token_sanitized = stripWhitespace(pre_token, &pre_token_length);
				char *post_token_sanitized = stripWhitespace(post_token, &post_token_length);

				assign(cur_qn, pre_token_sanitized, post_token_sanitized);
			}
		}

	} while (line != NULL);

	return ret_qb;
}
