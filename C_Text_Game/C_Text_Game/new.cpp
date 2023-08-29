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
#define SPACE 32

#define Player_x_limit 60
#define Player_y_limit 7

#define MONSTER1_Y_LIMIT 20
#define MONSTER2_Y_LIMIT 16

#define BULLET_SIZE 10
void gotoXY(int, int);
//void KeyBoard(Player);

struct Interface 
{
	float time;
	int hp;
	int score;
};

struct Player 
{
	int x;
	int y;
	const char* shape;
};

struct Enemy
{
	int x, y;
	const char* shape;
};

struct Bullet
{
	int x;
	int y;
	const char* shape;
};

void CreateMap(struct Interface player_interface)
{
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\ttime : %.1f\t\thp : %d\t\t\tscore : %d\t\t\t\t\t■\n", player_interface.time, player_interface.hp, player_interface.score);
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	for (int i = 8; i < HEIGHT - 1; i++)
	{
		printf("\n");
	}
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

int seed;

int Random()
{
	seed = rand() % 21 + 8;
	return seed;
}

#pragma region 이동

// 좌표 이동 함수
void gotoXY(int x, int y)
{
	// x, y 좌표 설정
	COORD position = { x,y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

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
			if (player->y > Player_y_limit)
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
			if (player->x < Player_x_limit)
			{
				player->x += 2;
			}
			break;
		case DOWN:
			if (player->y < HEIGHT - 3)
			{
				player->y++;
			}
			break;
		case SPACE:
			//Shoot(Bullet bullet);
			break;
		}
	}
}
#pragma endregion

void Shoot(Bullet * bullet)
{
	for (int i = bullet->x; i < WIDTH; i++)
	{
		gotoXY(i++, bullet->y);
		printf("%s", bullet->shape);
	}
}

void Create_enemy(struct Enemy enemy)
{
	if (enemy.x < 0 || enemy.y < 8)
	{
		enemy.x = WIDTH;
		enemy.y = Random();
	}
	
	gotoXY(enemy.x--, enemy.y);
	printf("%s", enemy.shape);
}
void Collider(struct Interface player_interface, struct Player player, struct Enemy enemy)
{
	if (player.x == enemy.x && player.y == enemy.y)
	{
		player_interface.hp--;
		if (player_interface.hp < 0)
		{
			return;
		}
	}
}



int main()
{
	srand(time(NULL));

	struct Player player = { 6,18,"↔" };
	struct Interface player_interface = { 0,5,0};
	struct Enemy enemy[5] = { {100, seed, "★"},{100, seed, "★"},{100, seed, "★"},{100, seed, "★"},{100, seed, "★"} };
	struct Bullet bullet[10] = { {player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."} };

	while (1)
	{
		CreateMap(player_interface);

		KeyBoard(&player);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		Create_enemy(enemy[0]);
		Collider(player_interface, player, enemy[0]);
		

		Sleep(100);
		system("cls");
	}

	return 0;
}

