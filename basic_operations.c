#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "helpful_functions.h"

void help()
{
	int sel;

	cleanScreen();
	printGameTitle();
	printf("%s\n","------------------------------" );
	printf("%s%s\n","Instructions for the ",TITLE );
	printf("%s\n","------------------------------" );
	printf("\n%s\n","Commands:" );
	printf("%s\n","----------------------------------------------" );
	printf("%s\n%s\n","1.insert 2.delete 3.showfwd 4.showrev  5.find","6.create 7.load   8.save    9.creators 10.exit");
	printf("%s\n","----------------------------------------------" );
	printf("%s","Enter the number of the command you want to learn about:" );
	scanf("%d",&sel);
	getchar();
	switch(sel)
	{
		case 1:
				printf("%s\n","\"insert\" with this command you can enter words to the list.\nExample:\"insert: [string] \"" );			
			    pause();
		break;

		case 2:
				printf("%s\n","\"delete\" with this command you can delete words from the list.\nExample:\"delete: [string]\"" );			
			    pause();
		break;

		case 3:
				printf("%s\n","\"showfwd\" with this command you can see the whole list from the start to end.\nExample:\"showfwd: [number] \"" );			
			    pause();
		break;

		case 4:
				printf("%s\n","\"showrev\" with this command you can see the whole list from the end to start.\nExample:\"showrev: [number] \"" );			
			    pause();
		break;

		case 5:
				printf("%s\n","\"find\" with this command you can find a word/s to the list.\nExample:\"find: [string] [number] \"" );			
			    pause();
		break;

		case 6:
				printf("%s\n","\"create\" with this command you can create a crossword from the list.\nExample:\"create: [string] [level] \"" );			
			    pause();
		break;

		case 7:
				printf("%s\n","\"load\" with this command you can fill the list with words from a .txt file.\nExample:\"load: [name(no extension!)] \"" );			
			    pause();
		break;

		case 8:
				printf("%s\n","\"save\" with this command you can save the crossword in a file.\nExample:\"save: [name(no extension!)] \"" );			
			    pause();
		break;

		case 10:
				break;

		default:
				printf("%s\n","There is no info about this command or wrong input!Try again!");			
			    pause();
		break;
	}
}

void insert()
{
	if(mode==1)
	{
		cleanCommandFromTheString(7);
		cleanThePunctuationPoints();
		checkCutAndPrintTheWord();	
	}
	else
		readTheFile();
	pause();
}

void delete()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	cleanCommandFromTheString(7);
	deleteTheWordFromTheList();
	
}

void showfwd()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	cleanCommandFromTheString(8);
	showTheList(0);
}

void showrev()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	cleanCommandFromTheString(8);
	showTheList(1);
}

void find()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	cleanCommandFromTheString(5);
	findTheWordInTheList();
}

void create()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	cleanCommandFromTheString(7);
	createTheCrossword();
}

void save()
{
	if(head==NULL)
	{
		printf("%s\n","Sorry,the list is empty!" );
		pause();
		return;
	}
	if(tableForCrossword==NULL && tableForCrosswordWithUnderscope==NULL)
	{
		printf("%s\n","Sorry,you have to create a crossword first.Pleaze try again after you create a crossword(etc. create: car easy)" );
		pause();
		return;
	}
	cleanCommandFromTheString(5);
	saveTheCrossword();
}

void showCreators()
{
	cleanScreen();
	printGameTitle();
	printf("%s%d\n\n","Version:",VERSION);
	printf("%s\n\n","Name: Andreas Christopoulos Email: zrn6770@gmail.com" );
	pause();
}

void freeTheList()
{
	wordList *tmp,*ptr;
	tmp=head;
	while(tmp)
	{
		free(tmp->word);
		ptr=tmp->next;
		free(tmp);
		tmp=ptr;
	}
}

void getCommandAndAct(){
	if(strcmp(cmd,"help")==0)
		help();
	else if(strncmp(cmd,"insert:",7)==0)
	{
		mode=1;
		insert();
	}
	else if(strncmp(cmd,"delete:",7)==0)
		delete();
	else if(strncmp(cmd,"showfwd:",8)==0)
		showfwd();
	else if(strncmp(cmd,"showrev:",8)==0)
		showrev();
	else if(strncmp(cmd,"find:",5)==0)
		find();
	else if(strncmp(cmd,"create:",7)==0)
		create();
	else if(strncmp(cmd,"load:",5)==0)
	{
		mode=0;
		insert();
	}
	else if(strncmp(cmd,"save:",5)==0)
		save();
	else if(strcmp(cmd,"creators")==0)
		showCreators();
	else if(strcmp(cmd,"exit")==0)
	{
		freeTheList();
		died=1;
	} 
	else
	{
		printf("%s%s\n",cmd,": command not found." );
		pause();
	}
}