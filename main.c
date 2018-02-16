/* 
Subject:Crossword
Name: Andreas Christopoulos    
Email: zrn6770@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main(void)
{
	head=NULL;
	tableForCrosswordWithUnderscope=NULL;
	tableForCrossword=NULL;
	listCounter=0;
	srand((unsigned)time(NULL));
	setTitle();
	cleanScreen();
	printGameTitle();
	showMainMenu();
	printf("\n");
	return 0;
}
