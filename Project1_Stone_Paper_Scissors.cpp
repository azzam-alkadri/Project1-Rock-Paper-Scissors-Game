#include <iostream>  
#include <string>    
#include <cstdlib>   
#include <ctime>     

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;          
    enGameChoice Player1Choice;     
    enGameChoice ComputerChoice;    
    enWinner Winner;                
    string WinnerName;              
};

struct stGameResults
{
    short GameRounds = 0;       
    short Player1WinTimes = 0;  
    short ComputerWinTimes = 0; 
    short DrawTimes = 0;        
    enWinner GameWinner;        
    string WinnerName = "";     
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRound() {

    short Rounds = 0;
    do {
        cout << "How Many Rounds Do You Want to Play ?";
        cin >> Rounds;
    } while (Rounds < 0);

    return Rounds;
}

void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner) {

    case enWinner::Computer:
        system("Color 4F");
        system("\a");
        break;

    case enWinner::Player1:
        system("Color 2F");
        break;
    case enWinner::Draw:
        system("Color 6F");
        break;
    }
}


enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}


string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}


enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
   
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}



enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {

    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults( HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes );
}





void ResetScreen() {

    system("cls");
    system("Color 0F");
}

string Tabs(short NumberOfTabs) {

    string T = "";

    for (int i = 1; i <= NumberOfTabs; i++) {

        T = T + "\t";
        cout << T;
    }

    return T;
}

void ShowGameOverScreen() {

    cout << Tabs(2) << "_______________________________________________________\n\n";
    cout << Tabs(2) << "                       ++++ G a m e O v e r ++++\n\n";
    cout << Tabs(2) << "_______________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "________________________[Game Results]________________________\n\n";
    cout << Tabs(2) << "Game Results            :" << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times        :" << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won Times      :" << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times              :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "FinalWinner             :" << GameResults.WinnerName << endl;
    cout << Tabs(2) << "______________________________________________________________\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}


void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();

        stGameResults GameResults = PlayGame(ReadHowManyRound());

        ShowGameOverScreen();

        ShowFinalGameResults(GameResults);

        cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {

    srand((unsigned)time(NULL));  

    StartGame();

    return 0;
    
}