#include <stdio.h>
#include <stdlib.h>
#include "header.h"



void cleanScreen()
{
	//A function for easy transfer from windows to unix and respectively from unix to windows.

	// linux
	#ifdef linux
	system("clear");
	#endif
	
	//WINDOWS
	#ifdef _WIN32
	system("cls");
	#endif
}

void printGameTitle()
{
	//Prints game's title
	printf("%s%s%d%s\n",TITLE," [ Version ",VERSION," ]");
}

void pause()
{
	printf("%s\n","Press enter to continue . . ." );
	while(getchar()!='\n');
}

void setTitle()
{
	//Windows title 
	#ifdef _WIN32
	system("title Crossword");
	#endif
	//Unix title
	#ifdef linux
	system("PS1='Crossword'");
	#endif
}

void showMainMenu()
{
	while(1)
	{
			cleanScreen();
			printGameTitle();
			printf("\n%s\n","If you need instructions enter \"help\"." );
			printf("$>");
			gets(cmd);
			getCommandAndAct();
			if(died==1){
				printf("%s%s\n","Thank you for using ",TITLE );
				pause();
				break;
			}
	}
}