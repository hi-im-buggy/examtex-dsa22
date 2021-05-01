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

	size_t line_size = MAX_LINE_SIZE;
	char *line = (char *) malloc( line_size * sizeof(char) );

	do {
		// read a line from the file and find brackets
		fgets(line, line_size, fstream);
		state.line_number++;
		
		if ( (state.in_question == false) && (strstr(line, QN_STRING) != NULL) ) {
			state.in_question = true;
		}

		// TODO add is_empty function in utils
		else if (/* the whole line is spaces */ false) {
			;
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

			memcpy(substr, (bracket_open), sublen);
			substr[sublen] = '\0'; // null terminate

			// TODO
			// tokenize the substring
			// call assign
		}

	} while (line != NULL);

	return ret_qb;
}
