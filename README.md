# ExamTex (Team 22)

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

### Contribution guidelines
- Keep the `master` branch clean and deployable. When introducing new features
  or attempting to fix bugs, use a different branch.
- Make a pull request once you feel a branch is ready to be merged with
  `master`. Once your code has been reviewed by at least one other team member
  and approved, and there are no merge conflicts, it can be merged into
  `master`.
- If you notice any problems in code that has already been merged into master,
  please use 'issues' on GitHub to bring attention to it.

### Style guidelines
- Use `camelCase` for functions, `snake_case` for variables, and `BLOCKCASE`
  for macros definitions. This makes it easier to keep track of the different
  pieces in the code.
- Use `clang-format -i <file-name>` to format a file to match a consistent
  code style in terms of white-space.

### Using the 'list' container
'list' is a generic container to act as a dynamic array, similar to C++'s
vector template.  Functions like `listAppend()`, `listInsertAt()`,
and `listDeleteAt()` are available to modify data held in a list.

Lists must be initialized first with the size of the data type they will be used to store.
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
