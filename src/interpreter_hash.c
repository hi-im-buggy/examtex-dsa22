#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.c"
#include "interpreter.h"

#define HASH 1007

Question **Question_collection;
Question **QP;

// returns 1 if the user requirement is fulfilled
int comparator_fn_diff(double A, double B, char comparator[2])
{
	// B is the difficulty level specified by the user
	// A is the difficulty level of the question

	if (!(strcmp(comparator, "==")))
		return (A == B);

	else if (!(strcmp(comparator, "<")))
		return (A < B);

	else if (!(strcmp(comparator, "<=")))
		return (A <= B);

	else if (!(strcmp(comparator, ">")))
		return (A > B);

	else
		return (A >= B);
}

// returns 1 if the user requirement is fulfilled (else 0)
int comparator_fn_type(char *Question_type, User_Parameters *UP)
{
	if (!(strcmp(UP->type, "BOTH")))
		return 1;

	if (!(strcmp(UP->type, Question_type)))
		return 1;

	return 0;
}

// stores the questions (in an array) which meet the requirement of the user
int get_Questions(User_Parameters *UP, Question_Bank *QB)
{
	int curr_size = 1;
	int incr_size = 1;

	Question_collection = NULL;

	Question_collection = (Question **)malloc(curr_size * sizeof(Question *));

	double diffA;
	double diffB = UP->difficulty;

	int check_diff, check_type;

	int i = 0;
	int j = 0;
	for (int i = 0; i < QB->no_questions; i++) {
		diffA = QB->questions[i]->difficulty;
		check_diff = comparator_fn_diff(diffA, diffB, UP->comparator);
		check_type = comparator_fn_type(QB->questions[i]->type, UP);

		if (check_diff && check_type) {
			// increment the size of array to avoid overflow
			if (j == curr_size) {
				curr_size = curr_size + incr_size;
				Question_collection = (Question **)realloc(
					Question_collection, curr_size * sizeof(Question *));
			}

			Question_collection[j] = (Question *)malloc(sizeof(Question));
			Question_collection[j] = QB->questions[i];
			j++;
		}
	}

	return j;
}

string_node **hash_Table;

int create_QuestionPaper(Question **Question_collection, int size, int N)
{
	srand(time(0));

	QP = NULL;

	if (size >= N) {
		QP = (Question **)malloc(N * sizeof(Question *));

		int i = 0;
		int index = 0;
		int j = 0;

		while (i < N) {
			index = rand() % size;

			// using linear probing to randomly pick a question
			if (Question_collection[index] == NULL) {
				int k = 0;
				j = (index + 1) % size;
				while (k < size) {
					if (Question_collection[j] != NULL)
						break;
					j = (j + 1) % size;
					k++;
				}
			}

			else
				j = index;

			if (findString(Question_collection[j]->text,HASH, hash_Table)==0)
            {
                insertString(Question_collection[j]->text, HASH, hash_Table);
                QP[i] = (Question *)malloc(sizeof(Question));
        	    QP[i] = Question_collection[j];
			    Question_collection[j] = NULL;
			    i++;
            }

            int k=0;
            int ct=0;

            while (k<size)
            {
                if (Question_collection[k]!=NULL)
                {
                    ct=1;
                    break;

                }
                k++;                    
            }
            
            if (ct==0)
            {
                printf("No more questions available!\n");
                break;
            }
            
            
		}
	}

	else {
		printf("Not enough Questions.\n");
		QP = NULL;
	}

	return 0;
}

// QP is the question paper to be printed out ...
// Dummy Function
int print_QuestionPaper(Question **QuestionPaper, int N)
{
	if (QuestionPaper != NULL) {
		for (int i = 0; i < N; i++) {
			printf("%d. \n", i + 1);
			printf("%s\n", QuestionPaper[i]->text);
			if (!(strcmp(QuestionPaper[i]->type, "MCQ"))) {
				for (int j = 0; j < QuestionPaper[i]->no_options; j++) {
					printf("%d %s\n", (j + 1), QuestionPaper[i]->options[j]);
				}
			}
			printf("\n");
		}
	}

	else
		printf("NO QUESTIONS TO DISPLAY\n");

	return 0;
}