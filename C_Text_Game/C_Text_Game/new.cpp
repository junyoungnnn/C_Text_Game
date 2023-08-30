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

bool bullet_check[10] = { false, false, false, false, false, false, false, false, false, false };

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

int bullet_index = 0;

void Shoot(Player* player, Bullet * bullet, bool* bullet_check)
{
	printf("**bullet_index: %d**: %d", bullet_index, bullet_check[bullet_index]);
	//for (int i = player->x; i < i+1; i++)
	//{
	//	//Sleep(25);
	//	//gotoXY(i - 1, player->y);
	//	//printf("  ");
	//	//gotoXY(i + 2,player->y);
	//
	//}
	if (bullet_index == 9)
	{
		bullet_index = 0;
	}
	bullet_index++;
	bullet_check[bullet_index] = true;
	
	
}

void Bullet_Move(Player* player, Bullet* bullet, bool* bullet_check)
{
	//bullet[bullet_index].x = player->x;
	if (bullet_check[bullet_index] == true)
	{
		for (int i = 0; i < 6; i++)
		{
		gotoXY(bullet[bullet_index].x++, player->y);
		
			printf("%s", bullet[bullet_index].shape);
		}
		if (bullet[bullet_index].x == WIDTH)
		{
			bullet_check[bullet_index] == false;
			bullet[bullet_index].x == -1;
			bullet[bullet_index].y == 40;
		}
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

		Bullet_Move(&player, bullet, bullet_check);



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
			Shoot(player, bullet, bullet_check);
			break;
		}
	}
}
#pragma endregion
