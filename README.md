   ### Utils
                                    

 - ####  The functions involved in the Utils are :
 
    ```c
    void assign(Question_B question, char string_before[], char string_after[])
    void assignType(Question_B question, char *string_after);
    void assignDiff(Question_B question, char *string_after)
    void assignOpt(Question_B question, char *string_after)
    void assignAns(Question_B question, char *string_after)
    char *stripWhitespace(char *line, int *length)
    bool isBlankLine(char *line)```

####    1. __assign( )__

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
    
####    2. __assignType( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the type of question that is being stored in the Data Structure.
        - The type plays a key role in making sure that we get the required genre of questions on the Output.
        - This function extends upto 3 types of Questions : MCQ & FIB & T/F.

####    3. __assignDiff( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the difficulty of question that is being stored in the Data Structure.
        - The difficulty plays a key role in making sure that we get questions at the required difficulty levels on the Output.
        - It reads a string as input, and manually converts it into a double variable,
          which consists of the actual difficulty of the question by iterating through it.
        
####    4. __assignOpt( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the options for the question that is being stored in the Data Structure.
        - This function is useful in distinguishing between the Option Storing mechanisms, Basing on the Type of Question.
        - It uses iteration to find the number of options being provided and stores that as well, 
          making it easier and clear for the Interpreter to work with.
        - Stores all the Option Strings in an array of strings.
    
####    5. __assignAns( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the Right Answer for the question being stored in the Data Structure.
        - It stored the Post-Sanitized token as the answer.

####    6. __stripWhitespace( )__

        - This function acts as a error-correction technique.
        - It basically checks and detects irregular white spaces in the Parsed String and
          Resolves it by extracting only the Non-whiteSpace String.
        - Ex: This function converts ` Testing ` into `Testing`.   *(Emphasis on the Blank Space)*
        - Takes Pointer to the String and Length of the String as Input Arguments.
        - Returns the new extracted String as output.

####    7. __isBlankLine( )__

        - This is a very simple function which checks and tells whether 
          a line of string being passed into it is Empty Line or has some text.
        - Takes the Pointer to the Line String as input.
        - works like a toggle (Bool).


- So, In this way, each of the functions mentioned above are a part of the Utils and operate as a medium betwee Parser and Interpreter.
- Utils is the part of the program which controls the manipulation and storage of the Input Data that is provided by the User to Parser.

### INTERPRETER.H
This is the header file for the interpreter.c of the project. It contains the structs “Question”, the “Question_Bank” and the “User_Parameter”. The struct Question contains information about the question such as the text, options, and the final answer. The struct Question_Bank contains the collection of questions in an array and also has a variable to store the total number of questions. The User_Parameter struct stores the requirements and the conditions for the final question paper.

### INTERPRETER.C

This file contains the functions which are used to create the final question paper from the large question bank following the requirements of the user. 

####  The functions involved in the Interpreter are :

```c
int comparator_fn_diff(double A, double B, char comparator[2])
int comparator_fn_type(char *Question_type, User_Parameters *UP)
int get_Questions(User_Parameters *UP, Question_Bank *QB)
int create_QuestionPaper(Question **Question_collection, int size, int N)
int print_QuestionPaper(Question **QuestionPaper, int N)
```

####    1.get_Questions:
The get_Questions function takes the struct User_Parameter and struct Question_Bank as parameters and chooses “all” the questions that satisfy the given conditions of type and difficulty and store them in an array of struct questions. 

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