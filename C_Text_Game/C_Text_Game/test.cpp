#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 100
#define HEIGHT 30

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define Player_x_limit 60
#define Player_y_limit 7

#define MONSTER1_Y_LIMIT 20
#define MONSTER2_Y_LIMIT 16

#define BULLET_SIZE 6

struct Monster {
	int x;
	int y;
	const char* shape;
};

struct Bullet
{
	int x;
	int y;
	const char* attack;
	int attack_time = 0;
	int attack_delay = 0;
};

void gotoXY(int x, int y)
{
	// x, y 좌표 설정
	COORD position = { x,y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

static int index = 0;

void Launch(Bullet* enemy)
{
	index++;

	if (index % BULLET_SIZE == 0)
	{
		index = 0;
	}
}

int main()
{
	struct Monster monster[2] = { {76,12,"♣"}, { 76,24,"♣"} };
	struct Bullet monster1_attack[6] = { {monster[0].x, monster[0].y,"☎", 0,0},{monster[0].x, monster[0].y,"☎", 0,0},{monster[0].x, monster[0].y,"☎", 0,0},{monster[0].x, monster[0].y,"☎", 0,0},{monster[0].x, monster[0].y,"☎", 0,0},{monster[0].x, monster[0].y,"☎", 0,0} };

	for (int i = 0; i <= index; i++)
	{
		gotoXY(monster1_attack[i].x--, monster1_attack[i].y);
		printf("%s\n", monster1_attack[i].attack);
	}

	Sleep(100);
	system("cls");
}