#include "utils.h"

#include <ctype.h>
#include <stdio.h>

void assign(Question_B question, char string_before[], char string_after[])
{
	// we can use toupper() to make strings independent of whether its BLOCK
	// letters or not
	if (strcmp(string_before, "Type") == 0)
		assignType(question, string_after);
	else if (strcmp(string_before, "Difficulty") == 0)
		assignDiff(question, string_after);
	else if (strcmp(string_before, "Opt") == 0)
		assignOpt(question, string_after);
	else if (strcmp(string_before, "Ans") == 0)
		assignAns(question, string_after);

	return;
}

void assignType(Question_B question, char *string_after)
{
	// we now know its to be set for type
	int Len = strlen(string_after);
	for (int i = 0; i < Len; i++) {
		string_after[i] = toupper(string_after[i]);
		// we are making sure MCQ or McQ or Mcq or mCQ all give same
	}
	question.type = string_after;

	return;
}

void assignDiff(Question_B question, char *string_after)
{
	// we have the values of the format 0.xyz..., which we have to carefully
	// convert
	int Len = strlen(string_after);
	// no.of digits is Len - 2;   (0 and ".")
	double value = 0;
	for (int i = 2; i < Len; i++) {
		value = value + string_after[i];
		value = value * 10;
	}
	// this we'll have value = the number xyz....
	// to make it decimal divide it with 10^(len-1)
	value = value / pow(10, Len - 1);
	question.difficulty = value;

	return;
}

void assignOpt(Question_B question, char *string_after)
{
	// we have options of format abcdef,ghijkl,mnopq,lolkma etc
	// first we need to know the number of options, for this we can check by
	// number of commas
	int Len = strlen(string_after);
	int CommaCount = 0;
	for (int i = 0; i < Len; i++) {
		if (string_after[i] == ',')
			CommaCount++;
	}
	// no,of options is No.of commas +1
	CommaCount++;
	// Now this is the count of options.
	char **array;
	question.no_options = CommaCount;
	// we have comma count no.of options, so we can make an array of arrays
	char OptArray[CommaCount][MAX_SIZE_OPTION]; // let max size of options be
												// MAX SIZE OPTION
	int i = 0, Index, j = 0;
	for (Index = 0; Index < Len; Index++) {
		char temp = string_after[Index];
		if (temp = ',') {
			i++;
			j = 0;
		} // we are moving to next row if encounter a comma and resetting index
		  // inside row (j)

		else {
			OptArray[i][j] = temp;
			j++;
		}
	}
	question.options = OptArray;

	return;
}

void assignAns(Question_B question, char *string_after)
{
	question.correct_option = string_after;
	return;
}

// strips the input line of any trailing and leading whitespae
// returns the stripped string and modifies length accordingly
char *stripWhitespace(char *line, int *length)
{
	if (line == NULL) {
		fprintf(stderr, "Invalid string passed to stripWhitespace()!\n");
		return NULL;
	}

	// a local variable to avoid constant dereferencing
	int len = *length;
	int start_index = 0, end_index = len; // length assumed accessible
	char cur;

	// find the first non whitespace character from the start
	cur = line[start_index];
	while (isspace(cur)) {
		start_index++;
		cur = line[start_index];

		if (start_index > len) {
			fprintf(stderr, "Unexpected error in stripWhitespace()!\n");
			break;
		}
	}

	// find the first non whitespace character from the start
	cur = line[end_index];
	while (isspace(cur)) {
		end_index--;
		cur = line[end_index];

		if (end_index < 0) {
			fprintf(stderr, "Unexpected error in stripWhitespace()!\n");
			break;
		}
	}

	if (start_index > end_index) {
		fprintf(stderr, "Unexpected error in stripWhitespace()!\n");
		return NULL;
	}

	len = end_index - start_index + 1;
	char *ret_string = (char *)malloc((len + 1) * sizeof(char));

	// copy the new string in
	for (int i = 0; i < len; i++) {
		ret_string[i] = line[start_index + i];
	}

	ret_string[len] = '\0'; // null terminate
	*length = len;			// update the length

	return ret_string;
}