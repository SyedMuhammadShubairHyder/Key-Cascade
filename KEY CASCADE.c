

#include<conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 50

int wordnum=0,esc=1;
clock_t start_time=0, end_time;double word_time_taken=0;
double total_time_taken = 0;
float choice=0;
char origlist[1000][100],userlist[1000][100],playername[100];


//THIS Will return the size of File 
int getFileSize(FILE *file)
{
	fseek(file, 0, SEEK_END);//it will set pointer at end
	int size = ftell(file);//this will tell the current location as we are already at the end so we get the size of file
	rewind(file);//it will set the pointer at the start
	return size;
}

// This Function Will Calculate the width By the Help of window.h library
int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// This Function Will Calculate the Height
int getConsoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
//this will clear the output of Counsol window with the help of stdlib library
void clearScreen()
{
	system("cls");
}

void pause()
{
	clearScreen();
	esc=0;
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

	// Get console width
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	// Calculate left padding for center alignment
	int padding = (consoleWidth - 12) / 2;
	
	printf("\n\n\n\n%*s============================================================%*s", padding-20, "", padding, "");
	
	printf("\n\n%*sPAUSE  MENU:%*s", padding, "", padding, "");
	printf("\n\n%*s============================================================%*s", padding-20, "", padding, "");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	printf("\n\n\n%*s1. RESTART GAME %*s\n\n%*s2. RETURN TO INSTRUCTIONS%*s\n\n%*s3. RETURN TO MENU%*s\n\n%*s4. RESUME%*s\n\n%*s5. QUIT GAME",padding-5, "", padding-5, "",padding-5, "", padding-5, "",padding-5, "", padding-5, "",padding-5, "", padding-5, "", padding-5, "");
	while (esc<1 || esc>5)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		printf("\n\n%*sENTER YOUR CHOICE :", padding-5, "", padding-5, "");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		scanf("%d",&esc);
		if(esc<1 || esc>5)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("\n\n%*sINVALID CHOICE!!!%*s", padding, "", padding, "");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
	getchar();
}

// This function will generate random words from file
char *getRandomWord(FILE *file, char *randomWord)//this function will take the file pointer and char pointer 
{

	fseek(file, 0, SEEK_SET); // it will set the cursor to the begining of file

	int numWords = 0; // this will calculate total words in file
	while (fscanf(file, "%*s") != EOF)//%*s will read the srting but will not store it anywhere
	{
		numWords++;
	}

	// this will generate a random position in the calculated  words Range
	int randomPosition = rand() % numWords;

	//To Read the words at required position 
	fseek(file, 0, SEEK_SET);//we will set cursor in file to start
	for (int i = 0; i < randomPosition; ++i)//then start moving it word by word until random position is reache
	{
		fscanf(file, "%*s");//we use %*s to read the word which will move the cursor to the requried word
	}

	fscanf(file, "%s", randomWord); // Now it will read the random word

	return randomWord; 
}


void movingtext(float choice)//this function will take choice as argument
{
	FILE *file = NULL;
	int x, y;
	int counsolheight;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get console width
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1,padding = (consoleWidth - 12) / 2;
			

	srand(time(NULL));//seed the random value
	
	char randomWord[MAX_WORD_LENGTH];//array to store random word
	//we have different file for different levels
	if (choice == 2)
	{
		file = fopen("beginner.txt", "r");
	}
	else if (choice == 3)
	{
		file = fopen("intermediate.txt", "r");
	}
	else if (choice == 4)
	{
		file = fopen("advance.txt", "r");
	}
	if (file == NULL)//this will handle the sitution when there is eror opening file
	{
		printf("ERROR OPENING FILE");
		exit(1);
	}

	//this will run upto the number of words user has entered
	for (int i = 0; i < wordnum; i++)
	{
		clearScreen();
		strcpy(origlist[i], getRandomWord(file, randomWord));//this will store random words int the array
		//starting position
		x = 0; 
		y = 0;

		while (1)
		{
			clearScreen();
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("%*sTO PAUSE: ", padding-8, "");
			
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("PRESS '0' THEN, 'ENTER' ");
			//this is responsible for moving the cursor on the counsol window taking arguments as x and y position
			COORD coord;
			coord.X = 0;
			coord.Y = getConsoleHeight() - 7;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			
			
			for (int i = 0; i < consoleWidth; i++) 
			{
			printf("-");
			}	
			
			printf("\n\n PLAYER NAME: ");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("%s",playername);
			
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("\n\n NUMBER OF WORDS: ");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("%d / %d",i+1,wordnum);

			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

			printf("%s", origlist[i]);
			//this will change the position of word at every iteratiom
			// Update the position for the next iteration
			x += 13; // Adjust the speed in the x-direction
			y += 5;	 // Adjust the speed in the y-direction
			//when it will reach the bottom i.e value of y will be equal or greater then counsol window it will stop 
			if (y >= getConsoleHeight()-9)
			{
				
				
				printf("\n\n%*sTYPE THE WORD: ", padding-5, "");
				start_time = clock();
				gets(userlist[i]);//it will take the user input
				end_time = clock();
				word_time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
				total_time_taken += word_time_taken; 
				
				//this whole will take the word to the another end of window making it looks like a V shape pattern
				y = y - 10;
				x = x + 8;
				
				for (int j = 0; j < strlen(origlist[i]); j++)
        		{
            		if (userlist[i][j] == '0')
            		{
            			pause();
            			if(esc==4)
            			{
            				i--;
            				break;
						}
						else
						{
							return;
						}
            		}
            		
            	}
				for (int k = 0; k < ((getConsoleWidth() / 20)) -2 || y == 0; k++)
				{	
					
					COORD coord;
					coord.X = x;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					y -= 5;
					x += 8;
					printf("%s", origlist[i]);
					coord.X = 0;
					coord.Y = getConsoleHeight() - 7;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					for (int i = 0; i < consoleWidth; i++) 
					{
						printf("-");
					}	
				
					printf("\n\n PLAYER NAME: ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%s",playername);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					printf("\n\n NUMBER OF WORDS: ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%d / %d",i+1,wordnum);
					
					coord.X = 0;
					coord.Y = 0;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					printf("%*sTO PAUSE: ", padding-8, "");
			
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("PRESS '0' THEN, 'ENTER' ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					Sleep(400);
					clearScreen();
				}

				break;
			}
			Sleep(400);//this will delay the word movement
		}
	}
	fclose(file);//this will close the file
}

void Practice()
{
	//In the prevoius function I have added comments for explanation 
	int counsolheight;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get console width
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1,padding = (consoleWidth - 12) / 2;


	int x , y ;
	
	srand(time(NULL));
	char randomWord[MAX_WORD_LENGTH];

	for (int i = 0; i < wordnum; i++)
	{
		for (int i = 0; i < 15; ++i)
		{
			char randomChar = 'a' + rand() % 26;
			randomWord[i] = randomChar;
		}
		randomWord[10] = '\0';

		strcpy(origlist[i], randomWord);

		x = 0;
		y = 0;
		while (1)
		{
			clearScreen();
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("%*sTO PAUSE: ", padding-8, "");
			
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("PRESS '0' THEN, 'ENTER' ");
			//this is responsible for moving the cursor on the counsol window taking arguments as x and y position
			COORD coord;
			coord.X = 0;
			coord.Y = getConsoleHeight() - 7;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			
			
			for (int i = 0; i < consoleWidth; i++) 
			{
			printf("-");
			}	
			
			printf("\n\n PLAYER NAME: ");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("%s",playername);
			
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("\n\n NUMBER OF WORDS: ");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("%d / %d",i+1,wordnum);

			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

			printf("%s", origlist[i]);
			//this will change the position of word at every iteratiom
			// Update the position for the next iteration
			x += 13; // Adjust the speed in the x-direction
			y += 5;	 // Adjust the speed in the y-direction
			//when it will reach the bottom i.e value of y will be equal or greater then counsol window it will stop 
			if (y >= getConsoleHeight()-9)
			{
				
				
				printf("\n\n%*sTYPE THE WORD: ", padding-5, "");
				start_time = clock();
				gets(userlist[i]);//it will take the user input
				end_time = clock();
				word_time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
				total_time_taken += word_time_taken; 
				
				//this whole will take the word to the another end of window making it looks like a V shape pattern
				y = y - 10;
				x = x + 8;
				
				for (int j = 0; j < strlen(origlist[i]); j++)
        		{
            		if (userlist[i][j] == '0')
            		{
            			pause();
            			if(esc==4)
            			{
            				i--;
            				break;
						}
						else
						{
							return;
						}
            		}
            		
            	}
				for (int k = 0; k < ((getConsoleWidth() / 20)) -2 || y == 0; k++)
				{	
					
					COORD coord;
					coord.X = x;
					coord.Y = y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					y -= 5;
					x += 8;
					printf("%s", origlist[i]);
					coord.X = 0;
					coord.Y = getConsoleHeight() - 7;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					for (int i = 0; i < consoleWidth; i++) 
					{
						printf("-");
					}	
				
					printf("\n\n PLAYER NAME: ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%s",playername);
					
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					printf("\n\n NUMBER OF WORDS: ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%d / %d",i+1,wordnum);
					
					coord.X = 0;
					coord.Y = 0;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					printf("%*sTO PAUSE: ", padding-8, "");
			
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("PRESS '0' THEN, 'ENTER' ");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					Sleep(400);
					clearScreen();
				}

				break;
			}
			Sleep(400);//this will delay the word movement
		}
	}
}


int rowLength(char arr[][100], int row)
{
	int length = 0;
	while (arr[row][length] != '\0')
	{
		length++;
	}
	return length;
}
void home()
{	
	clearScreen();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

	// Get console width
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	// Calculate left padding for center alignment
	int padding = (consoleWidth - 12) / 2;
	

	// Print top border
	for (int i = 0; i < consoleWidth; i++) {
		printf("=");
	}

	// Print heading with padding for center alignment
	printf("\n\n%*sKEY CASCADE%*s", padding, "", padding, "");

	// Print bottom border
	printf("\n\n");
	for (int i = 0; i < consoleWidth; i++) {
		printf("=");
	}
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\n\n\n\n%*sQ	W	E	R	T	Y	U	I	O	   P"	, padding-22, "");
	printf("\n\n%*s\tA	S	D	F	G	H	J	K	L"	, padding-22, "");
	printf("\n\n%*s\t\tZ	X	C	V	B	N	M"	, padding-20, "");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	
	printf("\n\n\n\n%*s\"Welcome to KEY CASCADE! A game to enhance your typing accuracy and speed.%*s\n%*sThe objective is to type the printed words quickly and accurately.\"", padding-27, "", padding-20, "", padding-22, "");

	printf("\n\n\n\n\n - ENTER YOUR NAME: ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gets(playername);
	
	esc++;
}
void instructions()
{
	clearScreen();
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - 12) / 2;
    for (int i = 0; i < consoleWidth; i++)
    {
        printf("=");
    }

    
    printf("\n\n%*sINSTRUCTIONS\n\n", padding, "", padding, "");
    
    for (int i = 0; i < consoleWidth; i++)
    {
        printf("=");
    }
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n- Set Up:\n");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	
	printf("   a. Find a quiet and comfortable place to play the game.\n");
	printf("   b. Ensure your keyboard is in good working condition.\n");
	printf("   c. Open a text editor or use an online typing website/game.\n");
	printf("   d. Adjust the font size and screen brightness for better visibility.\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("2. Warm-Up:\n");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	printf("   a. Before starting the challenge, take a few minutes to warm up your fingers. Stretch them and rotate your wrists to avoid any discomfort or strain.\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n4. START THE GAME:\n");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	printf("   a. Once you've chosen the difficulty level, Enter it and get started.\n");
	printf("   b. A word or sentence will appear on the screen for you to type.\n");
	printf("   c. Type the given text as accurately and quickly as possible.\n");
	printf("   d. Pay attention to capitalization, punctuation, and spelling.\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n5. SCORING:\n");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	printf("   a. The game will track your typing speed and accuracy.\n");
	printf("   b. Your typing speed is measured in words per minute (WPM), indicating how many words you can type in one minute.\n");
	printf("   c. Accuracy is measured by calculating the percentage of correctly typed letters.\n");
	printf("   d. The game will also provide feedback on your typing errors, such as mistyped characters or missed words.\n\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\nNow that you have the instructions, it's time to put your typing skills to the test! Challenge yourself, have fun, and watch your typing speed and accuracy improve over time. Happy typing!\n");
	
	printf("\n\n\n - PRESS ANY KEY TO CONTINUE:");
	getch();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	esc++;
	
}
void menu()
{
	clearScreen();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    
    int padding = (consoleWidth - 12) / 2;

    for (int i = 0; i < consoleWidth; i++)
    {
        printf("=");
    }

    
    printf("\n\n%*sMAIN MENU\n\n", padding, "", padding, "");
    
    for (int i = 0; i < consoleWidth; i++)
    {
        printf("=");
    }
    
    printf("\n\n\n  1.  ACCURACY EXERCISE: ");
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("It is designed for users who strictly want to improve their accuracy. ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n  2.  BEGINNER:  ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Suitable for those who want easy english words to improve their typing technique and speed. ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n  3.  INTERMEDIATE:  ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Ideal for those who want difficult english words to enhance their speed and accuracy. ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n  4.  ADVANCE:  ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("Recommended for experienced typists looking for advance english words for a real challenge. ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n  5.  QUIT GAME: ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("The game will close imediately. ");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    while ((choice<1 || choice>5))
	{
		printf("\n\n  - ENTER YOUR CHOICE (ONLY INTEGER): ");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		scanf("%f",&choice);
		if(choice<1 || choice>5)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
			printf("\n\n  \"INVALID CHOICE!!!\"");
		}
	}
	
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("\n\n- HOW MANY WORDS DO YOU WANT TO PRACTISE(ONLY INTEGER): ");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    scanf("%d",&wordnum);
    getchar();
    
    esc++;
}
void Gamereport(int wordnum)
{
    clearScreen();
    int total = 0;
    float accuracy = 0;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    
    int padding = (consoleWidth - 12) / 2;

    
    for (int i = 0; i < consoleWidth; i++)
    {
        printf("=");
    }

    
    printf("\n\n%*sGAME REPORT%*s", padding, "", padding, "");

    printf("\n\n");
    for (int i = 0; i < consoleWidth; i++) {
        printf("=");
    }
	
	printf("\n\n%*sPLAYER NAME:", padding, "");
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    printf(" %s ",playername);
    
    printf("\n\n%*sORIGINAL WORD:    |    PLAYER'S INPUT:%*s", padding - 11, "", padding, "");
    for (int i = 0; i < wordnum; i++)
    {
        printf("\n\n%*s%d. ", padding - 13, "", i + 1);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("%s", origlist[i]);
        
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\t\t\t");
        for (int j = 0; j < strlen(origlist[i]); j++)
        {
            if (origlist[i][j] == userlist[i][j])
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                printf("%c", userlist[i][j]);

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                accuracy += 1;
                total += 1;
            }
            else
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

                printf("%c", userlist[i][j]);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                total += 1;
            }
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("\n\n\n\n");
    for (int i = 0; i < consoleWidth; i++) 
	{
        printf("=");
    }
    
    accuracy = (accuracy / total) * 100;

    printf("\n\n%*sACCURACY = %.1f %% \tSPEED = %.1f WORDS PER MIN\n", padding - 11, "", accuracy,wordnum/(total_time_taken/60));
    
    for (int i = 0; i < consoleWidth; i++) 
	{
        printf("=");
    }
    printf("\n\n%*sSUGGESTIONS FOR IMPROVEMENT%*s", padding-10, "", padding, "");
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    printf("\n\n%*s- To improve your typing skills, make it a habit to practice regularly.", padding-30, "");
	printf("\n\n%*s- Aim for consistency rather than speed initially, gradually increasing your speed over time.", padding-30, "");
	printf("\n\n%*s- Focus on accuracy and proper finger placement on the keyboard.", padding-30, "");
	printf("\n\n%*s- Keep a record of your WPM and accuracy to monitor your progress.", padding-30, "");
	printf("\n\n%*s- Set goals for yourself and try to beat your previous scores.\n\n\n\n", padding-30, "");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    
    for (int i = 0; i < consoleWidth; i++) 
	{
        printf("=");
    }
	
	while (esc<0 || esc>1)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		printf("\n\n\n\n%*sPRESS '1' TO RESTART GAME OR '0' TO QUIT GAME: ", padding-20, "");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		scanf("%d",&esc);
		if(esc<0 || esc>1)
		{
			printf("\n\n%*sINVALID CHOICE!!!%*s", padding, "", padding, "");
		}                                                                
	}
	
	if(esc==0)
	{ 	
	 	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		clearScreen();
		printf("\n\n\n\n%*s\"THANK YOU FOR PLAYING\"\n\n\n%*s", padding-10, "", padding, "");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	getchar();
}
	
int main()
{
	printf("\n\n\n\t\t\t\"ENTER FULL SCREEN FOR BETTER EXPERIENCE\"");
	printf("\n\n\n\t\t\t\t\"PRESS ANY KEY TO CONTINUE:\"");
	getch();
	
	while(esc==1)
	{
		home();
		while (esc==2)
		{
			instructions();
			while (esc==3)
			{
				menu();
				if(choice==1 && esc==4)
				{
					Practice();
				}
				else if(esc==4 && choice!=1)
				{
					movingtext(choice);
				}
				if(esc==4)
				{
					Gamereport(wordnum);
					
				}
			}
		}
	}   
	exit(0);

}   
    