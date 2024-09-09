/*
Name: Rianna Pais
Date: 03/29/2024

This is a program in C++ that features a Tic-Tac-Toe game for users to play against the computer. It randomizes who gets the first turn, and each 
of the computer's move against the user. It also allows the user to create their own player name, and will track their win/loss record against the 
computer. The program utilizes two classes (Game and Player), their objects, and functions within each of the classes to properly compute, print, 
and play the game of Tic-Tac-Toe. A do-while loop is used to allow users to continue or quit playing when they want.
*/
	// included header, namespaces, and array
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
char board[3][3];

	// game class which includes a private symbol for the game, a static game count, and multiple public game functions
class Game{
	char symbol;

	public:	
		static int games;
	// constructor the a new object in the game class
		Game(){	
			games=0;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					board[i][j] = '_';
				}
			}
		}
	// functions for getting/setting/incrementing variables, manipulating the tic-tac-toe board, 
	// playing a automated computer move, and checking for the end of the game
		char getSymbol(){
			return symbol;
		}
		void randomizeTurn(){
			symbol = (rand() % 2 == 0) ? 'O' : 'X';
		}
		void resetBoard(){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					board[i][j] = '_';
				}
			}
		}
		void drawBoard(){
			cout << endl;
			cout << "   0  1  2 " << endl;
			for(int i = 0; i < 3; i++){
				cout << i << "  ";
				for(int j = 0; j < 3; j++){
					cout << board[i][j] << "  ";
				}
				cout << endl;
			}
			cout << endl;
		}
		void autoMove(){
			int rowRand, colRand;
			do {
				rowRand = rand() % 3;
				colRand = rand() % 3;
			} while (board[rowRand][colRand] != '_');
			board[rowRand][colRand] = symbol;
			cout << "Computer's Move:";
		}
		int checkEnd(){
			for (int i = 0; i < 3; i++){ //row check
        		if (board[i][0] != '_' && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            		if (board[i][0] == symbol)
        				return 0;
        			else 
        				return 1;
				}
			}
			for (int j = 0; j < 3; j++){ //column check
        		if (board[0][j] != '_' && board[0][j] == board[1][j] && board[1][j] == board[2][j]){
            		if (board[0][j] == symbol)
        				return 0;
        			else 
        				return 1;
				}
			} // diagonal checks
			 if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        		if (board[0][0] == symbol)
        			return 0;
        		else 
        			return 1;
    		}
    		if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        		if (board[0][2] == symbol)
        			return 0;
        		else 
        			return 1;
    		} //  draw/continuing game checks
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if (board[i][j] == '_')
						return 2;
				}
			}
			return 3;
		}
};
int Game::games=0;

	// the player class which includes private names and symbols for each player, and multiple public player functions
class Player{
	string name;
	string newName;
	char xo;
	int wins;
	public:
	// constructor to initialize new objects in the player class, along with providing a default player name
		Player(string defaultName = "Player"){
			wins=0;
			name = defaultName;
			xo = 'X';
		}
	// functions for getting/setting/increamenting variables, and prompting a user to make a move and checking the validty of thier input
		string getName(){
			return name;
		}
		void setName(string newName){
			name = newName;
		}
		int getWins(){
			return wins;
		}
		void Won(){
			wins++;
		}
		void setXO(){
			xo = 'O';
		}
		void setOX(){
			xo = 'X';
		}
		void playerMove(){
			int row, col;
			while (true){
				cout << "Your turn to pick a spot! Enter row number: ";
				cin >> row;
				if (row < 3 && row >= 0){
					cout << "Enter column number: ";
					cin >> col;
					if (col < 3 && col >= 0){
						if (board[row][col] == '_'){
							board[row][col] = xo;
							break;
						} else {
							cout << "This is not an open spot!" << endl;}			
					} else {
						cout << "Not a valid column number." << endl;}
				} else {
					cout << "Not a valid row number." << endl;}
			}
		}                                                
};

	// main body
int main (){
	// randomized time seed and new objects created for game and players
	srand(time(0));
	Game newGame;
	Player computer("Computer");
	Player newPlayer;
	// intake input for the user to have a player name
	string yesno;
	cout << "Would you like to enter your player name (Yes/No): ";
	cin >> yesno;
	yesno[0] = toupper(yesno[0]);
	string name;
	if (yesno == "Yes"){
		cout << "Enter player name: ";
		cin >> name;
		name[0] = toupper(name[0]);
		newPlayer.setName(name);
	} else {
		cout << "Using default name." << endl;
	} 
	string again;
	
	// a do-while loop that allows the user to repeatedly play tic-tac-toe with the computer
	do {
	// randomization of who gets the first turn and the first few moves
		newGame.drawBoard();
		newGame.randomizeTurn();
		if (newGame.getSymbol() == 'X'){
			newPlayer.setXO();
			newGame.autoMove();
			newGame.drawBoard();
		} else {
			newPlayer.setOX();
		}
		newPlayer.playerMove();
		cout << endl << newPlayer.getName() << "'s Move:";;
		newGame.drawBoard();
		newGame.autoMove();
		newGame.drawBoard();
		newPlayer.playerMove();
		cout << endl << newPlayer.getName() << "'s Move:";;
		newGame.drawBoard();
	// while loop that alternates moves between each player, check for a win, loss, or draw between them, and updates the board after each turn
		while (true){
			newGame.autoMove();
			newGame.drawBoard();
			if (newGame.checkEnd() == 0){
				cout << "Sorry... you lost :(";
				Game::games++;
				computer.Won();
				break;
			} else if (newGame.checkEnd() == 1){
				cout << "Congrats, you won!";
				Game::games++;
				newPlayer.Won();
				break;
			} else if (newGame.checkEnd() == 3){
				cout << "Draw.";
				Game::games++;
				break;
			} 
			newPlayer.playerMove();
			cout << endl << newPlayer.getName() << "'s Move:";;
			newGame.drawBoard();
			if (newGame.checkEnd() == 0){
				cout << "Sorry... you lost :(";
				Game::games++;
				computer.Won();
				break;
			} else if (newGame.checkEnd() == 1){
				cout << "Congrats, you won!";
				Game::games++;
				newPlayer.Won();
				break;
			} else if (newGame.checkEnd() == 3){
				cout << "Draw.";
				Game::games++;
				break;
			} 
		}
	// resetting the board and printing the results/win records after a game ends, and 
	// prompting a repeat or exit for if the user wants to play again or not
		newGame.resetBoard();
		cout << " Game Over!" << endl;
		cout << newPlayer.getName() << "'s Wins: " << newPlayer.getWins() << "/" << Game::games; 
		cout << "\tComputer's' Wins: " << computer.getWins() << "/" << Game::games << endl << endl;
		cout << "Would you like to play again? (Yes/No): ";
		cin >> again;
		again[0] = toupper(again[0]);
		while (again != "Yes" && again != "No"){
            cout << "Please enter Yes or No: ";
            cin >> again;
            again[0] = toupper(again[0]);
    	}
	} while (again != "No");
	cout << "Bye!" << endl;
	return 0;
}
