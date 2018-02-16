#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpful_functions.h"
#include "header.h"

void cleanCommandFromTheString(int x)
{
	int i;

	for(i=0;i<x;i++)
		cmd[i]=' ';
}

char *capitalizeTheWord(char *word,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(!isupper(word[i]))
			word[i] = word[i] - 32;
	}
	return word;
}

void cleanThePunctuationPoints()
{
	int i;

	i=0;
	while(cmd[i]!='\0')
	{
		if(cmd[i]=='!' || cmd[i]==',' || cmd[i]=='?' || cmd[i]==';' || cmd[i]=='.' || cmd[i]=='"' || cmd[i]=='(' || cmd[i]==')' || cmd[i]==':')
			cmd[i]=' ';
		i++;
	}
}

int returnMaxLength(int x)
{
	int i,y,max;

	max=strlen(tableForCrossword[0]);
	for(i=1;i<x;i++)
	{
		y=strlen(tableForCrossword[i]);
		if(max<y)
			max = y;
	}
	return max;
}


//--------------------->insert()_functions<---------------------------------------------\\

int rejectExtensions(char *x)
{
	if(strcmp(x,"com")==0)
		return 1;
	else if(strcmp(x,"gr")==0)
		return 1;
	else
		return 0;
}

int checkIfisAlpha(char *x)
{
	int i,y,k;
	char ch;
	i=0;

	if(rejectExtensions(x))
		return 1;

	while(x[i] !='\0')
	{
		ch = x[i] + '\0';
		if(!(isalpha(ch)))
		{
			return 1;
		}
		i++;			
	}
	y=strlen(x);
	if(y==1)
		return 1;
	else
		return 0;
}

void swapElementsOfTheList(wordList *node1,wordList *node2)
{
	wordList *tmp;
	tmp = (wordList *) malloc(sizeof(wordList));
	if(tmp==NULL)
	{
		printf("%s\n","Error:Not available memory!" );
		exit(1);
	}

	tmp->word=strdup(node1->word);
	tmp->wordLength=node1->wordLength;
	tmp->uniqLetters=node1->uniqLetters;
	memcpy(tmp->countLetters,node1->countLetters,sizeof(node1->countLetters));
	tmp->numOfTimes=node1->numOfTimes;
	tmp->insertionMode=node1->insertionMode;


	node1->word=strdup(node2->word);
	node1->wordLength=node2->wordLength;
	node1->uniqLetters=node2->uniqLetters;
	memcpy(node1->countLetters,node2->countLetters,sizeof(node1->countLetters));
	node1->numOfTimes=node2->numOfTimes;
	node1->insertionMode=node2->insertionMode;

	node2->word=strdup(tmp->word);
	node2->wordLength=tmp->wordLength;
	node2->uniqLetters=tmp->uniqLetters;
	memcpy(node2->countLetters,tmp->countLetters,sizeof(tmp->countLetters));
	node2->numOfTimes=tmp->numOfTimes;
	node2->insertionMode=tmp->insertionMode;

	free(tmp->word);
	free(tmp);
}

void sortTheList(wordList *newNode)
{
	while(newNode->next!=NULL)
	{
		if(strcmp(newNode->word,newNode->next->word)>0)
			swapElementsOfTheList(newNode,newNode->next);
		newNode=newNode->next;
	}
}

void addNewWordToTheList(char *token)
{
	char alpaphet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i,j;
	wordList *newNode,*tmp;

	newNode = (wordList *) malloc(sizeof(wordList));
	if(newNode==NULL)
	{
		printf("%s\n","Error:Not available memory!" );
		exit(1);
	}
	newNode->word =strdup(token);
	newNode->wordLength = strlen(token);
	newNode->uniqLetters=0;
	for(i=0;i<26;i++)
		newNode->countLetters[i]=0;
	newNode->word=capitalizeTheWord(newNode->word,newNode->wordLength);
	for(i=0;i<sizeof(alpaphet);i++)
	{
		for(j=0;j<newNode->wordLength;j++)
		{
			if(newNode->word[j]==alpaphet[i])
			{
				newNode->countLetters[i]++;
			}
		}
	}
	for(i=0;i<sizeof(alpaphet);i++)
	{
		if(newNode->countLetters[i]!=0)
		{
			newNode->uniqLetters++;
		}
	}
	newNode->numOfTimes = 1;
	newNode->insertionMode = mode;
	if(head==NULL)
	{
		head = newNode;
		head->next=NULL;
		head->previous=NULL;
	}
	else
	{
		newNode->previous=NULL;
		newNode->next=head;
		head->previous=newNode;
		head=newNode;
	}
	sortTheList(newNode);
}

int checkExistenceOfTheWord(char *token)
{
	wordList *tmp;
	int i;

	if(head==NULL)
		return 0;

	tmp=head;
	i=strlen(token);
	token = capitalizeTheWord(token,i);
	while(tmp!=NULL)
	{
		if(strcmp(token,tmp->word)==0)
		{
			tmp->numOfTimes++;
			printf("%s%s\n","This word already exists:",token);
			return 1;
		}
		tmp=tmp->next;
	}
	return 0;
}

void readTheFile()
{
	FILE *fp;
	char *token,*file,x;

	cleanCommandFromTheString(5);
	token=strtok(cmd,SET);
	file=strcat(token,".txt");
	if(!(fp=fopen(file,"r")))
	{
	 	printf("%s%s\n","Error:The file didnt open:",file );
		pause();
		return;
	}
	printf("%s%s\n",file," opened succesfully!" );

	while(fgets(cmd,sizeof(cmd),fp))
	{
		cleanThePunctuationPoints();
		checkCutAndPrintTheWord();
	}
	fclose(fp);
	cleanThePunctuationPoints();
	checkCutAndPrintTheWord();	
}

void checkCutAndPrintTheWord()
{
	int rejected_word,first_time;
	char *token,*tmp;

	first_time=1;
	rejected_word=0;

	printf("%s\n","--------------------" );
		token=strtok(cmd,SET);
		if(token==NULL)
		{
			printf("%s\n","You didnt enter a word!" );
			pause();
			return;
		}
		while(token!=NULL)
		{
			tmp= strdup(token);
			rejected_word = checkIfisAlpha(tmp);
			if(rejected_word==1 && first_time==0)
			{
				printf("%s%s\n","Rejected word:",token );
				rejected_word=0;
			}
			else if(rejected_word==0 && first_time==0)
			{
				if(!checkExistenceOfTheWord(token))
				{
					listCounter++;
					addNewWordToTheList(token);
					printf("%s%s\n","New word added:",token);
				}
			}	
			free(tmp);
			if(first_time==1)
				first_time=0;
			else
				token=strtok(NULL,SET);
		}
		printf("%s\n","--------------------" );
		
}
//--------------------->insert()_functions<---------------------------------------------\\

//--------------------->delete()_functions<---------------------------------------------\\

void deleteTheWordFromTheList()
{
	wordList *tmp,*buf;
	char *token;
	int wlength;
	int i,found=0;

	token=strtok(cmd,SET);
	while(token!=NULL)
	{
		tmp=head;
		wlength=strlen(token);
		token=capitalizeTheWord(token,wlength);
		while(tmp!=NULL)
		{	
			if(strcmp(token,tmp->word)==0)
			{
				found=1;
				listCounter--;
				buf=tmp;
				printf("%s\n","Deleted Word:" );
				printf("---------------------------\n");
				printf("Word:%s\nWordLength:%d\nUniqLetters:%d\nNumOfTimes:%d\nInsertionMode:%d\n",tmp->word,tmp->wordLength,tmp->uniqLetters,tmp->numOfTimes,tmp->insertionMode );
				printf("---------------------------\n");
				if(tmp->previous==NULL && tmp->next==NULL)
				{
					free(tmp->word);
					free(tmp);
					head=NULL;
					break;
				}
				else if(tmp->previous==NULL)
				{
					buf=tmp->next;
					buf->previous=NULL;
					head=buf;
				}
				else if(tmp->next==NULL)
				{
					buf=tmp->previous;
					buf->next=NULL;
				}
				else
				{
					buf=tmp->previous;
					buf->next=tmp->next;
					buf=tmp;
					buf=tmp->next;
					buf->previous=tmp->previous;
				}
				free(tmp->word);
				free(tmp);
				break;
			}
			tmp=tmp->next;
		}
		if(found==0)
			printf("%s%s\n","Sorry,no word matched for ",token);
		token=strtok(NULL,SET);
	}
	pause();
}

//--------------------->delete()_functions<---------------------------------------------\\

//--------------------->showfwd()_functions and showrev()_functions<---------------------------------------------\\

void showTheList(int x)
{
	wordList *tmp;
	int i,times;
	char *token;

	token = strtok(cmd,SET);
	times = atoi(token);
	if(times>listCounter)
		times=listCounter;
	else if(times<0)
	{
		printf("%s\n","Your entered a negative number" );
		pause();
		return;
	}
	tmp=head;
	if(x==0)
	{
		printf("Displaying the list in forward mode:\n");
		for(i=0;i<times;i++)
		{
			printf("---------------------------\n");
			printf("Word:%s\nWordLength:%d\nUniqLetters:%d\nNumOfTimes:%d\nInsertionMode:%d\n",tmp->word,tmp->wordLength,tmp->uniqLetters,tmp->numOfTimes,tmp->insertionMode );
			printf("---------------------------\n");
			tmp=tmp->next;
		}
	}
	else
	{
		printf("Displaying the list in reversed mode:\n");
		while(tmp->next!=NULL)
			tmp=tmp->next;
		for(i=0;i<times;i++)
		{
			printf("---------------------------\n");	
			printf("Word:%s\nWordLength:%d\nUniqLetters:%d\nNumOfTimes:%d\nInsertionMode:%d\n",tmp->word,tmp->wordLength,tmp->uniqLetters,tmp->numOfTimes,tmp->insertionMode );
			printf("---------------------------\n");
			tmp=tmp->previous;
		}
	}
	pause();
}

//--------------------->showfwd()_functions and showrev()_functions<---------------------------------------------\\

//--------------------->find()_functions<---------------------------------------------\\

void findTheWordInTheList()
{
	wordList *tmp;
	char *token,*word;
	int wlength,i,found,times,count;

	count=0;
	found=0;
	token=strtok(cmd,SET);
	word=strdup(token);
	while(token!=NULL)
	{
		times=atoi(token);
		token=strtok(NULL,SET);
	}
	if(times>listCounter)
		times=listCounter;
	else if(times<0)
	{
		printf("%s\n","You enter a negative number!" );
		pause();
		return;
	}
	else if(times==0)
	{
		printf("%s\n","You enter 0 words to find!");
		pause();
		return;
	}
	wlength=strlen(word);
	word=capitalizeTheWord(word,wlength);
	tmp=head;
	while(tmp!=NULL)
	{
		if(strncmp(word,tmp->word,wlength)==0)
		{
			printf("Word found:\n");
			printf("---------------------------\n");	
			printf("Word:%s\nWordLength:%d\nUniqLetters:%d\nNumOfTimes:%d\nInsertionMode:%d\n",tmp->word,tmp->wordLength,tmp->uniqLetters,tmp->numOfTimes,tmp->insertionMode );
			printf("---------------------------\n");
			found=1;
			count++;
		}
		if(count==times)
			break;
		tmp=tmp->next;
	}
	if(found==0)
		printf("%s%s\n","No match found for:",word );
	free(word);
	pause();
}

//--------------------->find()_functions<---------------------------------------------\\

//--------------------->create()_functions<---------------------------------------------\\

void allocateMemoryForTheTables(int x,int z,int i,char *y)
{
	if(x==1)
	{
		if((tableForCrossword = (char **) malloc(z*sizeof(char *)))==NULL || (tableForCrosswordWithUnderscope = (char **) malloc(z*sizeof(char *)))==NULL)
		{
			printf("%s\n","ERROR:Not available memory!" );
			exit(1);
		}
	}
	else
	{
		if(( tableForCrossword[i] = (char *) malloc(sizeof(y)))==NULL || (tableForCrosswordWithUnderscope[i] = (char *) malloc(sizeof(y)))==NULL)
		{
			printf("%s\n","ERROR:Not available memory!" );
			exit(1);
		}
	}
}

void freeTheTables(int x)
{
	int j;
	
	for(j=0;j<x;j++)
	{
		free(tableForCrossword[x]);
		free(tableForCrosswordWithUnderscope[x]);
	}
	free(tableForCrossword);
	free(tableForCrosswordWithUnderscope);
	tableForCrossword=NULL;
	tableForCrosswordWithUnderscope=NULL;
	printf("%s\n","Sorry,the list doesnt have the suitable word in order to create the crossword!Pleaze try again!" );
	pause();
}

void searchForTheSameHideChar(char *x,char z,int l)
{
	int i;
	for(i=1;i<l;i++)
	{
		if(x[i]==z)
			x[i]='_';
	}
}

void putTheUnderscopes(int x,int y,char *z,char *l)
{
	int j,hideChar;
	char hidedCharacter;
	char *wordWithUnderscope;

	wordWithUnderscope = strdup(z);

	if(y<5)
	{
		do
		{
			hideChar = rand() % y;
		}
		while(hideChar==0);
		hidedCharacter=wordWithUnderscope[hideChar];
		wordWithUnderscope[hideChar]='_';
		searchForTheSameHideChar(wordWithUnderscope,hidedCharacter,y);
		tableForCrosswordWithUnderscope[x]=wordWithUnderscope;
	}
	else if(y<7)
	{
		if(strcmp(l,"easy")==0)
		{
			for(j=0;j<2;j++)
			{
				do
				{
					hideChar = rand() % y;
				}
				while(hideChar==0 || wordWithUnderscope[hideChar]=='_');
				hidedCharacter=wordWithUnderscope[hideChar];
				wordWithUnderscope[hideChar]='_';
				searchForTheSameHideChar(wordWithUnderscope,hidedCharacter,y);
			}
			tableForCrosswordWithUnderscope[x]=wordWithUnderscope;
		}
		else if(strcmp(l,"hard")==0)
		{
			for(j=0;j<3;j++)
			{
				do
				{
					hideChar = rand() % y;
				}
				while(hideChar==0 || wordWithUnderscope[hideChar]=='_');
				hidedCharacter=wordWithUnderscope[hideChar];
				wordWithUnderscope[hideChar]='_';
				searchForTheSameHideChar(wordWithUnderscope,hidedCharacter,y);
			}
			tableForCrosswordWithUnderscope[x]=wordWithUnderscope;
		}
	}
	else
	{
		if(strcmp(l,"easy")==0)
		{
			for(j=0;j<3;j++)
			{
				do
				{
					hideChar = rand() % y;
				}
				while(hideChar==0 || wordWithUnderscope[hideChar]=='_');
				hidedCharacter=wordWithUnderscope[hideChar];
				wordWithUnderscope[hideChar]='_';
				searchForTheSameHideChar(wordWithUnderscope,hidedCharacter,y);
			}
			tableForCrosswordWithUnderscope[x]=wordWithUnderscope;
		}
		else if(strcmp(l,"hard")==0)
		{
			for(j=0;j<4;j++)
			{
				do
				{
					hideChar = rand() % y;
				}
				while(hideChar==0 || wordWithUnderscope[hideChar]=='_');
				hidedCharacter=wordWithUnderscope[hideChar];
				wordWithUnderscope[hideChar]='_';
				searchForTheSameHideChar(wordWithUnderscope,hidedCharacter,y);
			}
			tableForCrosswordWithUnderscope[x]=wordWithUnderscope;
		}
	}
}

void fillTheTablesWithTheCrossword(int x,char *y,char *z)
{
	wordList *tmp;
	char *wordToHold;
	int i,j,l,max,first_time,numOfTimes,lengthOfWordToHold;
	
	for(i=0;i<x;i++)
	{
		first_time = 0;
		tmp = head;
		while(tmp!=NULL)
		{
			if(y[i]==tmp->word[0])
			{
				if(first_time==0)
				{
					numOfTimes = tmp->numOfTimes;
					wordToHold = strdup(tmp->word);
					lengthOfWordToHold = strlen(wordToHold);
					first_time = 1;
				}
				else
				{
					for(j=0;j<i;j++)
					{
						if(strcmp(wordToHold,tableForCrossword[j])==0)
						{
							tmp=tmp->next;
							numOfTimes = tmp->numOfTimes;
							wordToHold = strdup(tmp->word);
							lengthOfWordToHold = strlen(wordToHold);
						}
					}
					if(strcmp(z,"easy")==0 && ( numOfTimes < tmp->numOfTimes || lengthOfWordToHold > tmp->wordLength ))
					{
						numOfTimes = tmp->numOfTimes;
						wordToHold = strdup(tmp->word);
						lengthOfWordToHold = strlen(wordToHold);
					}
					else if(strcmp(z,"hard")==0 && (  numOfTimes>tmp->numOfTimes || lengthOfWordToHold < tmp->wordLength ))
					{
						numOfTimes = tmp->numOfTimes;
						wordToHold = strdup(tmp->word);
						lengthOfWordToHold = strlen(wordToHold);
					}
				}
			}
			tmp = tmp->next;
		}
		if(first_time==0)
		{
			freeTheTables(i);
			return;
		}
		allocateMemoryForTheTables(0,0,i,wordToHold);
		tableForCrossword[i] = wordToHold;
		putTheUnderscopes(i,lengthOfWordToHold,wordToHold,z);
	}
	max=returnMaxLength(lengthForWordOfTheCrossword);
	printf("\n%s\n",  "---------------------------------------------------------------------------------------" );
	printf("\t\t\t\t%s\n","   - Crossword -" );
	printf("%s\n\n",  "---------------------------------------------------------------------------------------" );
	for(i=0;i<lengthForWordOfTheCrossword;i++)
	{
		l=strlen(tableForCrosswordWithUnderscope[i]);
		for(j=0;j<l;j++)
			printf("%c ",tableForCrosswordWithUnderscope[i][j]);
		for(j=0;j<max-l;j++)
			printf("  ");
		printf("\t:\t%s\n",tableForCrossword[i] );
	}
	printf("\n%s\n",  "---------------------------------------------------------------------------------------" );
}

void createTheCrossword()
{
	char *token,*wordOfTheCrossword,*difficulty;

	token = strtok(cmd,SET);
	if(token==NULL)
	{
		printf("%s\n","You didnt enter a word!" );
		pause();
		return;
	}
	wordOfTheCrossword = strdup(token);
	lengthForWordOfTheCrossword = strlen(wordOfTheCrossword);
	if(lengthForWordOfTheCrossword==1)
	{
		printf("%s\n","You cant make a crossword with a letter" );
		pause();
		return;
	}
	wordOfTheCrossword = capitalizeTheWord(wordOfTheCrossword,lengthForWordOfTheCrossword);
	while(token!=NULL)
	{
		difficulty = strdup(token);
		token = strtok(NULL,SET);
	}
	if (strcmp(difficulty,"easy")!=0 && strcmp(difficulty,"hard")!=0)
	{
		printf("%s\n","You didnt enter the difficulty!" );
		pause();
		return;
	}
	allocateMemoryForTheTables(1,lengthForWordOfTheCrossword,0," ");
	fillTheTablesWithTheCrossword(lengthForWordOfTheCrossword,wordOfTheCrossword,difficulty);
	pause();
}

//--------------------->create()_functions<---------------------------------------------\\

//--------------------->save()_functions<---------------------------------------------\\

void saveTheCrossword()
{
	FILE *fp;
	char *token,*file;
	int i,j,l,k,max;

	k=lengthForWordOfTheCrossword;
	token=strtok(cmd,SET);
	file=strcat(token,".txt");
	if(!(fp=fopen(file,"w+")))
	{
		printf("%s%s\n","Error:The file didnt open:",file );
		pause();
		return;
	}
	printf("%s%s\n",file," opened succesfully!" );
	max=returnMaxLength(lengthForWordOfTheCrossword);
	fprintf(fp,"\n%s\n",  "---------------------------------------------------------------------------------------" );
	fprintf(fp,"\t\t\t\t%s\n","   - Crossword -" );
	fprintf(fp,"%s\n\n",  "---------------------------------------------------------------------------------------" );
	for(i=0;i<k;i++)
	{
		l = strlen(tableForCrosswordWithUnderscope[i]);
		for(j=0;j<l;j++)
			fprintf(fp,"%c ",tableForCrosswordWithUnderscope[i][j] );
		for(j=0;j<max-l;j++)
			fprintf(fp,"  ");
		fprintf(fp,"\t:\t%s\n",tableForCrossword[i] );
	}
	fprintf(fp,"\n%s\n",  "---------------------------------------------------------------------------------------" );
	fclose(fp);
	printf("%s%s\n","Crossword saved at:",file );
	for(i=0;i<k;i++)
	{
		free(tableForCrosswordWithUnderscope[i]);
		free(tableForCrossword[i]);
	}
	free(tableForCrosswordWithUnderscope);
	free(tableForCrossword);
	tableForCrosswordWithUnderscope=NULL;
	tableForCrossword=NULL;
	printf("%s\n","Crossword was released!" );
	pause();

}
//--------------------->save()_functions<---------------------------------------------\\