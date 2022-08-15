#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {

	int a=0;
	if (scanf("%d", &a) == NULL)
		return 0;
	printf("%d",a);
}