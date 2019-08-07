/*
Name: Derrick Ward
Class/Section: CIS 554
HW # 4
Description: This file is the implementation for the Math Pop Quiz Class
Date: 8/5/2019
*/

#include <iostream>
#include <string>
#include "MathPopQuiz.h"
#include <ctime>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::rand;
using std::string;
using std::time;


MathPopQuiz::MathPopQuiz() :correctAnswers{ 0 }, totalQuestions{ 0 }
{}

void MathPopQuiz::start()
{
    int playAgain = 1;

    // Greeting
    cout << "Welcome to Math Pop Quiz:" << endl;

    do {
        int difficultyNumber, mathQuestionTypeChoice;
        QuestionType questionType;

        // Prompt and get type of math question user wants
        cout << "Please enter one of the following integers to indicate which type of math questions you would like.\n1 - Add\n2 - Subtraction\n3 - Multiplication\n4 - Division\n5 - Random\nYour Choice: ";
        cin >> mathQuestionTypeChoice;

        if (cin.fail() || mathQuestionTypeChoice < 1 || mathQuestionTypeChoice > 5)
        {
            cout << "Error with Input Supplied...Ending Program Now.";
            return;
        }
        else
        {
            questionType = static_cast<QuestionType>(mathQuestionTypeChoice);
        }

        // Prompt and get number difficulty user wants
        cout << "\nPlease enter a positive integer to indicate the math difficulty you would like.\n1 - Single Digits\n2 - Double Digits\n3 - Tripple Digits\netc...\nYour Choice: ";
        cin >> difficultyNumber;

        if (cin.fail() || difficultyNumber < 1)
        {
            cout << "Error with Input Supplied...Ending Program Now.";
            return;
        }

        // Ask User Ten Questions
        this->askNextTenQuestions(questionType, difficultyNumber);

        cout << "\nReport: you got " << this->correctAnswers << " questions out of 10 correct on the first attempt." << endl;

        // Tell the user how he/she did
        if (this->getPercentageOfCorrectAnswers() < 0.75)
        {
            cout << "\n" << this->negativeClosingResponse << endl << endl;
        }
        else
        {
            cout << "\n" << this->positiveClosingResponse << endl << endl;
        }

        // Ask the user if they would like to play again
        cout << "Would you like to play again or let another student play (1 = yes, 0 = no): " << endl;
        cin >> playAgain;

        if (cin.fail())
        {
            cout << "Error with Input Supplied...Ending Program Now.";
            return;
        }

        this->restartGameStats();
    } while (playAgain == 1);
}

// Ask user 10 math questions
void MathPopQuiz::askNextTenQuestions(QuestionType questionType, int difficultyNumber)
{
    int numberOfQuestionsAsked = 1;

    // Loop until ten questions have been asked
    while (numberOfQuestionsAsked <= 10)
    {
        this->goToNextQuestion(questionType, difficultyNumber);
        numberOfQuestionsAsked++;
    }

}

// Moves on to the next math question with the user
void MathPopQuiz::goToNextQuestion(QuestionType questionType, int difficultyNumber)
{
    int firstNumber = this->getRandomNumber(difficultyNumber);
    int secondNumber = this->getRandomNumber(difficultyNumber);
    bool beyondFirstAttempt = false;
    bool correctAnswerAchievedOnFirstTry = false;
    bool correctAnswerEntered = false;
    int answer;

    // Decide which Math Question to prompt user about
    switch (questionType)
    {
    case Add:
        this->incrementTotalQuestionsCounter();
        answer = firstNumber + secondNumber;
        this->promptQuestionAndGetUserAnswer(firstNumber, secondNumber, "plus", answer);
        break;
    case Subtraction:
        this->incrementTotalQuestionsCounter();
        answer = firstNumber - secondNumber;
        this->promptQuestionAndGetUserAnswer(firstNumber, secondNumber, "minus", answer);
        break;
    case Multiplication:
        this->incrementTotalQuestionsCounter();
        answer = firstNumber * secondNumber;
        this->promptQuestionAndGetUserAnswer(firstNumber, secondNumber, "times", answer);
        break;
    case Division:
        this->incrementTotalQuestionsCounter();
        answer = firstNumber / secondNumber;
        this->promptQuestionAndGetUserAnswer(firstNumber, secondNumber, "divided by", answer, true);
        break;
    case Random:
        // Use Recursion to ask the random question
        int randomMathType = this->getRandomNumber(1, 4);
        QuestionType randomQuestionType = static_cast<QuestionType>(randomMathType);
        this->goToNextQuestion(randomQuestionType, difficultyNumber);
        break;
    }
}

// Prompts user with a questions and returns the correct answer they gave
void MathPopQuiz::promptQuestionAndGetUserAnswer(int firstNumber, int secondNumber, string mathOperand, double correctAnswer, bool isDivisionQuestion)
{
    bool beyondFirstAttempt = false;
    bool correctAnswerAchievedOnFirstTry = false;
    bool correctAnswerEntered = false;
    int userAnswer;

    // Keep prompting the user until a correct answer is given
    while (!correctAnswerEntered)
    {
        // Clear Buffers
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Ask the question
        cout << "\nHow much is " << firstNumber << " " << mathOperand << " " <<  secondNumber << "? " << (isDivisionQuestion ? "(Just supply integer part)" : " ") << ": ";
        cin >> userAnswer; // capture the user answer

        if (cin.fail())
        {
            cout << "\nUnable to process your input. Try again" << endl;
            beyondFirstAttempt = true;
            continue;
        }
        else if (userAnswer != correctAnswer)
        {
            cout << "\n" << this->getRandomResponse(Negative) << endl;
            beyondFirstAttempt = true; // User has finished thier first attemp at answering. Even when they answer correctly, this question will still count as a incorrectly answered towards thier score.
            continue;
        }
        else if (userAnswer == correctAnswer)
        {
            cout << "\n" << this->getRandomResponse(Positive) << endl;
            correctAnswerEntered = true;

            // If this is the user's first attempt and they got it correct, count this question as correctly answered towards thier score
            if (!beyondFirstAttempt)
            {
                this->incrementCorrectAnswerCounter();
            }
        }
    }
}

// Get a random Response based on the Performance Response Type
string MathPopQuiz::getRandomResponse(PerformanceResponseType performanceResponseType)
{
    // get a random number
    int randomNumber = this->getRandomNumber(0,3);

    // Decide which response to give them
    switch (performanceResponseType)
    {
    case Positive:
        return this->positiveResponses[randomNumber];
        break;
    case Negative:
        return this->negativeResponses[randomNumber];
        break;
    default:
        return this->positiveResponses[randomNumber];
        break;
    };
}

// Get a random number between of a certain number of digits
int MathPopQuiz::getRandomNumber(int numberOfDigits)
{
    // Calculate min number
    int minNumber = (numberOfDigits <= 1) ? 1 : pow(10, numberOfDigits - 1);

    // Calculate max number
    int maxNumber = pow(10, numberOfDigits) - 1;

    return this->getRandomNumber(minNumber, maxNumber);
}

// Gets a random number between two digits
int MathPopQuiz::getRandomNumber(int min, int max)
{
    // Update Seed Number
    this->seeder += 9999;

    // Seed the random number generator
    srand(time(0) + this->seeder);

    // Get the random number
    int randomNumber = (rand() % max) + min;

    // Make sure we cap the random number to the max number limit
    if (randomNumber > max)
    {
        randomNumber = max;
    }

    return randomNumber;
}

// Increment Correct Answer Counter
void MathPopQuiz::incrementCorrectAnswerCounter()
{
    this->correctAnswers++;
}

// Increment Total Question Counter
void MathPopQuiz::incrementTotalQuestionsCounter()
{
    this->totalQuestions++;
}

// Returns the percentage of correct answers
double MathPopQuiz::getPercentageOfCorrectAnswers()
{
    return static_cast<double>(this->correctAnswers) / static_cast<double>(this->totalQuestions);
}

// Resets the game's stats
void MathPopQuiz::restartGameStats()
{
    this->correctAnswers = 0;
    this->totalQuestions = 0;
}