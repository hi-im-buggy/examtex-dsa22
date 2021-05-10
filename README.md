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
