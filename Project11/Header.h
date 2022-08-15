#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 9 //8X8 is for chess + 1 for numbers and latters
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

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

}piece;

typedef struct
{
	piece piecesArray[BOARD_SIZE][BOARD_SIZE];
	int boardBace[BOARD_SIZE][BOARD_SIZE];
}board;


/*functions*/

//color logic (windows)

void blackOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); }; //black on white
void blackOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); }; //black on black
void grayOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248); }; //white on white
void grayOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120); }; //white on black

void colorChange_white() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); };
void colorChange_gray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); };
void colorChange_whiteBlue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); };

//main functions
void BuildChessBoard(board* b)
{
	//vars 
	int counterForPrintingBlackWhite = white;

	//sets all pieces to empty
	for (int counter1 = 0; counter1 < BOARD_SIZE; counter1++)
	{
		for (int counter2 = 0; counter2 < BOARD_SIZE; counter2++)
		{
			//ini slots
			b->piecesArray[counter1][counter2].piceType = empty;
			b->piecesArray[counter1][counter2].playerType = nor;
			//ini bace (insert one white one black)
			if (counterForPrintingBlackWhite == white)
				b->boardBace[counter1][counter2] = white;
			else
				b->boardBace[counter1][counter2] = black;
			counterForPrintingBlackWhite = !counterForPrintingBlackWhite; 
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

void colorResolver(board* b, int x, int y)
{
	if (b->piecesArray[x][y].playerType == black && b->boardBace[x][y] == white)
		grayOnWhite();
	if (b->piecesArray[x][y].playerType == black && b->boardBace[x][y] == black)
		grayOnLightGray();
	if (b->piecesArray[x][y].playerType == white && b->boardBace[x][y] == white)
		blackOnWhite();
	if (b->piecesArray[x][y].playerType == white && b->boardBace[x][y] == black)
		blackOnLightGray();
}

void printBoard(board* b)
{
	//vars
	char lineAlphabet[9] = { 'A','B','C','D','E','F','G','H',' '};
	char lineNumbers[8] = { '8','7','6','5','4','3','2','1'};


	//print
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{

			
			switch (b->piecesArray[x][y].piceType)
			{
			case pawn:
					colorResolver(b,x,y);
					printf("|P|");
		
				break;
			case rook:
				colorResolver(b, x, y);
				printf("|R|");
				break;
			case knight:
				colorResolver(b, x, y);
				printf("|N|");
				break;
			case bishop:
				colorResolver(b, x, y);
				printf("|B|");
				break;
			case king:
				colorResolver(b, x, y);
				printf("|K|");
				break;
			case queen:
				colorResolver(b, x, y);
				printf("|Q|");
				break;
			case empty:
				colorChange_whiteBlue();
				if (y == BOARD_SIZE-1) 
				{
					printf(" %c ",lineAlphabet[x]);
				}
				else if (x == BOARD_SIZE - 1) {
					printf(" %c ", lineNumbers[y]);
				}
				else {
					colorChange_white();
					printf("|_|");
				}
					
			default:
				colorChange_gray();
				break;
			}
			//on last print
			if (x == BOARD_SIZE - 1) {
				printf("\n");
			}
			else if (y == BOARD_SIZE - 1) {

			}

		}
	}
}

char* movePiece(piece piece,char **location)
{

}

