/*
Name: Derrick Ward
Class/Section: CIS 554
HW # 4
Description: This file is the interface for the Math Pop Quiz Class
Date: 8/5/2019
*/

#include <iostream>

using std::string;

class MathPopQuiz {
public:
        MathPopQuiz();
        void start();
private:
    double seeder = 1;
    enum QuestionType { Add = 1, Subtraction = 2, Multiplication = 3, Division = 4, Random = 5 };
    enum PerformanceResponseType { Positive = 1, Negative = 2 };
    int correctAnswers, totalQuestions;
    const string positiveResponses[4] = {"Very good!", "Excellent!", "Nice work!", "Keep up the good work!"};
    const string negativeResponses[4] = { "No. Please try again.", "Wrong. Try once more.", "Don't give up!", "No. Keep Trying." };
    const string positiveClosingResponse = "Congratulations, you are ready to go to the next level!";
    const string negativeClosingResponse = "Please ask your teacher for extra help.";

    void askNextTenQuestions(QuestionType questionType, int difficultyNumber);
    void goToNextQuestion(QuestionType questionType, int difficultyNumber);
    void promptQuestionAndGetUserAnswer(int firstNumber, int secondNumber, string mathOperand, double correctAnswer, bool isDivisionQuestion = false);
    string getRandomResponse(PerformanceResponseType performanceResponseType);
    int getRandomNumber(int min, int max);
    int getRandomNumber(int numberOfDigits);
    void incrementCorrectAnswerCounter();
    void incrementTotalQuestionsCounter();
    double getPercentageOfCorrectAnswers();
    void restartGameStats();
};
