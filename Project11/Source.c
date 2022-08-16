#include "Header.h"


void main() {
	board b;
	BuildChessBoard(&b);
	
	//printf("Headline!\nsubtext subtext\n\n");

	printBoard(&b);
	
	b.playerTurn = white;

	//move piece
	movePiece(&b);
	system("cls");
	printBoard(&b);
	//make sure it sorkd (was leagal etc)
	//clear screen
	//print new board

}