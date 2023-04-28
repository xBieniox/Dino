#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <direct.h>
#include <fstream>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20

using namespace std;
//		cout<<"±±±±±±±±±";

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
bool lock = false;
int trapPos[3];
int spacebtw=61;
int trapFlag[3];
int dinofly = 0;
int walk = 0;
int k=0;
int m1=0;
int m2=0;
string swaper;
string nickname = "unknown";

char dino[4][8] = {' ', ' ', ' ', ' ', '_', '_', '_', ' ',
				   ' ', ' ', '_', '/', ' ', '"', '_', '|',
				   ' ', '|', '_', '_', '_', '/', '=', ' ',
				   '/', ' ', '|', '\\', ' ', ' ', ' ', ' '};

char dino2[4][8] = {' ', ' ', ' ', ' ', '_', '_', '_', ' ',
					' ', ' ', '_', '/', ' ', '"', '_', '|',
					' ', '|', '_', '_', '_', '/', '=', ' ',
					'/', ' ', '/', '|', ' ', ' ', ' ', ' '};

					char trap[3][3] = { ' ', '|', ' ', 
										'L', '|', ' ', 
										' ', '|', 'j'};

int dinoPos = 4;
int score = 0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void Leaderboard()
{
	system("cls");
	ifstream plik("C:\\Users\\bieni\\OneDrive\\Pulpit\\c\\flappy\\score.txt");
	if(plik.is_open())
	{
char word[100];
string leader[10];
while(plik.getline(word,100))
{
	
	
	leader[k]=word;
	k+=1;
}

for(int i=0; i<k;i++)
{
	gotoxy(10, 5+i);
	cout<<i+1<<". "<<leader[i];
}

	}
	else
		cout<<"Nie udało się otworzyć pliku";

			getch();
}
void Leaderboardscore()
{
	ifstream plik("C:\\Users\\bieni\\OneDrive\\Pulpit\\c\\flappy\\score.txt");
	if(plik.is_open())
	{
char word[100];
string leader[500];
while(plik.getline(word,100))
{
	
	
	leader[k]=word;
	k+=1;
}
leader[k+1]=to_string(score)+" "+nickname;

for(int j=0; j<k+1;j++)
{
for(int o=k+1;o>0;o--)
{
	m1=stoi(leader[j].substr(0,2));
	m2=stoi(leader[o].substr(0,2));

	cout<<m1;
	cout<<m2;
	getch();
	if(m1>m2)
	{

	}
	else{
swaper=leader[j];
leader[j]=leader[o];
leader[o]=swaper;

	}
}
}


for(int i=0; i<3;i++)
{
	gotoxy(10, 5+i);
	cout<<i+1<<". "<<leader[i];
}

	}
	else
		cout<<"Nie udało się otworzyć pliku";
		getch();
}

void Nickname()
{

	system("cls");
	gotoxy(10, 9);
	cout << "Write down your nickname and double click enter";
	gotoxy(10, 10);
	cin >> nickname;

	cout << "\n----------------------------------------------------->";

	getch();
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder()
{

	for (int i = 0; i < SCREEN_WIDTH+1; i++)
	{
		gotoxy(i, 0);
		cout << "_";
		gotoxy(i, SCREEN_HEIGHT+1);
		cout << "_";
		gotoxy(i, SCREEN_HEIGHT);
		cout << "^";
	}

	for (int i = 0; i < SCREEN_HEIGHT+1; i++)
	{
		gotoxy(0, i);
		cout << "||";
		gotoxy(SCREEN_WIDTH, i);
		cout << "||";
	}
	for (int i = 0; i < SCREEN_HEIGHT+1; i++)
	{
		gotoxy(WIN_WIDTH, i);
		cout << "||";
	}
}

void drawTrap(int ind)
{
	if (trapFlag[ind] == true)
	{

			
		for (int i = 0; i < 3; i++)
		{
			for (int j = -1; j < 2; j++)
			{
					gotoxy(WIN_WIDTH - trapPos[ind]+j, SCREEN_HEIGHT-1-i);
				cout << trap[i][j+1];
			}
		}
	}
}
void eraseTrap(int ind)
{
	if (trapFlag[ind] == true)
	{

		
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = -1; j < 2; j++)
			{
					gotoxy(WIN_WIDTH - trapPos[ind]+j, SCREEN_HEIGHT-1-i);
				cout << " ";
			}
		}
	}
}

void drawDino()
{

	if (walk == 0)
	{
		walk = 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				gotoxy(j + 4, i + dinoPos);
				cout << dino[i][j];
			}
		}
	}
	else
	{
		walk = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				gotoxy(j + 4, i + dinoPos);
				cout << dino2[i][j];
			}
		}
	}
}
void eraseDino()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gotoxy(j + 4, i + dinoPos);
			cout << " ";
		}
	}
}

int collision()
{
	for (int i = 61; i < 64; i++)
	{
		if (trapPos[0] >= i)
		{
			for (int j = -1; j < 2; j++)
			{
				if (dinoPos+j > SCREEN_HEIGHT - 5)
				{
					//			cout<< " uderzylo ";
					//			getch();
					Leaderboardscore();
					return 1;
				}
			}
		}
	}
	return 0;
}
void debug()
{
	gotoxy(SCREEN_WIDTH + 3, 4);
	cout << "Trap Pos: " << trapPos[0];
	gotoxy(SCREEN_WIDTH + 3, 6);
	cout << "Dino Pos: " << dinoPos;
}
void gameover()
{
	system("cls");
	cout << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------" << endl
		 << endl;
	cout << "\t\tPress any key to go back to menu.";
	getch();
}
void updateScore()
{
	gotoxy(WIN_WIDTH + 7, 5);
	cout << "Score: " << score << endl;
}

void instructions()
{

	system("cls");
	cout << "Instructions";
	cout << "\n----------------";
	cout << "\n Press spacebar to make dino jump";
	cout << "\n\nPress any key to go back to menu";
	getch();
}

void play()
{

	dinoPos = SCREEN_HEIGHT - 4;
	score = 0;
	trapFlag[0] = 1;
	trapFlag[1] = 0;
	trapPos[0] = trapPos[1] = 4;

	system("cls");
	drawBorder();
	
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2);
	cout << "Dino Jump";
	gotoxy(WIN_WIDTH + 6, 4);
	cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6);
	cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12);
	cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13);
	cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14);
	cout << " Spacebar = jump";

	gotoxy(10, 5);
	cout << "Press any key to start";
	getch();
	gotoxy(10, 5);
	cout << "                      ";

	while (1)
	{

		if (!lock)
		{
			if (kbhit())
			{
				char ch = getch();
				if (ch == 32)
				{
					if (dinoPos == SCREEN_HEIGHT - 4)

						lock = true;
					dinofly += 1;
				}
				if (ch == 27)
				{
					break;
				}
			}
		}

		drawDino();
		drawTrap(0);
		drawTrap(1);
		debug();
		if (collision() == 1)
		{
			gameover();
			return;
		}

		if (score < 30)
		{
			Sleep(100 - score * 3);
		}
		else
		{
			Sleep(10);
		}
		eraseDino();
		eraseTrap(0);
		eraseTrap(1);

		if (dinofly > 4)
		{
			if (dinoPos < SCREEN_HEIGHT - 4)
			{

				dinoPos += 1;
			}
			else
			{
				lock = false;
				dinofly = 0;
			}
		}
		else if (dinofly > 0)
		{
			dinoPos -= 1;
			dinofly += 1;
		}

		if (trapFlag[0] == 1)
			trapPos[0] += 2;

		if (trapFlag[1] == 1)
			trapPos[1] += 2;

		if (trapPos[0] >= 40 && trapPos[0] < 42)
		{
			trapFlag[1] = 1;
			trapPos[1] = 4;
			
		}
		if (trapPos[0] > 68)
		{
			score++;
			updateScore();
			trapFlag[1] = 0;
			trapPos[0] = trapPos[1];
		}
	}
}

int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do
	{
		system("cls");
		gotoxy(10, 5);
		cout << " -------------------------- ";
		gotoxy(10, 6);
		cout << " |       DINO  JUMP       | ";
		gotoxy(10, 7);
		cout << " --------------------------";
		gotoxy(10, 9);
		cout << "1. Play";
		gotoxy(10, 10);
		cout << "2. Instructions";
		gotoxy(10, 11);
		cout << "3. Leaderboard";
		gotoxy(10, 12);
		cout << "4. Nickname";
		gotoxy(10, 13);
		cout << "5. Quit";
		gotoxy(10, 15);
		cout << "Select option: ";
		char op = getche();

		switch (op)
		{
		case '1':
			play();
			break;
		case '2':
			instructions();
			break;
		case '3':
			Leaderboard();
			break;
		case '4':
			Nickname();
			break;
		case '5':
			exit(0);
			break;
		}

	} while (1);

	return 0;
}
