#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8 //8X8 is for chess
#include <stdio.h>
#include <malloc.h>
#include <string.h>


/*define ENUM type */
enum PieceType { empty, pawn = 1, bishop, knight, rook=5, queen = 9, king};
enum playerType { black, white, nor};
enum boardCoordinates { A , B, C, D, E, F, G, H};

/*structs*/
typedef struct
{
	int piceType; //king etc.
	int playerType; //black or white
	//char location[BOARD_SIZE][BOARD_SIZE];
}piece;

typedef struct
{
	piece piecesArray[BOARD_SIZE][BOARD_SIZE];
}board;


/*functions*/
int BuildChessBoard(board* b)
{
	//ini all pieces to empty
	for (int counter1 = 0; counter1 < BOARD_SIZE; counter1++) {
		for (int counter2 = 0; counter2 < BOARD_SIZE; counter2++) {
			b->piecesArray[counter1][counter2].piceType = empty;
			b->piecesArray[counter1][counter2].playerType = nor;
		}
	}

	//black
	b->piecesArray[A][7].piceType = rook;
	b->piecesArray[H][7].piceType = rook;

	b->piecesArray[B][7].piceType = knight;
	b->piecesArray[G][7].piceType = knight;

	b->piecesArray[C][7].piceType = bishop;
	b->piecesArray[F][7].piceType = bishop;

	b->piecesArray[D][7].piceType = queen;
	b->piecesArray[E][7].piceType = king;

	for (int i = 0; i < BOARD_SIZE;i++) {
		b->piecesArray[i][6].piceType = pawn;
		b->piecesArray[i][6].playerType = black;
		b->piecesArray[i][7].playerType = black;
	}

	//white
	b->piecesArray[A][0].piceType = rook;
	b->piecesArray[H][0].piceType = rook;
					
	b->piecesArray[B][0].piceType = knight;
	b->piecesArray[G][0].piceType = knight;
					
	b->piecesArray[C][0].piceType = bishop;
	b->piecesArray[F][0].piceType = bishop;
					 
	b->piecesArray[D][0].piceType = queen;
	b->piecesArray[E][0].piceType = king;

	for (int i = 0; i < BOARD_SIZE; i++) {
		b->piecesArray[i][1].piceType = pawn;
		b->piecesArray[i][1].playerType = white;
		b->piecesArray[i][0].playerType = white;
	}
	

	return 1;
}


void printBoard(board* b)
{
	for (int x = 0; x < BOARD_SIZE;x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			switch (b->piecesArray[y][x].piceType)
			{
			case pawn:
				if (b->piecesArray[y][x].playerType)
					printf("P");
				else
					printf("P");
			case rook:
				if (b->piecesArray[y][x].playerType)
					printf("-");
				else
					printf("+");
			case knight:
				if (b->piecesArray[y][x].playerType)
					printf("-");
				else
					printf("+");
			case bishop:
				if (b->piecesArray[y][x].playerType)
					printf("-");
				else
					printf("+");
			case king:
				if (b->piecesArray[y][x].playerType)
					printf("-");
				else
					printf("+");
			case queen:
				if (b->piecesArray[y][x].playerType)
					printf("-");
				else
					printf("+");
			default:
				break;
			}

			if (y == BOARD_SIZE - 1) {
				printf("\n");
			}
		}
	}
}

char* movePiece(piece piece,char **location)
{

}


/*
//open all pieces (including the empty once)
	b->piecesArray = (board*)malloc(sizeof(piece) * BOARD_SIZE * BOARD_SIZE);
	if (b->piecesArray)
		return 0; //faild to open board
*/