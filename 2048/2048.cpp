// 2048.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#pragma warning(disable:4996)
using namespace std;
int num[4][4];
int score, gameover, ifappear, gamew, gamef, moved_steps;
char key;
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__,GetLastError(), api, __LINE__);}
void MyCls(HANDLE);
inline void clrscr(void)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	MyCls(hStdOut);
	return;
}
void MyCls(HANDLE hConsole)
{
	COORD coordScreen = { 0,0 };
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute"); 
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}
int main();
void gamefaile()
{
	clrscr();
	cout << "You Fail!" << endl;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("Your score is %d, and you have moved %d Steps\n", score, moved_steps);
	printf("Press any key to return to main menu...\n");
	getch();
	clrscr();
	main();
}
void gamewin()
{
	clrscr();
	cout << "You Win!" << endl;
	for (int j = 0; j<4; j++)
	{
		for (int i = 0; i<4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("Your score is %d, and you have moved_stepsd %d Steps\n", score, moved_steps);
	printf("Press any key to return to main menu...\n");
	getch();
	clrscr();
	main();
}
void print()
{
	clrscr();
	printf("\t\t\t---------------------\n\t\t\t");
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("Your score is %d, and you have moved_stepsd %d Steps\n", score, moved_steps);
}
void appear()
{
	int ran, t[16], x = 0, a, b;
	srand((int)time(0));
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if (num[j][i] == 0)
			{
				t[x] = j * 10 + i;
				x++;
			}
	if (x == 1)
		ran = x - 1;
	else
		ran = rand() % (x - 1);
	a = t[ran] / 10;
	b = t[ran] % 10;
	srand((int)time(0));
	if ((rand() % 9)>2)
		num[a][b] = 2;
	else
		num[a][b] = 4;
}
void close()
{
	exit(0);
}
void add(int *p)
{

	int i = 0, b;
	while (i<3)
	{
		if (*(p + i) != 0)
		{
			for (b = i + 1; b < 4; b++)
			{
				if (*(p + b) != 0)
					if (*(p + i) == *(p + b))
					{
						score = score + (*(p + i)) + (*(p + b));
						*(p + i) = *(p + i) + *(p + b);
						if (*(p + i) == 2048)
							gamew = 1;
						*(p + b) = 0;
						i = b + i;
						++ifappear;
						break;
					}
					else
					{
						i = b;
						break;
					}
			}
			if (b == 4)
				i++;
		}
		else
			i++;
	}

}
void Gameplay()
{
	int g, e, a, b[4];
	appear();
	appear();
	while (1)
	{
		if (ifappear != 0)
			appear();
		print();
		key = getch();
		switch (key)
		{
		case 'w':
		case 'W':
		case 72:
			ifappear = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					b[i] = num[i][j];
					num[i][j] = 0;
				}
				add(b);
				e = 0;
				for (g = 0; g < 4; g++)
				{
					if (b[g] != 0)
					{
						num[e][j] = b[g];
						if (g != e)
							++ifappear;
						e++;
					}
				}
			}
			if (ifappear != 0)
				++moved_steps;
			break;
		case 's':
		case 'S':
		case 80:
			ifappear = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					b[i] = num[i][j];
					num[i][j] = 0;
				}
				add(b);
				e = 3;
				for (g = 3; g >= 0; g--)
				{
					if (b[g] != 0)
					{
						num[e][j] = b[g];
						if (g != e)
							++ifappear;
						e--;
					}
				}
			}
			if (ifappear != 0)
				++moved_steps;
			break;
		case 'a':
		case 'A':
		case  75:
			ifappear = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					b[i] = num[j][i];
					num[j][i] = 0;
				}
				add(b);
				e = 0;
				for (g = 0; g < 4; g++)
				{
					if (b[g] != 0)
					{
						num[j][e] = b[g];
						if (g != e)
							++ifappear;
						e++;
					}
				}
			}
			if (ifappear != 0)
				++moved_steps;
			break;
		case 'd':
		case 'D':
		case  77:
			ifappear = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					b[i] = num[j][i];
					num[j][i] = 0;
				}
				add(b);
				e = 3;
				for (g = 3; g >= 0; g--)
				{
					if (b[g] != 0)
					{
						num[j][e] = b[g];
						if (g != e)
							++ifappear;
						e--;
					}
				}
			}
			if (ifappear != 0)
				++moved_steps;
			break;
		case 27:
			system("cls");
			main();
			break;
		default:
			break;
		}
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (j < 3)
				{
					if (i < 3)
					{
						if (num[j][i] == num[j + 1][i] || num[j][i] == num[j][i + 1] || num[j][i] == 0)
						{
							gamef = 0;
							break;
						}
						else
							gamef = 1;
					}
					else
					{
						if (num[j][i] == num[j + 1][i] || num[j][i] == 0)
						{
							gamef = 0;
							break;
						}
						else
							gamef = 1;
					}
				}
				else
				{
					if (i < 3)
					{
						if (num[j][i] == num[j][i + 1] || num[j][i] == 0 || num[j][i + 1] == 0)
						{
							gamef = 0;
							break;
						}
						else
							gamef = 1;
					}
				}

			}
			if (gamef == 0)
				break;
		}
		if (gamef == 1 || gamew == 1)
			break;

	}
	if (gamef == 1)
		gamefaile();
	else
		gamewin();
}
void menu()
{
	int n;
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t*              1、Start                 *\n");
	printf("\t\t*              2、Quit                  *\n");
	printf("\t\t*****************************************\n");
	printf("Please input 1 or 2:[ ]\b\b");
	cin >> n;
	switch (n)
	{
	case 1:
		Gameplay();
		break;
	case 2:
		close();
		break;
	}
}
int main()
{
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			num[j][i] = 0;
	gamew = 0, gamef = 0, ifappear = 0, score = 0, gameover = 0, moved_steps = 0;
	menu();
	return 0;
}