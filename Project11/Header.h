#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 9 //8X8 is for chess 9X9 for numbers and latters

#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>


//Globals
char lineAlphabet[BOARD_SIZE] = { 'A','B','C','D','E','F','G','H',' ' };
char lineNumbers[BOARD_SIZE] = { '8','7','6','5','4','3','2','1' };
int zeroIfPawnFirstMoveArray_White[BOARD_SIZE - 1] = { 0 }; //takes track on the first moves of pawns
int zeroIfPawnFirstMoveArray_Black[BOARD_SIZE - 1] = { 0 }; //takes track on the first moves of pawns


/*ENUM*/
enum PieceType { empty, pawn = 1, bishop, knight, rook = 5, queen = 9, king };
enum playerType { black, white, nor };
enum boardCoordinates { A, B, C, D, E, F, G, H };


/*Structs*/
typedef struct
{
	int piceType; //king etc.
	int playerType; //black or white

}piece;

typedef struct
{
	piece piecesArray[BOARD_SIZE][BOARD_SIZE];
	int boardBace[BOARD_SIZE][BOARD_SIZE];
	int playerTurn;
}board;


/*Functions*/
//error message
void error(char* errorMessage) {
	if (errorMessage == NULL)
		printf("Error! unknown error\n");
	else
		printf("Error! code %s\n", errorMessage);
};


//Color logic (windows)
void blackOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); }; //black on white
void blackOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); }; //black on black
void grayOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248); }; //white on white
void grayOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120); }; //white on black
void colorChangeWhiteBlue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); }; //white on blue
void colorChangeDefault() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); }; //default

/*Main game functions*/
void BuildChessBoard(board* b)
{
	//vars 
	int counterForPrintingBlackWhite = white; //start couting from white

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
			counterForPrintingBlackWhite = !counterForPrintingBlackWhite; //flip start
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
	//black pawns
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		b->piecesArray[i][6].piceType = pawn;
		b->piecesArray[i][6].playerType = white;
		b->piecesArray[i][7].playerType = white;
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
	//white pawns
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		b->piecesArray[i][1].piceType = pawn;
		b->piecesArray[i][1].playerType = black;
		b->piecesArray[i][0].playerType = black;
	}
}

//This function takes care of color printing correctly
void colorResolver(board* b, int x, int y)
{
	if (b->piecesArray[x][y].playerType == black && b->boardBace[x][y] == white)
		blackOnWhite();
	if (b->piecesArray[x][y].playerType == black && b->boardBace[x][y] == black)
		blackOnLightGray();
	if (b->piecesArray[x][y].playerType == white && b->boardBace[x][y] == white)
		grayOnWhite();
	if (b->piecesArray[x][y].playerType == white && b->boardBace[x][y] == black)
		grayOnLightGray();

	//default (empty)
	if (b->piecesArray[x][y].piceType == empty && b->boardBace[x][y] == white)
		grayOnWhite();
	if (b->piecesArray[x][y].piceType == empty && b->boardBace[x][y] == black)
		grayOnLightGray();
}

void printBoard(board* b)
{
	//print
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			switch (b->piecesArray[x][y].piceType)
			{
			case pawn:
				colorResolver(b, x, y);
				printf("P ");
				break;
			case rook:
				colorResolver(b, x, y);
				printf("R ");
				break;
			case knight:
				colorResolver(b, x, y);
				printf("N ");
				break;
			case bishop:
				colorResolver(b, x, y);
				printf("B ");
				break;
			case king:
				colorResolver(b, x, y);
				printf("K ");
				break;
			case queen:
				colorResolver(b, x, y);
				printf("Q ");
				break;
			case empty:
				colorResolver(b, x, y);

				if (y == BOARD_SIZE - 1)
				{
					colorChangeWhiteBlue();
					printf("%c ", lineAlphabet[x]);
				}
				else if (x == BOARD_SIZE - 1) {
					colorChangeWhiteBlue();
					printf("%c ", lineNumbers[y]);
				}
				else {
					colorResolver(b, x, y);
					printf("  ");
				}
			default:
				colorChangeDefault();
				break;
			}
			//on last print
			if (x == BOARD_SIZE - 1) {
				printf("\n");
			}
		}
	}
}

//iterprets user command to location in numbers
int* userMoveResolver(char* string, board* b)
{
	int stringToNumbers[4] = { NULL };

	//get the first letter
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		if (string[0] == lineAlphabet[i]) {
			stringToNumbers[0] = i;
			break;
		}
	}
	//make sure it's found (was in range)
	if (stringToNumbers[0] == NULL && stringToNumbers[0] != 0)
		return NULL;

	//Making sure it's always a number
	if (!isdigit(string[1]))
		return NULL;

	//last key
	stringToNumbers[1] = (BOARD_SIZE - 1) - (string[1] - '0');

	/*next location*/

	//get the first letter
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		if (string[2] == lineAlphabet[i]) {
			stringToNumbers[2] = i;
			break;
		}
	}
	//make sure it's found (was in range)
	if (stringToNumbers[2] == NULL && stringToNumbers[2] != 0)
		return NULL;

	//Making sure it's always a number
	if (!isdigit(string[3]))
		return NULL;

	//last key
	stringToNumbers[3] = (BOARD_SIZE - 1) - (string[3] - '0');

	//make sure the move is leagal
	if (moveTester(stringToNumbers, b) == 0)
		return NULL;
	return stringToNumbers;
}

int moveTester(int* userMove, board* b)
{

	/*Pawn move logic*/
	if (b->piecesArray[userMove[0]][userMove[1]].piceType == pawn)
	{
		//black pawn logic
		if (b->piecesArray[userMove[0]][userMove[1]].playerType == black)
		{
			//eating
			if ((userMove[2] - userMove[0] == 1 || userMove[2] - userMove[0] == -1) && (userMove[1] + 1 == userMove[3]) && (b->piecesArray[userMove[2]][userMove[3]].playerType == white))
			{
				return 1;
			}

			//if not first move and trying to jump 2
			if ((zeroIfPawnFirstMoveArray_Black[userMove[0]] != 0) && (userMove[3] - userMove[1] == 2))
			{
				printf("Not first move, can't jump 2!");
				return 0;
			}

			//if skips 2 and there's one on the way
			if ((b->piecesArray[userMove[2]][userMove[3] - 1].piceType != empty) && ((userMove[3] - userMove[1] == 2)))
			{
				//skip if cross eating missing
				printf("You can't skip 2, there's a piece in there!");
				return 0;
			}
			//make sure it's not more then 2
			if (userMove[1] - userMove[3] > 2) {
				printf("Illegal move!");
				return 0;
			}
			//update array that it can't move 2 any more (moved once)
			zeroIfPawnFirstMoveArray_Black[userMove[0]] = 1;
		}

		//white pawn logic
		if (b->piecesArray[userMove[0]][userMove[1]].playerType == white)
		{

			//eating
			if ((userMove[2] - userMove[0] == 1 || userMove[2] - userMove[0] == -1) && (userMove[1] - 1 == userMove[3]) && (b->piecesArray[userMove[2]][userMove[3]].playerType == black))
			{
				return 1;
			}

			//if not first move and trying to jump 2
			if ((zeroIfPawnFirstMoveArray_White[userMove[0]] != 0) && (userMove[1] - userMove[3] == 2))
			{
				printf("Not first move, can't jump 2!");
				return 0;
			}

			//if skips 2 and there's one on the way
			if ((b->piecesArray[userMove[2]][userMove[3] + 1].piceType != empty) && (userMove[1] - userMove[3] == 2)) {
				//skip if cross eating missing
				printf("You can't skip 2!");
				return 0;
			}

			//make sure it's not more then 2
			if (userMove[3] - userMove[1] < -2) {
				printf("Illegal move!");
				return 0;
			}
			//update array that it can't move 2 any more (moved once)
			zeroIfPawnFirstMoveArray_White[userMove[0]] = 1;
		}

		//en passant not included yet!
		if (userMove[0] != userMove[2])
		{
			printf("Pawns can't move like that...\n");
			return 0;
		}
	}


	//if the piece beloges to him- then allow
	if (b->playerTurn != b->piecesArray[userMove[0]][userMove[1]].playerType)
	{
		printf("Illegal move!\n");
		return 0;
	}
	//if target location not empty
	if (b->piecesArray[userMove[2]][userMove[3]].piceType != empty)
	{
		//skip if cross eating missing
		printf("The next place is not empty!");
		return 0;
	}
	/*missing en passant special case*/

	return 1; //approve the move
}

char* movePiece(board* b)
{
	//vars
	char locationToLocation[5] = { NULL }; //for example: d2d4- pawn to from d2 to d4

	//player turn message
	if (b->playerTurn)
		printf("Whites move: ");
	else
		printf("Blacks move: ");

	//get the piece to move
	if (scanf("%s", locationToLocation) == NULL)
		return NULL;
	//cut and make sure it's fine
	int* userFinalMove = { NULL };
	while ((userFinalMove = userMoveResolver(locationToLocation, b)) == NULL) {
		//if illegal move
		printf("\ntry again: ");
		if (scanf("%s", locationToLocation) == NULL)
			return NULL;
	}

	//enter piece to new location
	b->piecesArray[userFinalMove[2]][userFinalMove[3]].piceType = b->piecesArray[userFinalMove[0]][userFinalMove[1]].piceType; //update location
	b->piecesArray[userFinalMove[2]][userFinalMove[3]].playerType = b->playerTurn; //update ownership

	//remove from old loaction
	b->piecesArray[userFinalMove[0]][userFinalMove[1]].piceType = empty;
	b->piecesArray[userFinalMove[0]][userFinalMove[1]].playerType = nor;

	//update turn
	b->playerTurn = !b->playerTurn;
}