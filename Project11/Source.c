#include "Header.h"


void main() {
	board b;
	int gameSwitch = 1; //game on
	BuildChessBoard(&b);
	printBoard(&b);
	b.playerTurn = white;
	//main game loop
	while (gameSwitch)
	{
		if (movePiece(&b) == NULL)
		{
			gameSwitch = 0;
			error("001");
			break;
		}
		system("cls");
		printBoard(&b);
	}
}