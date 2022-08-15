#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 9 //8X8 is for chess + 1 for numbers and latters
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>

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

//colors (windows)
void blackOnGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); };
void BlackOnGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); };
			
//void whiteOnGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); };
//void BlackOnGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248); };

void colorChange_white() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); };
void colorChange_gray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); };
void colorChange_whiteBlue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); };
void colorChange_whiteOrBlack(int color)
{
	if (color == white)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	}
	
};


//main functions
void BuildChessBoard(board* b)
{
	//sets all pieces to empty
	for (int counter1 = 0; counter1 < BOARD_SIZE; counter1++)
	{
		for (int counter2 = 0; counter2 < BOARD_SIZE; counter2++)
		{
			b->piecesArray[counter1][counter2].piceType = empty;
			b->piecesArray[counter1][counter2].playerType = nor;
		}
	}

	//sets black
	b->piecesArray[A][7].piceType = rook;
	b->piecesArray[H][7].piceType = rook;

	b->piecesArray[B][7].piceType = knight;
	b->piecesArray[G][7].piceType = knight;

	b->piecesArray[C][7].piceType = bishop;
	b->piecesArray[F][7].piceType = bishop;

	b->piecesArray[D][7].piceType = queen;
	b->piecesArray[E][7].piceType = king;

	for (int i = 0; i < BOARD_SIZE-1;i++)
	{
		b->piecesArray[i][6].piceType = pawn;
		b->piecesArray[i][6].playerType = black;
		b->piecesArray[i][7].playerType = black;
	}

	//sets white
	b->piecesArray[A][0].piceType = rook;
	b->piecesArray[H][0].piceType = rook;
					
	b->piecesArray[B][0].piceType = knight;
	b->piecesArray[G][0].piceType = knight;
					
	b->piecesArray[C][0].piceType = bishop;
	b->piecesArray[F][0].piceType = bishop;
					 
	b->piecesArray[D][0].piceType = queen;
	b->piecesArray[E][0].piceType = king;

	for (int i = 0; i < BOARD_SIZE-1; i++)
	{
		b->piecesArray[i][1].piceType = pawn;
		b->piecesArray[i][1].playerType = white;
		b->piecesArray[i][0].playerType = white;
	}
}

void printBoard(board* b)
{
	//vars
	char lineAlphabet[9] = { 'A','B','C','D','E','F','G','H',' '};
	char lineNumbers[8] = { '8','7','6','5','4','3','2','1'};
	int blockColorDecider = black;

	//print
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{

			//print first '|' in the correct color
			colorChange_whiteOrBlack(blockColorDecider);
			printf("|");

			switch (b->piecesArray[y][x].piceType)
			{
			case pawn:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
					printf("P");
				break;
			case rook:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
				printf("R");
				break;
			case knight:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
				printf("N");
				break;
			case bishop:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
				printf("B");
				break;
			case king:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
				printf("K");
				break;
			case queen:
				if (b->piecesArray[y][x].playerType)
					colorChange_gray();
				else
					colorChange_white();
				printf("Q");
				break;
			case empty:
				colorChange_whiteBlue();
				if (x == BOARD_SIZE-1) 
				{
					printf(" %c ",lineAlphabet[y]);
				}
				else if (y == BOARD_SIZE - 1) {
					printf(" %c ", lineNumbers[x]);
				}
				else {
					colorChange_white();
					printf("_");
				}
					
			default:
				colorChange_gray();
				break;
			}
			//on last print
			if (y == BOARD_SIZE - 1) {
				printf("\n");
			}
			


			colorChange_whiteOrBlack(blockColorDecider);
			printf("|");
			blockColorDecider = !blockColorDecider;
		}
	}
}

char* movePiece(piece piece,char **location)
{

}

