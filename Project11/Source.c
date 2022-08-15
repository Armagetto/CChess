#include "Header.h"


void main() {
	board b;
	BuildChessBoard(&b);
	
	//printf("%d,", b.piecesArray[A][7].piceType);

	printBoard(&b);
	
}