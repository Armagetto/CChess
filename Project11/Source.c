#include "Header.h"


void main() {
	board b;
	int gameSwitch = 1; //game on
	BuildChessBoard(&b);
	
	//printf("Headline!\nsubtext subtext\n\n");

	printBoard(&b);
	
	b.playerTurn = white;

	//game loop
	while (gameSwitch) {
		if (movePiece(&b) == NULL) {
			gameSwitch = 0;
			error();
			break;
		}
		system("cls");
		printBoard(&b);
	}
	

}