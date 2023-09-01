// 총알 한개로 변경 총알 구조체 배열-> 일반
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
	int x, y;
	float time;
	const char* hp;
	int score;
};

struct Player
{
	int x, y;
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

struct Item
{
	int x;
	int y;
	const char* shape;
};

void gotoXY(int, int);
void KeyBoard(Player*, Bullet*);

// 맵 생성
/*
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
*/

// 적 y축 렌덤 셍성
int seed;
int Random()
{
	seed = rand() % 20 + 8;
	return seed;
}

// 총알 발사 true
int bullet_Y;
void Shoot(Player* player, Bullet* bullet, bool* bullet_check)
{
	//bullet[bullet_index].x = player->x;
	
	*bullet_check = true;
	bullet_Y = player->y;

}

// 총알 이동 함수
void Bullet_Move(Player* player, Bullet* bullet, bool* bullet_check)
{

	if (*bullet_check == true)
	{
			gotoXY(bullet->x+=2, bullet_Y);

			//printf("%s", bullet->shape);

		}
		if (bullet->x == WIDTH)
		{
			*bullet_check = false;
			
		}
}

// 총알 위치를 플레이어에게 맞추는 함수
void Bullet_Position(Player* player, Bullet* bullet, bool* bullet_check)
{
	if (*bullet_check == false)
	{
		bullet->x = player->x ;
		bullet->y = player->y;
	}
}	

// 적 생성 플래그, 벽에 충돌화면 위치 초기화
void Create_enemy(struct Enemy* enemy, bool* flag)
{
	if (*flag == true)
	{
		gotoXY(enemy->x -= 1, enemy->y);
		//printf("%s", enemy->shape);
		if (enemy->x < 0 || enemy->y < 8)
		{
			*flag = false;
		}
	}
}

// 적 위치 초기화
void Enemy_Reset(struct Enemy* enemy, bool* flag)
{
	if (*flag == false)
	{
		enemy->x = WIDTH;
		enemy->y = Random();
	}

}

// 적과 부딪치면 데미지
void Collision(struct Interface* player_interface, struct Player* player, struct Enemy* enemy)
{
	for (int i = 0; i < 5; i++)
	{
		if (player->x == enemy[i].x && player->y == enemy[i].y)
		{
			if (player_interface->hp == "♥♥♥♥♥") player_interface->hp = "♥♥♥♥";
			else if (player_interface->hp == "♥♥♥♥") player_interface->hp = "♥♥♥";
			else if (player_interface->hp == "♥♥♥") player_interface->hp = "♥♥";
			else if (player_interface->hp == "♥♥") player_interface->hp = "♥";
			else if (player_interface->hp == "♥")
			{
				player_interface->hp = " ";
				exit(0);
			}
		}
	}
}


// 총알에 맞은 적 파괴
void Distory(Player* player, Bullet* bullet, Enemy* enemy, bool* flag, Interface* player_interface, bool* bullet_check)
{

	if (*bullet_check != false && (bullet->x == enemy->x || bullet->x == enemy->x-1) && bullet->y == enemy->y)
	{
		player_interface->score += 100;
		*flag = false;
		*bullet_check = false;
		Bullet_Position(player, bullet, bullet_check);
	}
}

// 적 생성 시작 플래그
void Start_flag(bool* flag)
{
	*flag = true;
}

// 아이템으로 회복
void Recovery(Player* player, Item* item, Interface * player_interface, bool* item_flag)
{
	if (*item_flag == false && player_interface->score != 0 && player_interface->score % 200 == 0)
	{
		*item_flag = true;
	}
	if (*item_flag == true)
	{
		gotoXY(item->x--, item->y);
	
		if (item->x < 0 || item->y < 8)
		{
			*item_flag = false;
		}
	}
	if (*item_flag == false)
	{
		item->x = WIDTH;
		item->y = Random();
	}
	if (player->x == item->x && player->y == item->y)
	{
		*item_flag = false;
		player_interface->score += 100;
		if (player_interface->hp == "♥♥♥♥") player_interface->hp = "♥♥♥♥♥";
		else if (player_interface->hp == "♥♥♥") player_interface->hp = "♥♥♥♥";
		else if (player_interface->hp == "♥♥") player_interface->hp = "♥♥♥";
		else if (player_interface->hp == "♥") player_interface->hp = "♥♥";
	}
}



int main()
{
	Init();
	srand(time(NULL));
	bool flag[5] = { false, false, false, false, false };
	bool item_flag = false;

	Player player = { 6,18," ↔" };
	Interface player_interface = { 0, 0, 0, "♥♥♥♥♥", 0};
	Enemy enemy[5] = { {WIDTH, 0, "  "},{WIDTH, Random(), "★1"},{WIDTH, Random(), "★2"},{WIDTH, Random(), "★3"},{WIDTH, Random(), "★4"} };
	//Bullet bullet[10] = { {player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"} };
	Bullet bullet = { player.x, player.y, "*→" };
	Item item = { WIDTH, Random(), "♥" };

	while (1)
	{


		//CreateMap(&player_interface);
		//player_interface.time += 0.1;

		Recovery(&player, &item, &player_interface, &item_flag);
		ShowBuffer(item.x, item.y, item.shape);

		KeyBoard(&player, &bullet);
		gotoXY(player.x, player.y);
		//printf("%s", player.shape);

		Bullet_Move(&player, &bullet, &bullet_check);
		Bullet_Position(&player, &bullet, &bullet_check);


		Start_flag(&flag[0]);
		Create_enemy(&enemy[0], &flag[0]);
		Enemy_Reset(&enemy[0], &flag[0]);

		if (enemy[0].x == 106) 
		{
			Start_flag(&flag[1]);
		}
		Create_enemy(&enemy[1], &flag[1]);
		Distory(&player, &bullet, &enemy[1], &flag[1], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[1], &flag[1]);

		if (enemy[0].x == 77)
		{
			Start_flag(&flag[2]);
		}
		Create_enemy(&enemy[2], &flag[2]);
		Distory(&player, &bullet, &enemy[2], &flag[2], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[2], &flag[2]);

		if (enemy[0].x == 48)
		{
			Start_flag(&flag[3]);
		}
		Create_enemy(&enemy[3], &flag[3]);
		Distory(&player, &bullet, &enemy[3], &flag[3], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[3], &flag[3]);

		if (enemy[0].x == 19)
		{
			Start_flag(&flag[4]);
		}
		Create_enemy(&enemy[4], &flag[4]);
		Distory(&player, &bullet, &enemy[4], &flag[4], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[4], &flag[4]);

		Collision(&player_interface, &player, enemy);

		Sleep(50);
		system("cls");

		ShowBuffer(player.x, player.y, player.shape);
		//ShowBuffer(enemy[0].x, enemy[0].y, enemy[0].shape);
		ShowBuffer(enemy[1].x, enemy[1].y, enemy[1].shape);
		ShowBuffer(enemy[2].x, enemy[2].y, enemy[2].shape);
		ShowBuffer(enemy[3].x, enemy[3].y, enemy[3].shape);
		ShowBuffer(enemy[4].x, enemy[4].y, enemy[4].shape);
		ShowBuffer(bullet.x, bullet.y, bullet.shape);

		char score[10];
		sprintf(score, "%d", player_interface.score);
		ShowBuffer(player_interface.x, player_interface.y, player_interface.hp);
		ShowBuffer(player_interface.x + 50, player_interface.y, score);

		// 2. 버퍼교체
		Flipping();

		Clear();
	}
	// 4. 버퍼를 해제합니다.
	ReleaseScreen();
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
			Shoot(player, bullet, &bullet_check);
			break;
		}
	}
}
#pragma endregion
