/*
Autheor: Dacheng Lin (Link)
Name: AI_Answering and Creating Plist file
Copyright © 2019 Dacheng Lin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Declare the Global variables
const int INPUT_SIZE = 100;
const int QUESTION_SIZE = 3;
const int ANSWER_SIZE = 3;
const string INPUT_FILE = "questions.txt";
const string OUTPUT_FILE = "answers.txt";

// Defining the Class

class Finding_Answers
{
public:
        void Question_section();
        // Post-condition: The user's question will be receive and
        // it will be broken down to different keywords and they wil
        // stored into another string array.The number of the key
        // words will be saved.

        void Matching_Questions(string File_Questions[]);
        // Pre-condition : The array of the keywords for matching the
        // questions will be filled based on the user's input.

        // Post-condition: The keywords in the string array will used
        // to find the matched question in the array of file questions
        // and the index of the matched question will be kept.

        void Outputing_Answers(string File_Answers[]);
        // Post-condition: The correct answer(based on the index of the
        // question in file) will be outputed to the screen.


private:
        // Finding Keywords
        string Question, Modified_Words;
        string Question_num, file_question;
        string Key_words[INPUT_SIZE];
        int index_question = 0;
        int index_file_question = 0;
        int Matching_value = 0;
        int Max_Matching_value = 0;
        int Matched_index = 0;
        int Current_matched_index;
        bool Key_Word_FOUND = false;

        // Output Answers
        string File_answers;

};


int main()
{
    Finding_Answers user_questions, found_answers;
    bool loop = true;

    // Testing Arrays
    string Questions[] = {"where is pcc", "who is ashraf", "what clubs should i join"};
    string Answers[] = {"Right here! ", "A CS professor! ", "MESA! "};

    // Testing driver
    do
    {
        // Input Section
        user_questions.Question_section();

        // Processing
        user_questions.Matching_Questions(Questions);

        // Output
        user_questions.Outputing_Answers(Answers);

     }while(loop);
    return 0;

}


//----------------------------------------------------------Input Questions
void Finding_Answers::Question_section()
{
    cout << "Please enter your question below: \n";
        getline (cin,Question);

        // Add a space at the end to prevent the loss of words during
        // the storing keyword section

        Question += " ";

        // Break down users's questions into key words and store them
        // into the string array
        for( int index = 0; index < Question.length(); index++)
        {
            // Case 1: White Space / Question Mark / The last character
            // Checking all the spaces and the end of the string in order
            // to store different key words
            if (isspace(Question[index]) ||  Question[index] == '?' ||
                index == (Question.length() -1))
            {
                // Don't store the key words when it comes to these words
                if (Modified_Words == "is" || Modified_Words == "are"
                 || Modified_Words == "it" || Modified_Words == "he"
                 || Modified_Words == "he" || Modified_Words == "she"
                 || Modified_Words == "they" || Modified_Words == "the"
                 || Modified_Words == "that" || Modified_Words == "this"
                 || Modified_Words == "these" || Modified_Words == "those"
                 || Modified_Words == "his" || Modified_Words == "her"
                 || Modified_Words == "its" )
                {
                    Modified_Words = "";
                }

                // Store the Key words into the array
                // when the string is not empty or when it reaches the end of
                // string
                if (!Modified_Words.empty() || index == (Question.length() -1) )
                {
                    Key_words[index_question] = Modified_Words;

                    // Increase the index size for the array
                    if (!Modified_Words.empty())
                        index_question++;
                }

                // Reset the string for the words after hitting spaces
                Modified_Words = "";

            }

            // Case 2: Normal Characters
            // Read each character before hitting the space
            // and store them into the string(ALL Lower Case)
            else
            {
                tolower(Question[index]);
                Modified_Words += (Question[index]);
            }

        }

        // Testing***********************************
        //for (string X: Key_words)
        //    cout << X << endl;

}


//---------------------------------------------------------Matching Questions
void Finding_Answers::Matching_Questions(string File_Questions[])
{
    // Declare the local variable
    int find_result;

    cout << index_question << endl;

    for (int count = 0; count < QUESTION_SIZE; count++ )
    {
        // Read file questions in the array
        file_question = File_Questions[count];

        // Reset the Matching value for every loop
        Matching_value = 0;
        Key_Word_FOUND = false;

        // Testing (Details)******************************
        // cout << file_question << endl;

        for(unsigned int index = 0; index < index_question; index++)
        {
            // See the result of searching keywords
            find_result = file_question.find(Key_words[index]);

            // Matching keywords with file questions
            if( find_result > -1)
            {
               // Increase the Matching value of that line of question
               // When the finding result is positive and Save this
               Matching_value++;
               Current_matched_index = index_file_question;
               Key_Word_FOUND = true;
            }

        }

        // Testing (Details)****************************************
        // cout << Matching_value <<"  "<< index_file_question << endl;

        // CASE 1: If previous Key words Matching value is bigger than the
        // current Matching value, store the previous question index
        if (Matching_value > Max_Matching_value && Key_Word_FOUND)
        {
            Matched_index = Current_matched_index;
            Max_Matching_value = Matching_value;

        }

        // Counting the index for the questions in the file
        index_file_question++;
    }



}

//----------------------------------------------Output Matched Answer
void Finding_Answers::Outputing_Answers(string File_Answers[])
{

    for (int count = 0; count < ANSWER_SIZE; count++)
    {
        // Read the answers in the array
        File_answers = File_Answers[count];

        // If the index of the answers matches with the
        // Found Matched index of the question
        // Output that answer to the user
        if (count == Matched_index)
        {
            cout << File_answers;
        }

    }


    // Reset Everything for the repetition
    Matched_index = 0;
    index_question = 0;
    index_file_question = 0;
    Matching_value = 0;
    Max_Matching_value = 0;
    Matched_index = 0;

}

/* Sample Run:
Last login: Mon Jun  3 17:49:49 on ttys000
Dachengs-MacBook-Air:~ dachenglink$ source /var/folders/m6/mrkkrvy95fj56v9vxx51s7yr0000gn/T/tmpaS4qZe
Please enter your question below:
where is pcc
2
Right here! Please enter your question below:
who is ashraf
2
A CS professor! Please enter your question below:
what clubs i join?
4
MESA! Please enter your question below:
*/


