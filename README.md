# ExamTex (Team 22)
### Group members
#### Rahothvarman P (2020114008)
Worked on the Interpreter for MCQs.

#### Lenka Charan Sahit (2020101011)
Worked on the Interpreter for FIB type questions.

#### Pratyaksh Gautam (2020114002)
Worked on the Parser skeleton and wrote the `list` functions.

#### Akash Vallamsetty (2020102050)
Worked on test cases and documentation, and output formatting.

#### Sai Namrath Polakampalli (2020101063)
Worked on the utility functions used by the parser, including `assign()` and related functions.

## Important files and major contributors
- `src/interpreter.c`: Rahothvarman and Charan
- `src/list.c`: Pratyaksh
- `src/main.c`: Pratyaksh and Akash
- `src/parser.c`: Pratyaksh and Namrath
- `src/utils.c`: Namrath

## Usage
First, clone the repo and build the project.

```
git clone https://github.com/hi-im-buggy/examtex-dsa22
cd examtex-dsa22
mkdir bin;
make
```

Now, the program can be used as such
```
bin/examtex -i <question_bank_file> -u <user_params_file>
```

This will generate the question paper and print it to `stdout`.

## Input file format
This implementation of the 'examtex' language has a strict requirement of only
one curly brace assignment per line, and a blank line to separate question
blocks.  
It is freely able to handle 'MiXeD cAse' and excess trailing and leading
whitespaces without errors.

The general syntax for the question bank file can be seen here
```
\question
{type = mcq}
{difficulty = 0.2}
{text = C is a language}
{opt=Functional,Procedural,Objects,Events}
{ans=Functional}
```

The general syntax for the user parameters file can be seen here
```
\sample
{type = mcq}
{difficulty <= 0.2}
{number = 5}
```

## Design overview
### Parser
The parser has been designed in a generalized manner for the most part,
but the two types of input files, question bank and user parameters,
have been parsed separately.  
Since the line containing the "difficulty" directive in the user parameters
contains two pieces of information, the target difficulty and the comparator,
it also had to be dealt with specially.

In general however, the parser simply takes in one line of input,
keeps track of whether it is in a question block and the line numbers
of the files, and calls `assign()` from utils for the assignment
in case of question bank files, and handles it locally in case of
user parameter files. It also raises errors where possible.


### Utils
The functions involved in the Utils are :

```c
void assign(Question_B question, char string_before[], char string_after[]);
void assignType(Question_B question, char *string_after);
void assignDiff(Question_B question, char *string_after);
void assignOpt(Question_B question, char *string_after);
void assignAns(Question_B question, char *string_after);
char *stripWhitespace(char *line, int *length);
bool isBlankLine(char *line);
int hashString(const char *str);
int insertString(const char *str, int n, string_node *hashtable[]);
int findString(const char *str, int n, string_node *hashtable[]);
```

#### 1. __assign( )__

- This is the key function for the working of Parser
  and acts as the link between Interpreter and Parser, by manipulating the input data read by Parser
  and Storing it in the Data  Structures, which the Interpreter uses to analyse.
- This is a common function for all the major types of Data that is necessary for Question Bank Questions.
- Takes the Pointer to `Question Bank Data Structure, Pre-Sanitized token and Post-Sanitized tokens` as Input.
- Depending on the Pre-Sanitized and Post-Sanitized Tokens, that are passed into the function,
  It stores the given data and uses it as a standard for comparison in Interpreter.
- This function can act independent of the Case of the Alphabets passed into it while storing.
  Ex : It stores MCQ , Mcq , mCQ , McQ - all as the same string, to ensure that Capitalisation-Errors do not cause issues.
- This function extends upto 3 types of Questions : MCQ & FIB & T/F
  (Out of which T/F at the moment is not distinguished as a new Type in the Interpreter as it can be considered as a type of MCQ)
- This function calls the remaining Util functions, depending on the tokens passed into it from the Parser.

#### 2. __assignType( )__


- This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
- Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
- This function is used to store the type of question that is being stored in the Data Structure.
- The type plays a key role in making sure that we get the required genre of questions on the Output.
- This function extends upto 3 types of Questions : MCQ & FIB & T/F.

#### 3. __assignDiff( )__

- This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
- Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
- This function is used to store the difficulty of question that is being stored in the Data Structure.
- The difficulty plays a key role in making sure that we get questions at the required difficulty levels on the Output.
- It reads a string as input, and manually converts it into a double variable,
  which consists of the actual difficulty of the question by iterating through it.

#### 4. __assignOpt( )__

- This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
- Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
- This function is used to store the options for the question that is being stored in the Data Structure.
- This function is useful in distinguishing between the Option Storing mechanisms, Basing on the Type of Question.
- It uses iteration to find the number of options being provided and stores that as well,
  making it easier and clear for the Interpreter to work with.
- Stores all the Option Strings in an array of strings.

#### 5. __assignAns( )__

- This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
- Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
- This function is used to store the Right Answer for the question being stored in the Data Structure.
- It stored the Post-Sanitized token as the answer.

#### 6. __stripWhitespace( )__

- This function acts as a error-correction technique.
- It basically checks and detects irregular white spaces in the Parsed String and
  Resolves it by extracting only the Non-whiteSpace String.
- Ex: This function converts ` Testing ` into `Testing`.   *(Emphasis on the Blank Space)*
- Takes Pointer to the String and Length of the String as Input Arguments.
- Returns the new extracted String as output.

#### 7. __isBlankLine( )__

- This is a very simple function which checks and tells whether
  a line of string being passed into it is Empty Line or has some text.
- Takes the Pointer to the Line String as input.
- works like a toggle (Bool).

#### 8. __hashString() ,insertString(), findString()__

  - These three functions are useful to Hash the Input Text for the question, which ensures that the questions do not repeat.
  - We use a Hash Table to make sure this is implemented properly.
  - We've used Separate Chaining in implementing the hashing.
  - We're Inserting the String in O(1) and Finding the String is O(1) time, which is very convenient.



So, In this way, each of the functions mentioned above are a part of the Utils and operate as a medium between Parser and Interpreter.  
Utils is the part of the program which controls the manipulation and storage of the Input Data that is provided by the User to Parser.

### Interpreter

#### Interpreter.c
This is the header file for the interpreter.c of the project. It contains the structs ???Question???, the ???Question_Bank??? and the ???User_Parameter???. The struct Question contains information about the question such as the text, options, and the final answer. The struct Question_Bank contains the collection of questions in an array and also has a variable to store the total number of questions. The User_Parameter struct stores the requirements and the conditions for the final question paper.

#### Interpreter.c

This file contains the functions which are used to create the final question paper from the large question bank following the requirements of the user. 

####  The functions involved in the Interpreter are :

```c
int comparator_fn_diff(double A, double B, char comparator[2]);
int comparator_fn_type(char *Question_type, User_Parameters *UP);
int get_Questions(User_Parameters *UP, Question_Bank *QB);
int create_QuestionPaper(Question **Question_collection, int size, int N);
int print_QuestionPaper(Question **QuestionPaper, int N);
```

####    1.get_Questions:
The get_Questions function takes the struct User_Parameter and struct Question_Bank as parameters and chooses ???all??? the questions that satisfy the given conditions of type and difficulty and store them in an array of struct questions. 

  Time Complexity: 
  As we traverse through the whole Question_Bank in a loop the time complexity would be O(N).

####    2.comparator_fn_diff:
For checking if the questions satisfy our conditions in the get_Questions function we use two functions in the get_Questions function which are comparator_fn_diff and comparator_fn_type. The comparator_fn_diff takes the difficulty level of the question and the difficulty level asked in the question paper and a comparator for deciding which comparator to use, to compare both the difficulties. It returns 1 if the required condition is satisfied.

	Time Complexity:
	This takes O(1) time as it is just comparing two variables.

####    3.comparator_fn_type:
Similarly, this function takes the question type and the User_Parameter struct as parameters to compare the type of the question and the required type. It returns 1 if the required condition is satisfied.

	Time Complexity:
	This also takes O(1) time as it is just comparing two variables.

####    4.create_QuestionPaper:
We have already chosen the questions that follow our type and difficulty level. This function picks randomly the number of questions (using the rand and srand in time.h) that the user wants and while picking we take care of repetitions by using a hash table, and puts these questions into the final QP struct (the question paper struct). 

  Time Complexity: We traverse through the while loop till we have the required number of questions and also we might also have to traverse for the linear probing (can't be more than N) so the total time complexity would be O(N*N).
	
####    Data Structures used:

The data structures which are mainly used are structs and arrays of structs. We have also used Hashtables to ensure that the questions are not repeated.

### Marks: Further Scope
Considering the future design of the project, the parser has been written in a
general manner and the code is reusable by only changing `assign()` function.
Thus, the code is flexible enough to allow for more types of questions in the
future by modifying the functions in utils and interpreter.

As for the marks, since questions store the correct option, it is only a matter
of taking the input from the students, which can be done right after printing (like in moodle xD),
comparing against the correct option, and using the difficulty to give marks on the basis of
a metric like the weighted average.

The marks thus collected can be displayed or further analysed (maybe to consider
the accuracy of question difficulty).

### Using the 'list' container

'list' is a generic container to act as a dynamic array, similar to C++'s
vector template.  Functions like `listAppend()`, `listInsertAt()`,
and `listDeleteAt()` are available to modify data held in a list.

A set of wrappers for specific data types can be generated, which call
underlying generic functions.  
In both cases,
a list `l` must be initialized with `listInit(&l, sizeof(data_type)`
and destroyed after use with `listDestroy(&l)`

#### Wrappers

For the wrapper functions, add the line `GENERATE_LIST_WRAPPER(data_type)`
near the end of `src/listwrapper.h`. The data type must itself be accessible
from the headerfile. See for example:

```c
// in listwrapper.h
typedef struct __test_struct {
	int a;
	char c;
} test_struct;

GENERATE_LIST_WRAPPER(test_struct);
```
The struct was declared in place so is accessible, and a set of wrappers
for it is generated.

```c
#include "listwrapper.h"
#include <stdio.h>

int main()
{
	list l;
	listInit(&l, sizeof(test_struct));

	for (int i = 0; i < 10; i++) {
		test_struct cur;
		cur.a = i;
		cur.c = 'a' + i;
		test_structListAppend(&l, cur);
	}

	for (int i = 0; i < 10; i++) {
		test_struct out = test_structListAt(&l, i);
		printf("%d %c\n", out.a, out.c);
	}
	putchar('\n');

	listDestroy(&l);
	return 0;
}
```

#### Generics

For accessing data stored in a list, `listAt()` is used, which returns a `void` pointer to the specified index.
This pointer must be typecast to the correct data type to be used properly.

```c
#include "list.h"

list l;
listInit(&l, sizeof(int)); // a list to store integers
int x = 10;
listAppend(&l, &x); // a pointer to the data must be passed
// (l.num_elements == 1) and l.empty is false
int y = *(int *)listAt(&l);
// the pointer returned is typecast and dereferenced
// now (y == 10)
listDeleteAt(&l, 0);
// (l.num_elems == 0) and l.empty is true
listDestroy(&l); // free the memory associated with the list
```

## Contribution guidelines

- Keep the `master` branch clean and deployable. When introducing new features
  or attempting to fix bugs, use a different branch.
- Make a pull request once you feel a branch is ready to be merged with
  `master`. Once your code has been reviewed by at least one other team member
  and approved, and there are no merge conflicts, it can be merged into
  `master`.
- If you notice any problems in code that has already been merged into master,
  please use 'issues' on GitHub to bring attention to it.

### Directory structure

The project directory structure is organised as follows:
```
./
?????? src/
???  ?????? /* Contains source files */
?????? tests/
???  ?????? /* Contains tests for the program */
?????? bin/
???  ?????? /* Contains binary files (ignored by git) */
?????? README.md
?????? Makefile
?????? .gitignore
```
