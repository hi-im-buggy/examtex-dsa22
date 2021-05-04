#ifndef INTERPRETER_H
#define INTERPRETER_H

struct Question {
	int hashq;		   // stores the hash value of the question text
	char *type;		   // defaults to MCQ for version 1 (type = "MCQ")
	char *text;		   // has the text of the question
	double difficulty; // stores the difficulty level of the question (max = 1)
	int no_options;	   // stores the number of options for the question
	char **options;	   // contains the options in an array of strings
	char *correct_option; // stores the correct option of the question
};

typedef struct Question Question;

struct Question_Bank {
	int no_questions; // stores the number of questions in this question bank
	Question **questions; // Array of pointers to "struct Question pointers"
};

typedef struct Question_Bank Question_Bank;

struct User_Parameters {
	char *type;			// defaults to MCQ for version 1 (type = "MCQ")
	double difficulty;	// difficulty level which the user requires
	int no_questions;	// number of questions which the user needs
	char comparator[2]; // can be "==", "<", "<=", ">", ">="
};

typedef struct User_Parameters User_Parameters;

#endif
