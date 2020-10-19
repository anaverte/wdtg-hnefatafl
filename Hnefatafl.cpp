
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

//metoda 1
struct state {
	char board1[11][11];
	int mark = 1;
};

void copyArray(char board1[11][11], char board2[11][11]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			board1[i][j] =board2[i][j];
		}
	}
}

void movePawn(char board[11][11], int x1,int y1, int x2, int y2) {
	board[x2][y2] = board[x1][y1];
	if (x1 == 5 && y1 == 5) 
	{ board[x1][y1] = 'x'; }
	else{
	board[x1][y1] = ' ';}
}

bool capturePawn(char board[11][11], int x, int y) {
	bool white=false;
	if (board[x][y] == '*' || board[x][y] == '#')white = 1;
	if (white) {
		if (x > 1 && board[x-1][y]=='o' && (board[x - 2][y] == 'x' || board[x - 2][y] == '*' || board[x - 2][y] == '#')) {
			board[x - 1][y] = ' ';
			return 1;
		}
		if (x < 9 && board[x + 1][y] == 'o' && (board[x + 2][y] == 'x' || board[x + 2][y] == '*' || board[x + 2][y] == '#')) {
			board[x + 1][y] = ' ';
			return 1;
		}
		if (y > 1 && board[x ][y- 1] == 'o' && (board[x ][y- 2] == 'x' || board[x ][y- 2] == '*' || board[x ][y- 2] == '#')) {
			board[x ][y- 1] = ' ';
			return 1;
		}
		if (y < 9 && board[x ][y+ 1] == 'o' && (board[x ][y+ 2] == 'x' || board[x ][y+ 2] == '*' || board[x ][y+ 2] == '#')) {
			board[x ][y+ 1] = ' ';
			return 1;
		}
		return false;
	}
	else
	{
		if (x > 1 && board[x - 1][y] == '*' && (board[x - 2][y] == 'x'  || board[x - 2][y] == 'o')) {
			board[x - 1][y] = ' ';
			return 1;
		}
		if (x < 9 && board[x + 1][y] == '*' && (board[x + 2][y] == 'x' || board[x + 2][y] == 'o' )) {
			board[x + 1][y] = ' ';
			return 1;
		}
		if (y > 1 && board[x][y - 1] == '*' && (board[x][y - 2] == 'x' || board[x][y - 2] == 'o')) {
			board[x][y - 1] = ' ';
			return 1;
		}
		if (y < 9 && board[x][y + 1] == '*' && (board[x][y + 2] == 'x' || board[x][y + 2] == 'o' )) {
			board[x][y + 1] = ' ';
			return 1;
		}
		return false;
	}
	

}

bool captureKing(char board[11][11]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (board[i][j] == '#') 
			{
				if ((i == 5 && (j == 4 || j == 6)) || ((i == 4 || i == 5 || i == 6) && j == 5)) {
					if ((board[i - 1][j] == 'o' || board[i - 1][j] == 'x') && (board[i + 1][j] == 'o' || board[i + 1][j] == 'x') && (board[i][j - 1] == 'o' ||
						board[i][j - 1] == 'x') && (board[i][j + 1] == 'o' || board[i][j + 1] == 'x')) {
						board[i][j] = ' ';
						return 1;
					}
				}
				else if (((i>0 && i<10) && (board[i - 1][j] == 'o' || board[i - 1][j] == 'x') && (board[i + 1][j] == 'o' || board[i + 1][j] == 'x')) || 
				 (j>0 && j<10) && ((board[i][j - 1] == 'o' || board[i][j - 1] == 'x') && (board[i][j + 1] == 'o' || board[i][j + 1] == 'x'))) {
					board[i][j] = ' ';
					return 1;
				}
			}
		}
	}
	return 0;	
}

//metoda 2

void randomBoard(char board[11][11],char signs[4]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			board[i][j] = signs[rand() % 4];
		}
	}
	board[0][0] = signs[rand() % 2];
	board[0][10] = signs[rand() % 2];
	board[10][10] = signs[rand() % 2];
	board[10][0] = signs[rand() % 2];
	board[5][5] = signs[rand() % 2];
}

void drawBoard(char board[11][11]) {
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

bool isGood(char board[11][11]) {
	int king = 0, black = 0, white = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (board[i][j] == '#') {
				king++;
				if (king > 1) return 0;
			}
			else if (board[i][j] == '*') {
				white++;
				if (white > 12) return 0;
			}
			else if(board[i][j] == 'o') {
				black++;
				if (black > 24) return 0;
			}
		}	
	}
	if (king < 1) return 0;

	return 1;
}

int main()
{
	char board[11][11];
	char signs[4] = { ' ','#','o','*' };

	srand(time(NULL));

	
   //metoda 2
	cout << "METODA 2" << endl<<endl;
	unsigned long long int combinations = pow(4,116);
	unsigned long long int combinations2 = pow(2, 5);
	cout << "Mozliwe kombinacje: "<< combinations <<" * "<< combinations2 << endl;
	cout << "Mozliwe kombinacje: "<< (double)combinations * (double)combinations2 << endl;

	int average = 0;
	int sum = 0;
	for (int j = 0; j < 15; j++)
	{
		int goodBoards = 0;
		for (int i = 0; i < 1000; i++)
		{
			randomBoard(board, signs);
			if (isGood(board)) goodBoards++;
		}
		cout << "Dobre plansze podczas " << j + 1 << " proby: " << goodBoards << endl;
		sum = sum + (goodBoards / 1000) * combinations * combinations2;
	} 
	average = sum / 15;
	cout << "Wynik: "<< average;

	//metoda 1
	bool blackWins = 0;
	bool whiteWins = 0;
	//bool withdraw = 0;

	state beginningBoard;
	
	//tworzenie pustej planszy
for (int i = 0; i < 11; i++)
{
	for (int j = 0; j < 11; j++)
	{
		beginningBoard.board1[i][j] = ' ';
	}
}

//plansza początkowa na bazie pustej
//pola specjalne
beginningBoard.board1[0][0] = beginningBoard.board1[10][10] = beginningBoard.board1[0][10] = beginningBoard.board1[10][0] = 'x';
//czarne pionki
beginningBoard.board1[0][3] = beginningBoard.board1[0][4] = beginningBoard.board1[0][5] = beginningBoard.board1[0][6] =
beginningBoard.board1[0][7] = beginningBoard.board1[3][0] = beginningBoard.board1[3][10] = beginningBoard.board1[4][0] =
beginningBoard.board1[4][10] = beginningBoard.board1[5][0] = beginningBoard.board1[5][1] = beginningBoard.board1[5][9] =
beginningBoard.board1[5][10] = beginningBoard.board1[6][0] = beginningBoard.board1[6][10] = beginningBoard.board1[7][0] =
beginningBoard.board1[7][10] = beginningBoard.board1[10][3] = beginningBoard.board1[10][4] = beginningBoard.board1[10][5] =
beginningBoard.board1[9][5] = beginningBoard.board1[10][6] = beginningBoard.board1[10][7] = beginningBoard.board1[1][5] = 'o';
//białe pionki
beginningBoard.board1[3][5] = beginningBoard.board1[4][4] = beginningBoard.board1[4][5] = beginningBoard.board1[4][6] =
beginningBoard.board1[5][3] = beginningBoard.board1[5][4] = beginningBoard.board1[5][6] = beginningBoard.board1[5][7] =
beginningBoard.board1[6][4] = beginningBoard.board1[6][5] = beginningBoard.board1[6][6] = beginningBoard.board1[7][5] = '*';
//król
beginningBoard.board1[5][5] = '#';

const int MAX_NUMBER_OF_TRIES = 200;
const int MAX_NUMBER_OF_TURNS = 999;
state possibleMoves[480];
double averageb=0;
double averaged=0;
double bs[MAX_NUMBER_OF_TRIES];
double ds[MAX_NUMBER_OF_TRIES];
int numberOfTries=0;
int k = 1,availableMoves=0,index=0;
bool whiteMoves = 0;
int turn = 0;

while (numberOfTries < MAX_NUMBER_OF_TRIES) {
	while (!whiteWins && (!blackWins) && turn <= MAX_NUMBER_OF_TURNS) {
		if (whiteMoves) {
			index = 0;
			for (int i = 0; i < 11; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					if (beginningBoard.board1[i][j] == '#' || beginningBoard.board1[i][j] == '*') {
						//w lewo
						while (true) {
							if (i > 0 && (i - k) >= 0 && (beginningBoard.board1[i - k][j] == ' ') || (beginningBoard.board1[i][j] == '#' && beginningBoard.board1[i - k][j] == 'x')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i - k, j);
								if (possibleMoves[index].board1[0][0] == '#' || possibleMoves[index].board1[10][10] == '#' || possibleMoves[index].board1[0][10] == '#' || possibleMoves[index].board1[10][0] == '#') {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i - k, j)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }							
								//potrzeba jeszcze oceny
								index++;
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w górę
						while (true) {
							if (j > 0 && (j - k) >= 0 && (beginningBoard.board1[i][j - k] == ' ') || (beginningBoard.board1[i][j] == '#' && beginningBoard.board1[i][j - k] == 'x')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i, j - k);
								if (possibleMoves[index].board1[0][0] == '#' || possibleMoves[index].board1[10][10] == '#' || possibleMoves[index].board1[0][10] == '#' || possibleMoves[index].board1[10][0] == '#') {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i, j - k)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w prawo
						while (true) {
							if (i < 10 && (i + k) <= 10 && ((beginningBoard.board1[i + k][j] == ' ') || (beginningBoard.board1[i][j] == '#' && beginningBoard.board1[i + k][j] == 'x'))) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i + k, j);
								if (possibleMoves[index].board1[0][0] == '#' || possibleMoves[index].board1[10][10] == '#' || possibleMoves[index].board1[0][10] == '#' || possibleMoves[index].board1[10][0] == '#') {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i + k, j)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w dół
						while (true) {
							if (j < 10 && (j + k) <= 10 && ((beginningBoard.board1[i][j + k] == ' ') || (beginningBoard.board1[i][j] == '#' && beginningBoard.board1[i][j + k] == 'x'))) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i, j + k);
								if (possibleMoves[index].board1[0][0] == '#' || possibleMoves[index].board1[10][10] == '#' || possibleMoves[index].board1[0][10] == '#' || possibleMoves[index].board1[10][0] == '#') {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i, j + k)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
					}
				}
			}
			//sprawdzenie, który ruch najbardziej opłaca się wykonać, w przypadku powtarzającej się wartości losowo
			int options[450];
			int h = 0;
			options[h] = 0;
			int maxMark = 1;
			for (int b = 0; b < index; b++)
			{
				if (possibleMoves[b].mark > maxMark) {
					options[0] = b;
					maxMark = possibleMoves[b].mark;
					h = 1;
				}
				if (possibleMoves[b].mark == maxMark) {
					options[h] = b;
					h++;
				}
			}

			//jako beginningBoard board1 skopiować aktualną planszę
			int randomNumber = rand() % (h + 1);
			copyArray(beginningBoard.board1, possibleMoves[options[randomNumber]].board1);
			//sprawdzenie, czy biały wygrał
			if (maxMark == 4)whiteWins = 1;
			//zwiększenie liczby tur
			turn++;
			whiteMoves = 0;
		}
		else {
			index = 0;
			for (int i = 0; i < 11; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					if (beginningBoard.board1[i][j] == 'o') {
						//w lewo
						while (true) {
							if (i > 0 && (i - k) >= 0 && (beginningBoard.board1[i - k][j] == ' ')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i - k, j);
								if (captureKing(possibleMoves[index].board1)) {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i - k, j)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w górę
						while (true) {
							if (j > 0 && (j - k) >= 0 && (beginningBoard.board1[i][j - k] == ' ')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i, j - k);
								if (captureKing(possibleMoves[index].board1)) {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i, j - k)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w prawo
						while (true) {
							if (i < 10 && (i + k) <= 10 && (beginningBoard.board1[i + k][j] == ' ')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i + k, j);
								if (captureKing(possibleMoves[index].board1)) {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i + k, j)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
						//w dół
						while (true) {
							if (j < 10 && (j + k) <= 10 && (beginningBoard.board1[i][j + k] == ' ')) {
								copyArray(possibleMoves[index].board1, beginningBoard.board1);
								movePawn(possibleMoves[index].board1, i, j, i, j + k);
								if (captureKing(possibleMoves[index].board1)) {
									possibleMoves[index].mark = 4;
								}
								if (capturePawn(possibleMoves[index].board1, i, j + k)) {
									possibleMoves[index].mark = 3;
								}
								else { possibleMoves[index].mark = 2; }
								index++;
								//potrzeba jeszcze oceny
								availableMoves++;
								k++;
							}
							else {
								k = 1;
								break;
							}
						}
					}
				}

			}
			//sprawdzenie, który ruch najbardziej opłaca się wykonać, w przypadku powtarzającej się wartości losowo
			int options[450];
			int h = 0;
			options[h] = 0;
			int maxMark = 1;
			for (int b = 0; b < index; b++)
			{
				if (possibleMoves[b].mark > maxMark) {
					options[0] = b;
					maxMark = possibleMoves[b].mark;
					h = 1;
				}
				if (possibleMoves[b].mark == maxMark) {
					options[h] = b;
					h++;
				}
			}
			//jako beginningBoard board1 skopiować aktualną planszę
			int randomNumber = rand() % (h+1);
			copyArray(beginningBoard.board1, possibleMoves[options[randomNumber]].board1);
			//sprawdzenie, czy czarny wygrał
			if (maxMark == 4)blackWins = 1;
			//zwiększenie liczby tur
			turn++;
			whiteMoves = 1;
		}
		
	}
	bs[numberOfTries] = availableMoves / turn;
	ds[numberOfTries] = turn;
	numberOfTries++;
	turn = 0;
	blackWins = 0;
	whiteWins = 0;
	availableMoves = 0;
}
//obliczenie i wyświetlenie wyniku
int bsSum = 0;
for (int i = 0; i < MAX_NUMBER_OF_TRIES; i++)
{
	bsSum += bs[i];
}
averageb = bsSum / MAX_NUMBER_OF_TRIES;
double dsSum = 0;
for (int i = 0; i < MAX_NUMBER_OF_TRIES; i++)
{
	dsSum += ds[i];
}
averaged = dsSum / MAX_NUMBER_OF_TRIES;
cout << endl<<endl<<"METODA 1" << endl<<endl;
cout << "b: " << averageb << endl;
cout << "d: " << averaged << endl;
cout << "Wynik: " << averageb << '^' << averaged << ", co ze wzgledu na wielkosc daje " << pow(averageb, averaged);

   return 0;
}