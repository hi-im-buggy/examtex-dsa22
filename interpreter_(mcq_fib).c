#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "interpreter.h"

int comparator_fn_type(char question_type[], User_Parameters* UP)
{
	// B is the difficulty level specified by the user
	// A is the difficulty level of the question

	if (!(strcmp(UP->type, "BOTH")))
		return 1;

	else (!strcmp(UP->type, question_type)))
		return 1;

	
}

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

/*
// This data is to be obtained from parser
// Dummy Function
Question_Bank * get_QuestionBank(int n, Question * questions)
{
	Question_Bank * QB = (Question_Bank *) malloc(sizeof(Question_Bank) + (n *
sizeof(Question))); QB->no_questions = n; QB->questions = questions; return QB;
}
*/

// This function gets input from user and creates the struct User_Parameter
// and also returns it
// version 1 only MCQs
User_Parameters *get_UserParameters()
{
	User_Parameters *UP = (User_Parameters *)malloc(sizeof(User_Parameters));
	//strcpy(UP->type, "MCQ");
	scanf("%s",UP->type);

	int n;
	printf("Enter number of questions : ");
	scanf("%d", &n);
	UP->no_questions = n;

	double difficulty;
	printf("Enter the difficulty level : ");
	scanf("%lf", &difficulty);

	int choice;
	printf("Enter the condition : \n");
	printf("1. PRESS 1 FOR EQUAL TO\n");
	printf("2. PRESS 2 FOR LESS THAN\n");
	printf("3. PRESS 3 LESS THAN EQUAL TO\n");
	printf("4. PRESS 4 GREATER THAN\n");
	printf("5. PRESS 5 GREATER THAN EQUAL TO\n");
	scanf("%d", &choice);

	printf("Creating a Question Paper of %d questions : \n", n);
	printf("Question type ==> MCQ\n");
	printf("difficulty level ==> ");

	switch (choice) {
	case 1:
		strcpy(UP->comparator, "==");
		printf("equal to ");
		break;

	case 2:
		strcpy(UP->comparator, "<");
		printf("lesser than ");
		break;

	case 3:
		strcpy(UP->comparator, "<=");
		printf("lesser than equal to ");
		break;

	case 4:
		strcpy(UP->comparator, ">");
		printf("greater than ");
		break;

	case 5:
		strcpy(UP->comparator, ">=");
		printf("greater than equal to ");
		break;
	}

	printf("%0.1lf.\n", difficulty);

	return UP;
}

Question **Question_collection;

// stores the questions (in an array) which meet the requirement of the user
int get_Questions(User_Parameters *UP, Question_Bank *QB)
{
	int curr_size = 1;
	int incr_size = 1;
	Question_collection = (Question **)malloc(curr_size * sizeof(Question *));

	double diffA;
	double diffB = UP->difficulty;
	char typeA[6];
	//char typeB[6];


	int i = 0;
	int j = 0;
	
	for (int i = 0; i < QB->no_questions; i++) {

		diffA = QB->questions[i]->difficulty;
		
		strcpy(typeA,QB->questions[i]->type);
		int check_diff=comparator_fn_diff(diffA, diffB, UP->comparator);
		int check_type=comparator_fn_type(typeA,UP->type);
		if ((check_diff==1)&&(check_type==1)) {
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

Question **QP;

int create_QuestionPaper(Question **Question_collection, int size, int N)
{
	srand(time(0));
	QP = (Question **)malloc(N * sizeof(Question *));

	int i = 0;
	int index;
	int j;
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

		QP[i] = (Question *)malloc(sizeof(Question));
		QP[i] = Question_collection[j];
		free(Question_collection[j]);
		i++;
	}

	return 0;
}

// QP is the question paper to be printed out ...

int print_QuestionPaper(Question **QuestionPaper, int N)
{
	for (int i = 0; i < N; i++) {
		printf("%d. \n", i + 1);
		printf("%s\n", QuestionPaper[i]->text);
		for (int j = 0; j < QuestionPaper[i]->no_options; j++) {
			printf("%d %s\n", (j + 1), QuestionPaper[i]->options[j]);
		}
		printf("\n");
	}
	return 0;
}