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
- Make a pull request once you feel a branch is ready to be merged with `master`.
  Once your code has been reviewed by at least one other team member and
  approved, and there are no merge conflicts, it can be merged into `master`.
- If you note any problems code that has already been merged into master, please use
  'issues' on GitHub to bring attention to those parts

### Style guidelines
- Use `camelCase` for functions, `snake_case` for variables, and `BLOCKCASE`
  for macros definitions. This makes it easier to keep track of the different
  pieces in the code.
- Use `clang-format -i <file-name>` to format a file to match a consistent
  code style in terms of white-space.
