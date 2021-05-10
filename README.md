 ## _**A brief report on Util Functions involved in DSA-ExamTeX-22 Project**_
                                    

 ###   The functions involved in the Utils are :
    ```c
    void assign(Question_B question, char string_before[], char string_after[])
    void assignType(Question_B question, char *string_after)
    void assignDiff(Question_B question, char *string_after)
    void assignOpt(Question_B question, char *string_after)
    void assignAns(Question_B question, char *string_after)
    char *stripWhitespace(char *line, int *length)
    bool isBlankLine(char *line)```

####    1. __assign( )__

        - This is the key function for the working of Parser and acts as the link between Interpreter and Parser, by manipulating the input data read by Parser and Storing it in the Data Structures, which the Interpreter uses to analyse.
        - This is a common function for all the major types of Data that is necessary for Question Bank Questions.
        - Takes the Pointer to `Question Bank Data Structure, Pre-Sanitized token and Post-Sanitized tokens` as Input. 
        - Depending on the Pre-Sanitized and Post-Sanitized Tokens, that are passed into the function, It stores the given data and uses it as a standard for comparison in Interpreter.
        - This function can act independent of the Case of the Alphabets passed into it while storing.
        Ex : It stores MCQ , Mcq , mCQ , McQ - all as the same string, to ensure that Capitalisation-Errors do not cause issues.
        - This function extends upto 3 types of Questions : MCQ & FIB & T/F (Out of which T/F at the moment is not distinguished as a new Type in the Interpreter as it can be considered as a type of MCQ)
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
        - It reads a string as input, and manually converts it into a double variable, which consists of the actual difficulty of the question by iterating through it.
        
####    4. __assignOpt( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the options for the question that is being stored in the Data Structure.
        - This function is useful in distinguishing between the Option Storing mechanisms, Basing on the Type of Question.
        - It uses iteration to find the number of options being provided and stores that as well, making it easier and clear for the Interpreter to work with.
        - Stores all the Option Strings in an array of strings.
    
####    5. __assignAns( )__

        - This is one of the many Sub-Data Assigning Functions that operate on the `assign()` Function.
        - Takes Pointer to Question Bank Data Structure , Post-Sanitized Token as Input arguments.
        - This function is used to store the Right Answer for the question being stored in the Data Structure.
        - It stored the Post-Sanitized token as the answer.

####    6. __stripWhitespace( )__

        - This function acts as a error-correction technique.
        - It basically checks and detects irregular white spaces in the Parsed String and Resolves it by extracting only the Non-whiteSpace String.
        - Ex: This function converts ` Testing ` into `Testing`.   *(Emphasis on the Blank Space)*
        - Takes Pointer to the String and Length of the String as Input Arguments.
        - Returns the new extracted String as output.

####    7. __isBlankLine( )__

        - This is a very simple function which checks and tells whether a line of string being passed into it is Empty Line or has some text.
        - Takes the Pointer to the Line String as input.
        - works like a toggle (Bool).


- So, In this way, each of the functions mentioned above are a part of the Utils and operate as a medium betwee Parser and Interpreter.
- Utils is the part of the program which controls the manipulation and storage of the Input Data that is provided by the User to Parser.
