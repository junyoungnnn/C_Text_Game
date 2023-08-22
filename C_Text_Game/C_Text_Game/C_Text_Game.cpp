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
#define Player_y_limit 6


struct Player {
	int x;
	int y;
	const char* shape;
	const char* attack;
};

struct Monster {
	int x;
	int y;
	const char* shape;
	const char* attack;
};

struct Interface {
	int time;
	int hp;
	int score;
	int level;
};

int seed1 = 0;
int seed2 = 0;

int Random(int seed)
{
	srand(time(NULL));
	seed = rand() % 3; // 0, 1, 2 반환

	seed--; // -1, 0, +1 반환
	return seed;
}

// 좌표 이동 함수
void gotoXY(int x, int y)
{
	// x, y 좌표 설정
	COORD position = { x,y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// 맵생성
char map[WIDTH][HEIGHT];

void KeyBoard(Player* player)
{
	char key = 0;

	if (_kbhit())
	{
		key = _getch();
		if (key == -32)
		{
			key = _getch();
		}
		switch (key)
		{
		case UP:
			if (player->y >= Player_y_limit)
			{
				player->y--;
			}
			break;
		case LEFT:
			if (player->x > 4)
			{
				player->x -= 2;
			}
			break;
		case RIGHT:
			if (player->x <Player_x_limit)
			{
				player->x += 2;
			}
			break;
		case DOWN:
			if (player->y <=HEIGHT)
			{
				player->y++;
			}
			break;
		}
	}
}

int main()
{
	Player player = { 6,18,"★","◎" };
	Monster monster1 = { 76,12,"♣","☎" };
	Monster monster2 = { 76,24,"♣","☎" };

	while (1)
	{
		if (monster1.y >= Player_x_limit && monster1.y <= HEIGHT)
		{
			monster1.y += Random(seed1);
		}
		if (monster2.y >= Player_x_limit && monster2.y <= HEIGHT)
		{
			monster2.y += Random(seed2);
		}

		KeyBoard(&player);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		gotoXY(monster1.x, monster1.y);
		printf("%s", monster1.shape);
		gotoXY(monster2.x, monster2.y);
		printf("%s", monster2.shape);
		
		Sleep(100);
		system("cls");

	}

	return 0;
}

