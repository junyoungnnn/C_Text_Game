// �Ѿ� �Ѱ��� ���� �Ѿ� ����ü �迭-> �Ϲ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "doublebuffer.h"

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

bool bullet_check = false;

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

// �� ����
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

// �� y�� ���� �ļ�
int seed;
int Random()
{
	seed = rand() % 20 + 8;
	return seed;
}

// �Ѿ� �߻� true
int bullet_Y;
void Shoot(Player* player, Bullet* bullet, bool* bullet_check)
{
	//bullet[bullet_index].x = player->x;
	printf("***: %d", *bullet_check);
	
	*bullet_check = true;
	bullet_Y = player->y;

}

// �Ѿ� �̵� �Լ�
void Bullet_Move(Player* player, Bullet* bullet, bool* bullet_check)
{

	if (*bullet_check == true)
	{
			gotoXY(bullet->x++, bullet_Y);

			//printf("%s", bullet->shape);

		}
		if (bullet->x == WIDTH)
		{
			*bullet_check = false;
			
		}
}

// �Ѿ� ��ġ�� �÷��̾�� ���ߴ� �Լ�
void Bullet_Position(Player* player, Bullet* bullet, bool* bullet_check)
{
	if (*bullet_check == false)
	{
		bullet->x = player->x;
		bullet->y = player->y;
	}
}

// �� ���� �÷���, ���� �浹ȭ�� ��ġ �ʱ�ȭ
void Create_enemy(struct Enemy* enemy, bool* flag)
{
	if (*flag == true)
	{

		gotoXY(enemy->x--, enemy->y);
		//printf("%s", enemy->shape);
		if (enemy->x < 0 || enemy->y < 8)
		{
			*flag = false;
		}
	}
}

// ���� �ε�ġ�� ������
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

void Enemy_Reset(struct Enemy* enemy, bool* flag)
{
	if (*flag == false)
	{
		enemy->x = WIDTH;
		enemy->y = Random();
	}

}

// �Ѿ˿� ���� �� �ı�
void Distory(Bullet* bullet, Enemy* enemy, bool* flag)
{

	if (bullet->x == enemy->x && bullet->y == enemy->y)
	{
		*flag = false;
		//exit(0);
		
	}

}

// �� ���� ���� �÷���
void Start_flag(int* delay, bool* flag)
{
	*flag = true;
}



int main()
{
	Init();
	srand(time(NULL));
	int delay = 0;
	bool flag[5] = { false, false, false, false, false };

	Player player = { 6,18,"��" };
	Interface player_interface = { 0,5,0 };
	Enemy enemy[5] = { {WIDTH, Random(), "��"},{WIDTH, Random(), "��"},{WIDTH, Random(), "��"},{WIDTH, Random(), "��"},{WIDTH, Random(), "��"} };
	//Bullet bullet[10] = { {player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"},{player.x, player.y, "��"} };
	Bullet bullet = { player.x, player.y, "��" };
	while (1)
	{
		delay += 1;
		printf("%d", delay);

		CreateMap(&player_interface);
		//player_interface.time += 0.1;

		KeyBoard(&player, &bullet);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		Bullet_Move(&player, &bullet, &bullet_check);
		Bullet_Position(&player, &bullet, &bullet_check);




		Start_flag(&delay, &flag[0]);
		Create_enemy(&enemy[0], &flag[0]);
		Distory(&bullet, &enemy[0], &flag[0]);
		Enemy_Reset(&enemy[0], &flag[0]);

		if (enemy[0].x == 80) 
		{
			Start_flag(&delay, &flag[1]);
		}
		Create_enemy(&enemy[1], &flag[1]);
		Distory(&bullet, &enemy[1], &flag[1]);
		Enemy_Reset(&enemy[1], &flag[1]);

		if (enemy[1].x == 80)
		{
			Start_flag(&delay, &flag[2]);
		}
		Create_enemy(&enemy[2], &flag[2]);
		Distory(&bullet, &enemy[2], &flag[2]);
		Enemy_Reset(&enemy[2], &flag[2]);

		if (enemy[2].x == 80)
		{
			Start_flag(&delay, &flag[3]);
		}
		Create_enemy(&enemy[3], &flag[3]);
		Distory(&bullet, &enemy[3], &flag[3]);
		Enemy_Reset(&enemy[3], &flag[3]);

		if (enemy[3].x == 80)
		{
			Start_flag(&delay, &flag[4]);
		}
		Create_enemy(&enemy[4], &flag[4]);
		Distory(&bullet, &enemy[4], &flag[4]);
		Enemy_Reset(&enemy[4], &flag[4]);

		Collision(&player_interface, &player, enemy);

		Sleep(10);
		system("cls");
		ShowBuffer(player.x, player.y, player.shape);
		ShowBuffer(enemy[0].x, enemy[0].y, enemy[0].shape);
		ShowBuffer(enemy[1].x, enemy[1].y, enemy[1].shape);
		ShowBuffer(enemy[2].x, enemy[2].y, enemy[2].shape);
		ShowBuffer(enemy[3].x, enemy[3].y, enemy[3].shape);
		ShowBuffer(enemy[4].x, enemy[4].y, enemy[4].shape);
		ShowBuffer(bullet.x, bullet.y, bullet.shape);

		// 2. ���۱�ü
		Flipping();

		Clear();
	}
	// 4. ���۸� �����մϴ�.
	ReleaseScreen();
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
			Shoot(player, bullet, &bullet_check);
			break;
		}
	}
}
#pragma endregion
