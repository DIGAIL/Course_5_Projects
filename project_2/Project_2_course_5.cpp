#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
enum EnOperationType { Add = 1, sub = 2, mult = 3, Divs = 4, mix = 5 };
enum EnQuestionLevel { Essay = 1, Med = 2, Hard = 3, Mix = 4 };
struct StQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	EnQuestionLevel QuestionsLevel = EnQuestionLevel::Essay;
	EnOperationType OperationType = EnOperationType::Add;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false;

};
struct StQuiz
{
	StQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	EnQuestionLevel QuestionLevel = EnQuestionLevel::Essay;
	EnOperationType OperationType = EnOperationType::Add;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IsPass = false;

};
short ReadNumber(string message)
{
	int Number;
	cout << message << endl;
	cin >> Number;
	return Number;
}
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
string LevelName(EnQuestionLevel QuestionName)
{
	string ArrayOfQuestionLevel[4] = { "Essay","Med","Hard","Mix" };
	return ArrayOfQuestionLevel[QuestionName-1];
}
void SetScreen(bool Right)
{
	if (Right == true)
	{
		system("color 2f");
		system("\a");
	}
	else
	{
		system("color 4f");
	}
}
EnQuestionLevel ReadLevel()
{
	short QuestionLevel=0;
	cout << " Which level do you to play : 1[essay] , 2[med] , 3[hard] , 4[mix] " ;
	cin >> QuestionLevel;
	return (EnQuestionLevel)QuestionLevel;
}
EnOperationType ReadOperationType()
{
	short OpType=0;
	cout << " please enter operation type : 1[+] , 2[*] , 3[-] , 4[/] , 5 [mix]; ";
	cin >> OpType;
	return (EnOperationType)OpType;
}
string OperationTypeToText(EnOperationType OperationType)
{
	switch (OperationType)
	{
	case EnOperationType::Add:
		return "+";
		break;
	case  EnOperationType::sub:
		return "-";
		break;
	case  EnOperationType::mult:
		return "*";
		break;
	case  EnOperationType::Divs:
		return "/";
		break;
	case EnOperationType::mix:
		return "mix";
	default:
		return "unknown";
	}
}
int SimpeCalculator(short Number1,short Number2,EnOperationType OperationType)
{
	switch (OperationType)
	{
	case EnOperationType::Add:
		return Number1 + Number2;
	case EnOperationType::sub:
		return Number1 - Number2;
	case EnOperationType::mult:
		return Number1 * Number2;
	case EnOperationType::Divs:
		if (Number2 != 0)
		{
			return Number1 / Number2;
		}
	default:
		return Number1 + Number2;
	}
}
EnOperationType GetRandomOperationType()
{
	short OperationType = RandomNumber(1, 4);
	return (EnOperationType)OperationType;
}
StQuestion GenerateQuestion(EnQuestionLevel QuestionLevel,EnOperationType OperationType)
{
	StQuestion Question;
	if (QuestionLevel == EnOperationType::mix)
	{
		QuestionLevel = (EnQuestionLevel)RandomNumber(1, 3);
	}
	if (OperationType == EnOperationType::mix)
	{
		OperationType = GetRandomOperationType();
	}
	Question.OperationType = OperationType;
	switch (QuestionLevel)
	{
	case EnQuestionLevel::Essay:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpeCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	case EnQuestionLevel::Med:
		Question.Number1 = RandomNumber(20, 50);
		Question.Number2 = RandomNumber(20, 50);
		Question.CorrectAnswer = SimpeCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	case EnQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpeCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	case EnQuestionLevel::Mix:

		Question.Number1 = RandomNumber(1, 100);
		Question.Number2 = RandomNumber(1, 100);
		Question.CorrectAnswer = SimpeCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	}
	return Question;
}
void GenerateQuizQuestions(StQuiz& Quiz)
{
	for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
	{
		Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OperationType);
	}
}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
int ReadOperation()
{
	int Op = 0;
	cin >> Op;
	return Op;
}
void PrintTheQuestion(StQuiz &Quiz,short NumberOfQuestion)
{
	cout << "\n";
	cout << " Question ( " << NumberOfQuestion + 1 << "/" << Quiz.NumberOfQuestions << ")\n";
	cout << Quiz.QuestionList[NumberOfQuestion].Number1 ;
	cout << OperationTypeToText(Quiz.QuestionList[NumberOfQuestion].OperationType) ;
	cout << Quiz.QuestionList[NumberOfQuestion].Number2 ;
}
void CorrectAnswer(StQuiz& Quiz, short QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quiz.QuestionList[QuestionNumber].AnswerResult = false;
		Quiz.NumberOfWrongAnswer++;
		cout << " wrong answer	\n";
		cout << " the right answer : ";
		cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << " \n ";
	}
	else
		{
		Quiz.QuestionList[QuestionNumber].AnswerResult = true;
		Quiz.NumberOfRightAnswer++;
		cout << " right answer\n";
	}
	SetScreen(Quiz.QuestionList[QuestionNumber].AnswerResult);
	
}
void AskAndCorrenctAnswer(StQuiz& Quiz)
{
	for (short QuestionNumber = 0;QuestionNumber < Quiz.NumberOfQuestions;QuestionNumber++)
	{
		PrintTheQuestion(Quiz, QuestionNumber);
		cout << " = ";
		Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectAnswer(Quiz, QuestionNumber);

	}
	Quiz.IsPass = (Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);
}
string FindTheFinalResult(bool Passed)
{
	if (Passed)
		return "Pass ;-)";
	else
		return "Fail ;-(";
}
void PrintTheQuestionResult(StQuiz& Quiz)
{
	cout << "\n";
	cout << " final result " << FindTheFinalResult(Quiz.IsPass) << endl;
	cout << "----------------------------------------------------\n";
	cout << " number of Question      : " << Quiz.NumberOfQuestions << endl;
	cout << " Question Level          : " << LevelName(Quiz.QuestionLevel) << endl;
	cout << " Operation Type          : " << OperationTypeToText(Quiz.OperationType) << endl;
	cout << " number of right answer  : " << Quiz.NumberOfRightAnswer << endl;
	cout << " number of wrong answer  : " << Quiz.NumberOfWrongAnswer << endl;
	cout << "----------------------------------------------------\n";
}
short ReadQuestionNumber()
{
	short Number = 0;
	do
	{
		cout << " how many question do you want to answer? ";
		cin >> Number;
	} while (Number < 1 || Number>10);
	return Number;
}
void PlayMathGame()
{
	StQuiz Quiz;
	Quiz.NumberOfQuestions = ReadQuestionNumber();
	Quiz.QuestionLevel = ReadLevel();
	Quiz.OperationType = ReadOperationType();

	GenerateQuizQuestions(Quiz);
	AskAndCorrenctAnswer(Quiz);
	PrintTheQuestionResult(Quiz);
}
void ResetScreen()
{
	system("cls");
	system(" color 0f");
}
void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << " do you want to play again\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}