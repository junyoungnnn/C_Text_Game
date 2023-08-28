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
void gotoXY(int x, int y);
void KeyBoard(Player* player);

struct Interface {
	float time;
	int hp;
	int score;
};

struct Player {
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
	printf("����������������������������������������������������������\n");
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("��\t\ttime : %.1f\t\thp : %d\t\t\tscore : %d\t\t\t\t\t��\n", player_interface.time, player_interface.hp, player_interface.score);
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("����������������������������������������������������������\n");
	for (int i = 8; i < HEIGHT - 1; i++)
	{
		printf("\n");
	}
	printf("����������������������������������������������������������\n");
}

int seed;

int Random()
{
	seed = rand() % 21 + 8;
	return seed;
}

void Shoot(Bullet * bullet)
{
	for (int i = bullet->x; i < WIDTH; i++)
	{
		gotoXY(i++, bullet->y);
		printf("%s", bullet->shape);
	}
}



int main()
{
	srand(time(NULL));

	struct Player player = { 6,18,"��" };
	struct Interface player_interface = { 0,5,0};
	struct Enemy enemy = { 100, seed, "��" };
	struct Bullet bullet[10] = { {player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."} };

	while (1)
	{
		CreateMap(player_interface);

		KeyBoard(&player);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		if (enemy.x < 0 || enemy.y < 8)
		{
			enemy.x = WIDTH;
			enemy.y = Random();
		}
		if (player.x == enemy.x && player.y == enemy.y)
		{
			player_interface.hp--;
			if (player_interface.hp < 0)
			{
				return 0;
			}
		}

		gotoXY(enemy.x--, enemy.y);
		printf("%s", enemy.shape);

		Sleep(100);
		system("cls");
	}

	return 0;
}

#pragma region �̵�

// ��ǥ �̵� �Լ�
void gotoXY(int x, int y)
{
	// x, y ��ǥ ����
	COORD position = { x,y };

	// Ŀ�� �̵�
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
			Shoot(Bullet bullet);
			break;
		}
	}
}
#pragma endregion