#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 116
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

void gotoXY(int, int);
void KeyBoard(Player*, Bullet*);

void CreateMap(struct Interface* player_interface)
{
	printf("����������������������������������������������������������\n");
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t\t��\n");
	printf("��\t\ttime : %.1f\t\thp : %d\t\t\tscore : %d\t\t\t\t\t��\n", player_interface->time, player_interface->hp, player_interface->score);
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
	seed = rand() % 20 + 8;
	return seed;
}

void Shoot(Player* player, Bullet * bullet)
{
	for (int i = player->x; i < WIDTH; i++)
	{
		gotoXY(i++, player->y);
		printf("%s", bullet->shape);
		gotoXY(i--, player->y);
		printf(" ");
	}
}

void Create_enemy(struct Enemy* enemy)
{
	//Sleep(100);
	if (enemy->x < 0 || enemy->y < 8)
	{
		enemy->x = WIDTH;
		enemy->y = Random();
	}
	
	gotoXY(enemy->x--, enemy->y);
	printf("%s", enemy->shape);
}
void Collision(struct Interface* player_interface, struct Player* player, struct Enemy* enemy)
{
	for (int i = 0; i < 5; i++)
	{
		if (player->x == enemy[i].x && player->y == enemy[i].y)
		{
			player_interface->hp--;
			if (player_interface->hp <= 0)
			{
				player_interface->hp--;
				exit(0);
			}
		}
	}
}



int main()
{
	srand(time(NULL));

	Player player = { 6,18,"��" };
	Interface player_interface = { 0,5,0 };
	Enemy enemy[5] = { {100, seed, "��"},{100, seed, "��"},{100, seed, "��"},{100, seed, "��"},{100, seed, "��"} };
	Bullet bullet[10] = { {player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."},{player.x, player.y, "."} };

	while (1)
	{
		CreateMap(&player_interface);
		//player_interface.time += 0.1;

		KeyBoard(&player, bullet);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		Create_enemy(&enemy[0]);
		Create_enemy(&enemy[1]);
		Create_enemy(&enemy[2]);
		Create_enemy(&enemy[3]);
		Create_enemy(&enemy[4]);
		Collision(&player_interface, &player, enemy);
		
		
		Sleep(10);
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

void KeyBoard(Player* player, Bullet* bullet)
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
			Shoot(player, bullet);
			break;
		}
	}
}
#pragma endregion
