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
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\ttime : %.1f\t\thp : %d\t\t\tscore : %d\t\t\t\t\t■\n", player_interface->time, player_interface->hp, player_interface->score);
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
	seed = rand() % 20 + 8;
	return seed;
}

void Shoot(Player* player, Bullet * bullet)
{
	for (int i = player->x; i < WIDTH; i++)
	{
		gotoXY(i++, player->y);
		printf("%s", bullet->shape);
		Sleep(25);
		gotoXY(i - 1, player->y);
		printf("  ");
		gotoXY(i + 2,player->y);
		

	}
}

void Create_enemy(struct Enemy* enemy, bool* flag)
{
	if (*flag == true)
	{
		
	gotoXY(enemy->x--, enemy->y);
	printf("%s", enemy->shape);
		if (enemy->x < 0 || enemy->y < 8)
		{
			*flag = false;
			enemy->x = WIDTH;
			enemy->y = Random();
		}
	}
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

void Start_flag(int *delay, bool*flag)
{
	if (*delay % 10 == 0)
	{
		*flag = true;
		*delay = 0;
	}
}



int main()
{
	srand(time(NULL));
	int delay = 0;
	bool flag[5] = { false, false, false, false, false };
	

	Player player = { 6,18,"↔" };
	Interface player_interface = { 0,5,0 };
	Enemy enemy[5] = { {100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"}};
	Bullet bullet[10] = { {player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"} };

	while (1)
	{
		delay += 1;
		printf("%d", delay);
		
		CreateMap(&player_interface);
		//player_interface.time += 0.1;

		KeyBoard(&player, bullet);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		Start_flag(&delay, &flag[0]);
		Create_enemy(&enemy[0], &flag[0]);

		Start_flag(&delay, &flag[1]);
		Create_enemy(&enemy[1], &flag[1]);

		Create_enemy(&enemy[2], &flag[2]);
		Create_enemy(&enemy[3], &flag[3]);
		Create_enemy(&enemy[4], &flag[4]);
		Collision(&player_interface, &player, enemy);
		
		
		Sleep(10);
		system("cls");
	}

	return 0;
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
