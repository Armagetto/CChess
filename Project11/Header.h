﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 9 //8X8 is for chess 9X9 for numbers and latters

#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>



//globals
char lineAlphabet[BOARD_SIZE] = { 'A','B','C','D','E','F','G','H',' ' };
char lineNumbers[BOARD_SIZE] = { '8','7','6','5','4','3','2','1' };


/*define ENUM type */
enum PieceType { empty, pawn = 1, bishop, knight, rook=5, queen = 9, king};
enum playerType { black, white, nor};
enum boardCoordinates { A,B,C,D,E,F,G,H };


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
	int playerTurn;
}board;


/*functions*/
//error message
void error(char* errorMessage) {
	if (errorMessage == NULL )
		printf("Error! unknown error\n"); 
	else
		printf("Error! code %s\n", errorMessage); 
};


//color logic (windows)
void blackOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); }; //black on white
void blackOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); }; //black on black
void grayOnWhite() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248); }; //white on white
void grayOnLightGray() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120); }; //white on black
void colorChangeWhiteBlue() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23); }; //white on blue
void colorChangeDefault() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); }; //default

//main game functions
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

	for (int i = 0; i < BOARD_SIZE-1;i++)
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

	for (int i = 0; i < BOARD_SIZE-1; i++)
	{
		b->piecesArray[i][1].piceType = pawn;
		b->piecesArray[i][1].playerType = black;
		b->piecesArray[i][0].playerType = black;
	}
}

//this function takes care of color printing correctly
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
				colorResolver(b,x,y);
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
				
				if (y == BOARD_SIZE-1) 
				{
					colorChangeWhiteBlue();
					printf("%c ",lineAlphabet[x]);
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
int* stringToPices(char* string)
{
	int stringToNumbers[3] = { NULL };
	switch (string[0])
	{
	case 'p':
		stringToNumbers[0] = pawn;
		break;
	case 'r':
		stringToNumbers[0] = rook;
		break;
	case 'n':
		stringToNumbers[0] = knight;
		break;
	case 'b':
		stringToNumbers[0] = bishop;
		break;
	case 'k':
		stringToNumbers[0] = king;
		break;
	case 'q':
		stringToNumbers[0] = queen;
		break;
	default:
		//no leagal piece was found
		return NULL;
		break;
	}

	
	//get the next latter
	//make sure it's in range
	for (int i = 0; i < BOARD_SIZE - 1;i++) {
		if (string[1] == lineAlphabet[i]) {
			stringToNumbers[1] = i;
			break;
		}
	}
	//make sure it's found (was in range)
	if (stringToNumbers[1] == NULL)
		return NULL;

	//Making sure it's always a number
	if (!isdigit(string[2]))
		return NULL;
	
	
	//last key
	stringToNumbers[2] = (BOARD_SIZE-1) - (string[2] - '0');


	return stringToNumbers;
}

char* movePiece(board* b)
{
	//vars
	char PieceAndLocation[4] = { NULL }; //for example: pd4- pawn to d4
	int i;
	int j;
	int x = 0;
	int y = 0;

	//player turn message
	if (b->playerTurn)
	printf("Whites turn: ");
	else
	printf("Blacks turn: ");

	//get the piece to move
	if (scanf("%s", PieceAndLocation) == NULL)
		return NULL;
	//cut and make sure it's fine
	int* moveCommad;
	while ((moveCommad = stringToPices(PieceAndLocation)) == NULL) {
		//if illegal move
		printf("Bad name!\ntry again: ");
		if (scanf("%s", PieceAndLocation) == NULL)
			return NULL;
	}

	//need to add: cheak that the move was leagal(all the ruls of chess)+ not longer then 3+ on the board
	
	//scan for piece location
	for (i=0; i < BOARD_SIZE-1; i++) {
		for (j=0; j < BOARD_SIZE-1 ; j++) {
			//if found
			if (b->piecesArray[i][j].piceType == moveCommad[0] && b->piecesArray[i][j].playerType == b->playerTurn) {
				//save and brake
				x = i;
				y = j;
				break;
			}
		}
		if (b->piecesArray[i][j].piceType == moveCommad[0] && b->playerTurn == b->playerTurn)
			break;
	}
	//remove from old loaction and save in temp
	b->piecesArray[x][y].piceType = empty;
	b->piecesArray[x][y].playerType = nor;


	//enter piece to new location and update turn
	b->piecesArray[moveCommad[1]][moveCommad[2]].piceType = moveCommad[0]; //update location
	b->piecesArray[moveCommad[1]][moveCommad[2]].playerType = b->playerTurn; //update ownership
	b->playerTurn = !b->playerTurn; //flip turn
}