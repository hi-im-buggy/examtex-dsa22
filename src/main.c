#include "interpreter.h"
#include "list.h"
#include "listwrapper.h"
#include "parser.h"
#include "utils.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *const argv[])
{
	// in_file is the file from which the question bank is read
	// up_file is the file from which the user parameters are read
	char *in_file = NULL, *up_file = NULL;
	FILE *instream = stdin;
	FILE *upstream = NULL;

	// parse commandline arguments
	int opt;
	while ((opt = getopt(argc, argv, "i:u:o:")) != -1) {
		switch (opt) {
		case 'i': in_file = optarg; break;
		case 'u': up_file = optarg; break;
		case 'h':
		default:
			fprintf(
				stderr,
				"\nUsage: %s -i [question bank file] -u [user params file]\n\n",
				argv[0]);
			return 0;
		}
	}

	if (optind > argc && argc != 1) {
		fprintf(stderr, "Expected argument after options\n");
		return 0;
	}

	if (in_file != NULL)
		instream = fopen(in_file, "r");

	if (up_file != NULL)
		upstream = fopen(up_file, "r");

	Question_Bank qb = parse_qb_file(instream);

	User_Parameters_Set ups = parse_up_file(upstream);

	extern Question **Question_collection;
	extern Question **QP;

	printf("# Question Paper\n\n");

	int num_qualified_questions;
	for (int i = 0; i < ups.no_params; i++) {
		num_qualified_questions = get_Questions(ups.params + i, &qb);

		create_QuestionPaper(Question_collection, num_qualified_questions,
							 ups.params[i].no_questions);

		print_QuestionPaper(QP, ups.params[i].no_questions);
	}

	printf("----------------------\n");
	printf("End of question paper\n");

	return 0;
}
