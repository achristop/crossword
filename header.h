#define TITLE "Crossword"
#define VERSION 1

//START - Structs
typedef struct wList
{
 char *word; // the stored word
 int wordLength; // length of the word in letters
 int uniqLetters; // number of unique word letters
 int countLetters[26]; // Counts every letter of the word
 int numOfTimes; // no of times the word appears in the text
 int insertionMode; //0 from file, 1 from keyboard
 struct wList *next;
 struct wList *previous;
} wordList;
//END - Structs

//START - Functions 
void pause();
void getCommandAndAct();
void cleanScreen();
void printGameTitle();
void setTitle();
void showMainMenu();
//END - Functions

//START - Global var
int died;
int mode;
char cmd[1200];
int listCounter;
char **tableForCrossword,**tableForCrosswordWithUnderscope;
wordList *head;
//END - Global var