#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//structs
typedef struct {
	int type;
	char location[8][8];
}piece;

typedef struct {
	char location[8][8];
}board;


//functions
