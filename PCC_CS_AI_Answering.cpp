/*
Autheor: Dacheng Lin (Link)
Name: AI_Answering (PCC CS Department)
Copyright © 2019 Dacheng Lin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Declare the Global variables
const int INPUT_SIZE = 100;
const int QUESTION_SIZE = 100;
const int ANSWER_SIZE = 100;
const int COMMON_WORDS_SIZE = 56;
const string QUESTION_FILE = "questions.txt";
const string ANSWER_FILE = "answers.txt";
const string COMMON_WORDS[COMMON_WORDS_SIZE] =
                              {"is", "are", "it", "he","her", "they",
                              "the", "that", "this", "these", "those",
                              "his", "her", "its", "for", "of", "from",
                              "do", "does", "did", "on", "if", "in", "at",
                              "or", "to", "a", "beside", "an", "by", "have",
                              "has", "i", "me", "will", "would", "while",
                              "than","though", "through", "make", "made",
                              "therefore", "however", "out", "again",
                              "hence", "still", "thus", "so", "yet",
                              "then", "before", "after", "however",
                              "indeed"};



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

void Store_File_Sentences(ifstream & infile, string sentences[],
                          const int QUESTION_SIZE, string file);
// Pre-condition : The function will receive a input file and
//                 all the line sentences will be read.
// Post-condition: The sentence on each line will be stored in
//                 the array based on the maxuimum string size.

int main()
{
    // Declare the classs
    Finding_Answers user_questions;

    // Declare the I/O stream and Variables
    ifstream fin;
    bool loop = true;

    // Testing Arrays
    string Questions[QUESTION_SIZE];
    string Answers[ANSWER_SIZE];

    // Testing driver
    do
    {
        // Store the Questions AND Answers in the files into arrays
        Store_File_Sentences(fin,Questions,QUESTION_SIZE,QUESTION_FILE);
        Store_File_Sentences(fin,Answers,ANSWER_SIZE,ANSWER_FILE);

        // Input Section
        user_questions.Question_section();

        // Testing
        for (string x: Questions)
            cout << x << endl;

        // Processing
        user_questions.Matching_Questions(Questions);

        // Output
        user_questions.Outputing_Answers(Answers);

     }while(loop);

    return 0;

}

//-----------------------------------------------------------------
void Store_File_Sentences(ifstream & infile, string sentences[],
                          const int QUESTION_SIZE, string file)
{
    // Declare the local variables
    string file_question;
    string line_number;
    int index_questions = 0;

    infile.open(file);

    if(infile.fail())
    {
        cout << "Sorry. The file doesn't exist.\n\n";
        exit(1);
    }

    while(!infile.eof() && index_questions < QUESTION_SIZE)
    {
        // Read the Numbers of Questions and Answers
        infile >> line_number;

        // Read every line in the file and output it
        getline (infile,file_question);

        // Store in the array
        sentences[index_questions] = file_question;

        // Increase the index
        index_questions++;
    }

    infile.close();
}


//----------------------------------------------------------Input Questions
void Finding_Answers::Question_section()
{
    cout << "Hello~Welcome to PCC CS Department!\n";
    cout << "Please enter your question below: \n";
    getline (cin,Question);
    cout << endl;

    // Add a space at the end to prevent the loss of words during
    // the storing keyword section

    Question += " ";

        // Break down users's questions into key words and store them
        // into the string array
        for( int index = 0; index < Question.length(); index++)
        {
            // Case 1: Special Punctuations/ The last character
            // Checking all the spaces and the end of the string in order
            // to store different key words
            if (isspace(Question[index]) ||  Question[index] == '?' ||
                index == (Question.length() -1) || Question[index] == ','
                || Question[index] == '.')
            {
                // Don't store the key words when it comes to these common words
                for (int index2 = 0; index2 < COMMON_WORDS_SIZE; index2 ++)
                {
                    if (Modified_Words == COMMON_WORDS[index2])
                    {
                        Modified_Words = "";
                    }
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
                Modified_Words += tolower(Question[index]);
            }

        }

        // Testing***********************************
        for (string X: Key_words)
            cout << X << endl;

}


//---------------------------------------------------------Matching Questions
void Finding_Answers::Matching_Questions(string File_Questions[])
{
    // Declare the local variable
    int find_result;

    for (int count = 0; count < QUESTION_SIZE; count++ )
    {
        // Read file questions in the array
        file_question = File_Questions[count];

        // Reset the Matching value for every loop
        Matching_value = 0;
        Key_Word_FOUND = false;

        // Testing (Details)******************************
         cout << file_question << endl;

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
         cout << Matching_value <<"  "<< index_file_question << endl;

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

    // If the Highest matching value is not greater than one
    if (Max_Matching_value <= 1)
        cout << "Sorry. This question is not in the database:~)" << endl;

    // If the Highest match value is greater than one
    else
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
                cout << File_answers << endl;
            }

        }
    }

    // Reset Everything for the repetition
    Matched_index = 0;
    index_question = 0;
    index_file_question = 0;
    Matching_value = 0;
    Max_Matching_value = 0;
    Matched_index = 0;

    cout << endl;
}

/* Sample Run:
Last login: Tue Jun  4 01:19:43 on ttys000
source /var/folders/m6/mrkkrvy95fj56v9vxx51s7yr0000gn/T/tmppZcbL2
Dachengs-Air:~ dachenglink$ source /var/folders/m6/mrkkrvy95fj56v9vxx51s7yr0000gn/T/tmppZcbL2
Hello~Welcome to PCC CS Department!
Please enter your question below:
hello, how are you

 Halooo...I feel great right now! I am glad that you are here: )

Hello~Welcome to PCC CS Department!
Please enter your question below:
what do you like

 I like All of the Pop-songs and raps, and I like to listen to classic music and jazz too.

Hello~Welcome to PCC CS Department!
Please enter your question below:
what is pcc

 Pasadena city college PCC is the best community college in the Los Angeles.

Hello~Welcome to PCC CS Department!
Please enter your question below:
where is pcc

 1570 E. Colorado Blvd. Pasadena, CA 91106

Hello~Welcome to PCC CS Department!
Please enter your question below:
what is favorite food

 My favorite food is seafood! Especially sockeye salmon!

Hello~Welcome to PCC CS Department!
Please enter your question below:
who is dacheng lin / link?

 He's my boss, and I always wish him good luck for his future career on computer science and music:D...Don't tell him that I like you more than him... Haha:D jkjk

Hello~Welcome to PCC CS Department!
Please enter your question below:
what is C++

 In C++ class, you can learn about Problem-solving through structured programming of algorithms on computers using the basics of the C++ object-oriented language. Includes variables, expressions, input/output (I/O), branches, looping constructs, functions, argument passing, single and double dimensional arrays, strings, file I/O, C++ vectors, software design principles, testing, and debugging techniques.

Hello~Welcome to PCC CS Department!
Please enter your question below:
where should i study

 I would recommend that you study in the library, it is very quiet, there are plenty of seats, and there are restrooms on each floor!

Hello~Welcome to PCC CS Department!
Please enter your question below:
how can i succeed

 To succeed in this discipline, an aspiring student must seek to obtain a strong high school background in math and science, build strategic-thinking skills, develop strong oral and written communication skills and develop her/his ability to work in a team environment.

Hello~Welcome to PCC CS Department!
Please enter your question below:
what is superpower?

Sorry. This question is not in the database:~)

Hello~Welcome to PCC CS Department!
Please enter your question below:
*/


