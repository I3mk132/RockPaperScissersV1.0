
/// Project 1 :: Ammars Project Second Try ::
// Rock - Paper - Scissors

#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundNumber {
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults {
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

short Randint(short From, short To) {
	short Num = rand() % (To - From + 1) + From;
	return Num;
}

string Tabs(int Num) {
	string t = "";
	for (int i = 1; i <= Num; i++) {
		t += "\t";
	}
	return t;
}

enGameChoice GetComputerChoice() {
	return (enGameChoice)Randint(1, 3);
}

enGameChoice ReadPlayerChoice() {
	int Num;
	do {
		cout << "Your Choice : [1]:Rock, [2]:Paper, [3]:Scissors ? " << endl;
		cin >> Num;

	} while (Num < 1 || Num > 3);
	return (enGameChoice)Num;
}

string WinnerName(enWinner Winner) {
	string RoundWinnerArray[3] = { "Player1", "Computer", "No Winner" };
	return RoundWinnerArray[(int)Winner - 1];
}

string ChoiceName(enGameChoice ChoiceName) {
	string ChoiceNameArray[3] = { "Rock", "Paper", "Scissors" };
	return ChoiceNameArray[(int)ChoiceName - 1];
}

void PrintRoundResults(stRoundNumber RoundNumber) {
	cout << "_____________Round [" << RoundNumber.RoundNumber << "]_____________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundNumber.Player1Choice) << "\n";
	cout << "Computer Choice: " << ChoiceName(RoundNumber.ComputerChoice) << "\n";
	cout << "Round Winner   : [" << RoundNumber.WinnerName << "]\n";
	cout << "_______________________________________" << endl;
}

enWinner GetRoundWinner(stRoundNumber& RoundNumber) {

	if (RoundNumber.Player1Choice == RoundNumber.ComputerChoice) {
		return enWinner::Draw;
	}

	switch (RoundNumber.Player1Choice) {
	case enGameChoice::Paper: {

		if (RoundNumber.ComputerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;

	}
	case enGameChoice::Rock: {

		if (RoundNumber.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;

	}

	case enGameChoice::Scissors: {

		if (RoundNumber.ComputerChoice == enGameChoice::Rock) {
			return enWinner::Computer;
		}
		break;

	}

	default: {
		return enWinner::Player1;
	}

	}
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {
	if (Player1WinTimes == ComputerWinTimes) {
		return enWinner::Draw;
	}
	else if (Player1WinTimes < ComputerWinTimes) {
		return enWinner::Computer;
	}
	else {
		return enWinner::Player1;
	}
}

stGameResults FillGameResults(short AmountOfRounds, short PlayerWins, short ComputerWins, short Draws) {
	stGameResults GameResults;

	GameResults.GameRounds = AmountOfRounds;
	GameResults.Player1WinTimes = PlayerWins;
	GameResults.ComputerWinTimes = ComputerWins;
	GameResults.DrawTimes = Draws;
	GameResults.GameWinner = WhoWonTheGame(GameResults.Player1WinTimes, GameResults.ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResults PlayGame(short AmountOfRounds) {
	stRoundNumber RoundNumber;
	short PlayerWins = 0, ComputerWins = 0, Draws = 0;

	for (short i = 1; i <= AmountOfRounds; i++) {
		cout << "Round [" << i << "] begins: \n" << endl;
		RoundNumber.RoundNumber = i;
		RoundNumber.Player1Choice = ReadPlayerChoice();
		RoundNumber.ComputerChoice = GetComputerChoice();
		RoundNumber.Winner = GetRoundWinner(RoundNumber);
		RoundNumber.WinnerName = WinnerName(RoundNumber.Winner);

		// Counters
		if (RoundNumber.Winner == enWinner::Player1) {
			PlayerWins++;
			system("Color 2F");
		}
		else if (RoundNumber.Winner == enWinner::Computer) {
			ComputerWins++;
			system("Color 4F");
		}
		else {
			Draws++;
			system("Color 3F");
		}

		PrintRoundResults(RoundNumber);
	}

	return FillGameResults(AmountOfRounds, PlayerWins, ComputerWins, Draws);
}

short ReadAmountOffRounds() {
	short Num;
	do {
		cout << "How many Rounds 1 to 10 ? " << endl;
		cin >> Num;
	} while (Num < 1 || Num > 10);
	return Num;
}

void ResetScreen() {
	system("cls");
	system("Color 0F");
}

void PrintGameOver() {
	cout << Tabs(2) << "_____________________________________________________\n\n";
	cout << Tabs(4) << "+++ G A M E  O V E R +++\n";
	cout << Tabs(2) << "_____________________________________________________\n\n";
}

void PrintGameResults(stGameResults GameResults) {
	cout << Tabs(2) << "__________________ [ Game Results ] ___________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << "\n";
	cout << Tabs(2) << "Player1 won Times  : " << GameResults.Player1WinTimes << "\n";
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << "\n";
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << "\n";
	cout << Tabs(2) << "Final Winner       : " << WinnerName(GameResults.GameWinner) << "\n";
	cout << Tabs(2) << "________________________________________________________\n" << endl;
}

void StartGame() {
	char PlayAgain = 'Y';

	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadAmountOffRounds());
		PrintGameOver();
		PrintGameResults(GameResults);

		cout << "Do you wnat to play again? Y/N ? " << endl;
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
	cout << "Bye!" << endl;
}

int main() {
	srand((unsigned)time(NULL));

	StartGame();

}
