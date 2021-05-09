#include <stdio.h>
#include <stdlib.h>

#include "interpreter.c"

int main()
{
    // Hardcoding the Question Bank

    int N = 13;
    Question_Bank *QB1 = (Question_Bank *)malloc(sizeof(Question_Bank));
    QB1->no_questions = N;
    QB1->questions = (Question **)malloc(N * sizeof(Question *));

    for (int i = 0; i < N; i++)
    {
        QB1->questions[i] = (Question *)malloc(sizeof(Question));
        Question *Q = QB1->questions[i];
        Q->hashq = rand();
        Q->type = (char *)malloc(3 * sizeof(char));
        Q->text = (char *)malloc(100 * sizeof(char));
        Q->correct_option = (char *)malloc(100 * sizeof(char));

        if (i < 10)
        {
            strcpy(Q->type, "MCQ");
            Q->no_options = 4;
            Q->options = (char **)malloc(Q->no_options * sizeof(char *));
            for (int j = 0; j < Q->no_options; j++)
                Q->options[j] = (char *)malloc(20 * sizeof(char));
        }

        if(i >= 10)
            strcpy(Q->type, "FIB");        
    }

    QB1->questions[0]->text = "Who is the founder of Haryanka Dynasty ?";
    QB1->questions[0]->options[0] = "Ajatashatru";
    QB1->questions[0]->options[1] = "Harshavardhan";
    QB1->questions[0]->options[2] = "Bimbisara";
    QB1->questions[0]->options[3] = "Ghananand";
    QB1->questions[0]->correct_option = "Bimbisara";
    QB1->questions[0]->difficulty = 0.2;

    QB1->questions[1]->text = "The Rowlatt act was passed in ?";
    QB1->questions[1]->options[0] = "1905";
    QB1->questions[1]->options[1] = "1913";
    QB1->questions[1]->options[2] = "1919";
    QB1->questions[1]->options[3] = "1925";
    QB1->questions[1]->correct_option = "1919";
    QB1->questions[1]->difficulty = 0.6;

    QB1->questions[2]->text = "East India association was set up in ?";
    QB1->questions[2]->options[0] = "1866";
    QB1->questions[2]->options[1] = "1857";
    QB1->questions[2]->options[2] = "1836";
    QB1->questions[2]->options[3] = "1885";
    QB1->questions[2]->correct_option = "1866";
    QB1->questions[2]->difficulty = 0.5;

    QB1->questions[3]->text = "Where was Ajeetnath Tirthankar born ?";
    QB1->questions[3]->options[0] = "Ayodhya";
    QB1->questions[3]->options[1] = "Kishkintha";
    QB1->questions[3]->options[2] = "Nasik";
    QB1->questions[3]->options[3] = "Ujjain";
    QB1->questions[3]->correct_option = "Ayodhya";
    QB1->questions[3]->difficulty = 0.4;

    QB1->questions[4]->text = "Which Kushana ruler patronised Buddhism ?";
    QB1->questions[4]->options[0] = "Ashoka";
    QB1->questions[4]->options[1] = "Vikramaditya";
    QB1->questions[4]->options[2] = "Kanishka";
    QB1->questions[4]->options[3] = "Kautilya";
    QB1->questions[4]->correct_option = "Kanishka";
    QB1->questions[4]->difficulty = 0.3;

    QB1->questions[5]->text = "During whose reign did Gandhara school of art blossom ?";
    QB1->questions[5]->options[0] = "Harsha";
    QB1->questions[5]->options[1] = "Ashok";
    QB1->questions[5]->options[2] = "Kanishka";
    QB1->questions[5]->options[3] = "Chandragupta-II";
    QB1->questions[5]->correct_option = "Kanishka";
    QB1->questions[5]->difficulty = 0.9;

    QB1->questions[6]->text = "Babur was born in the year ?";
    QB1->questions[6]->options[0] = "1483";
    QB1->questions[6]->options[1] = "1583";
    QB1->questions[6]->options[2] = "1693";
    QB1->questions[6]->options[3] = "1783";
    QB1->questions[6]->correct_option = "1483";
    QB1->questions[6]->difficulty = 0.5;

    QB1->questions[7]->text = "Babur came to India from ?";
    QB1->questions[7]->options[0] = "Khiva";
    QB1->questions[7]->options[1] = "Ferghana";
    QB1->questions[7]->options[2] = "Khorasan";
    QB1->questions[7]->options[3] = "Seistan";
    QB1->questions[7]->correct_option = "Ferghana";
    QB1->questions[7]->difficulty = 0.7;

    QB1->questions[8]->text = "Which dynasty did Babur rule ?";
    QB1->questions[8]->options[0] = "Mughal";
    QB1->questions[8]->options[1] = "Nanda";
    QB1->questions[8]->options[2] = "Maurya";
    QB1->questions[8]->options[3] = "Haryanka";
    QB1->questions[8]->correct_option = "Mughal";
    QB1->questions[8]->difficulty = 0.1;

    QB1->questions[9]->text = "Babur was succeeded by ?";
    QB1->questions[9]->options[0] = "Sher Shah";
    QB1->questions[9]->options[1] = "Akbar";
    QB1->questions[9]->options[2] = "Humayun";
    QB1->questions[9]->options[3] = "Bahadur Shah";
    QB1->questions[9]->correct_option = "Humayun";
    QB1->questions[9]->difficulty = 0.8;

    QB1->questions[10]->text = "Full form of GUI is ________.";
    QB1->questions[10]->correct_option = "Graphical User Interface";
    QB1->questions[10]->difficulty = 0.5;

    QB1->questions[11]->text = "_________ refers to physical tangible components of a computer.";
    QB1->questions[11]->correct_option = "Hardware";
    QB1->questions[11]->difficulty = 0.8;

    QB1->questions[12]->text = "OS stands for _________.";
    QB1->questions[12]->correct_option = "Operating System";
    QB1->questions[12]->difficulty = 0.4;

    User_Parameters *UP1 = (User_Parameters *)malloc(sizeof(User_Parameters));
    UP1->type = (char *)malloc(4 * sizeof(char));
    strcpy(UP1->type, "BOTH");
    UP1->difficulty = 0.6;
    UP1->no_questions = 3;
    strcpy(UP1->comparator, "<=");

    /*
    printf("\n***** ----- Question Bank ----- *****\n\n");
    print_QuestionPaper(QB1->questions, N);
    printf("\n***** ----- End of Question Bank ----- *****\n\n");
    */

    // printf("\n***** ----- Question Bank ----- *****\n");
    // print_QuestionPaper(QB1->questions, QB1->no_questions);
    // printf("\n***** ----- End ----- *****\n");

    int size = get_Questions(UP1, QB1);
    // printf("\n***** ----- Selected Questions ----- *****\n");
    // print_QuestionPaper(Question_collection, size);
    // printf("\n***** ----- End ----- *****\n");

    create_QuestionPaper(Question_collection, size, UP1->no_questions);
    // printf("\n***** ----- Question Paper ----- *****\n");
    print_QuestionPaper(QP, UP1->no_questions);
    // printf("\n***** ----- End ----- *****\n");

    /*
    printf("\n***** ----- Question Paper ----- *****\n\n");
    print_QuestionPaper(QP, UP1->no_questions);
    printf("\n***** ----- End of Question Paper ----- *****\n\n");
    */
}