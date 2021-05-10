# ExamTex (Team 22)

## Usage
First, clone the repo and build the project.

```
git clone https://github.com/hi-im-buggy/examtex-dsa22
cd examtex-dsa22
mkdir bin
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
void assign(Question_B question, char string_before[], char string_after[])
void assignType(Question_B question, char *string_after);
void assignDiff(Question_B question, char *string_after)
void assignOpt(Question_B question, char *string_after)
void assignAns(Question_B question, char *string_after)
char *stripWhitespace(char *line, int *length)
bool isBlankLine(char *line)
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


So, In this way, each of the functions mentioned above are a part of the Utils and operate as a medium between Parser and Interpreter.  
Utils is the part of the program which controls the manipulation and storage of the Input Data that is provided by the User to Parser.

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
├─ src/
│  └─ /* Contains source files */
├─ tests/
│  └─ /* Contains tests for the program */
├─ bin/
│  └─ /* Contains binary files (ignored by git) */
├─ README.md
├─ Makefile
└─ .gitignore
```
