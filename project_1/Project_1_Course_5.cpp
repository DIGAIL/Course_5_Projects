#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;
enum EnGameChoice {stone = 1, paper = 2, scissor = 3 };
enum EnWinner { player = 1, computer = 2, draw = 3 };
struct StRoundInfo
{
	short RoundNumber = 0;
	EnGameChoice PlayerChoice;
	EnGameChoice ComputerChoice;
	EnWinner Winner;
	string WinnerName = "";
};
struct StGameResult
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawWonTimes = 0;
	EnWinner GameWinner;
	string WinnerName = "";
};
int ReadNumber(string message)
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
EnGameChoice ReadChoice()
{
	short ReadChoice = 1;
	do
	{
		cout << "\n your choice (stone)=1,(paper)=2,(scissor)=3 ?\n";
		cin >> ReadChoice;
	} while (ReadChoice < 1 || ReadChoice>3);
	return (EnGameChoice)ReadChoice;
}
EnGameChoice GetComputerChoice()
{
	return (EnGameChoice)RandomNumber(1, 3);
}
EnWinner WhoWonTheRound(StRoundInfo GameChoice)
{
	if (GameChoice.PlayerChoice == GameChoice.ComputerChoice)
	{
		return EnWinner::draw;
	}
	switch (GameChoice.PlayerChoice)
	{
	case EnGameChoice::stone:
		if (GameChoice.ComputerChoice == EnGameChoice::paper)
		{
			return EnWinner::computer;
		}
		break;
	case EnGameChoice::paper:
		if (GameChoice.ComputerChoice == EnGameChoice::scissor)
		{
			return EnWinner::computer;
		}
		break;
	case EnGameChoice::scissor:
		if (GameChoice.ComputerChoice == EnGameChoice::stone)
		{
			return EnWinner::computer;
		}
		break;
	}
	//when you reach here you can say player won or you won ;
	return EnWinner::player;
}
EnWinner WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
	if (ComputerWonTimes > PlayerWonTimes)
		return EnWinner::computer;
	else if (ComputerWonTimes < PlayerWonTimes)
		return EnWinner::player;
	else
		return EnWinner::draw;
}
string Tabs(short NumberOfTabs)
{
	string Tabs = " ";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		Tabs = Tabs + "\t";
		cout << Tabs;
	}
	return Tabs;
}
string ChoiceName(EnGameChoice Choice)
{
	string ArrayOfChoiceName[3] = { "stone","paper","scissor" };
	return ArrayOfChoiceName[Choice - 1];
}
string WinnerName(EnWinner Winner)
{
	string ArrayOfWinnerName[3] = { "Player","Computer","Draw" };
	return ArrayOfWinnerName[Winner - 1];
}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "----------------------------------------------\n";
	cout << Tabs(2) << "              +++Game Over+++                 \n";
	cout << Tabs(2) << "----------------------------------------------\n";
}
void setScreenColor(EnWinner Winner)
{

	switch (Winner)
	{
	case EnWinner::computer:
		system("color 4f");
		//system("\a");
		break;
	case EnWinner::player:
		system("color 2f ");
		break;
	default:
		system("color 6f");
		break;
	}
}
void PrintRoundReslt(StRoundInfo RoundInfo)
{
	cout << "------------round   [" << RoundInfo.RoundNumber << "]--------\n";
	cout << "  Player Choice     : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << " computer choice    : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << " Round Winner       [" << WinnerName(RoundInfo.Winner) << "] \n";
	setScreenColor(RoundInfo.Winner);
}
StGameResult FillGameResult(int Round, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
	StGameResult GameResult;
	GameResult.GameRounds = Round;
	GameResult.PlayerWinTimes = PlayerWonTimes;
	GameResult.ComputerWinTimes = ComputerWonTimes;
	GameResult.DrawWonTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(PlayerWonTimes, ComputerWonTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;

}
StGameResult PlayGame(short HowManyRound)
{
	StRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\n Round [ " << GameRound << "] Begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == EnWinner::player)
			PlayerWonTimes++;
		else if (RoundInfo.Winner == EnWinner::computer)
			ComputerWonTimes++;
		else
			DrawTimes++;

		PrintRoundReslt(RoundInfo);
	}
	return FillGameResult(HowManyRound, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}
void ShowTheFinalGameResult(StGameResult GameResult)
{
	cout << Tabs(2) << "----------------[Game Result]--------------------------\n\n";
	cout << Tabs(2) << " Game Round         : " << GameResult.GameRounds << endl;
	cout << Tabs(2) << " Player Won Times   : " << GameResult.PlayerWinTimes << endl;
	cout << Tabs(2) << " Computer Won Times : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << " Draw Won Times     : " << GameResult.DrawWonTimes << endl;
	cout << Tabs(2) << " Final Winner       : " << WinnerName(GameResult.GameWinner) << endl;
	cout << Tabs(2) << "---------------------------------------------------------\n\n";
	
}
short ReadRound()
{
	int Round = 1;
		do
		{
			Round = ReadNumber(" how many round you want 1 to 10 ? ");
		} while (Round < 1 || Round>10);
	return Round;
}
void ResetScreen()
{
	system("cls");
	system("color 0f");
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		StGameResult GameResult = PlayGame(ReadRound());
		ShowGameOverScreen();
		ShowTheFinalGameResult(GameResult);
		cout << " Do you want to play again ? (Y/N) ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}