#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "doublebuffer.h"
#include "title.h"
#include "endtitle.h"

#define WIDTH 116
#define HEIGHT 24

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32

#define Player_x_limit 60
#define Player_y_limit 7

bool bullet_check = false;

struct Interface
{
	int x, y;
	float time;
	const char* hp_text;
	const char* hp;
	const char* score_text;
	int score;
};

struct Player
{
	int x, y;
	const char* shape;
};

struct Player_wings
{
	int leftwing_x, leftwing_y;
	int rightwing_x, rightwing_y;
	int backwing_x, backwing_y;
	const char* leftwing;
	const char* rightwing;
	const char* backwing;
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



// 적 y축 렌덤 셍성
int seed;
int Random()
{
	seed = rand() % 15 + 7;
	return seed;
}

// 총알 발사 true
int bullet_Y;
void Shoot(Player* player, Bullet* bullet, bool* bullet_check)
{
	*bullet_check = true;
	bullet_Y = player->y;
}

// 총알 이동 함수
void Bullet_Move(Player* player, Bullet* bullet, bool* bullet_check)
{

	if (*bullet_check == true)
	{
		gotoXY(bullet->x += 6, bullet_Y);
	}
	if (bullet->x == WIDTH || bullet->x == WIDTH + 1 || bullet->x == WIDTH + 2 || bullet->x == WIDTH + 3 || bullet->x == WIDTH + 4 || bullet->x == WIDTH + 5)
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

// 날개의 위치
void Wings_Position(Player* player, Player_wings* player_wings)
{
	player_wings->leftwing_x = player->x;
	player_wings->leftwing_y = player->y - 1;
	player_wings->rightwing_x = player->x;
	player_wings->rightwing_y = player->y + 1;
	player_wings->backwing_x = player->x - 1;
	player_wings->backwing_y = player->y;
}

// 적 생성 플래그, 벽에 충돌화면 위치 초기화
void Create_enemy(struct Enemy* enemy, bool* enemy_flag)
{
	if (*enemy_flag == true)
	{
		gotoXY(enemy->x -= 1, enemy->y);
		//printf("%s", enemy->shape);
		if (enemy->x < 0 || enemy->y < 7)
		{
			*enemy_flag = false;
		}
	}
}

// 적 위치 초기화
void Enemy_Reset(struct Enemy* enemy, bool* enemy_flag)
{
	if (*enemy_flag == false)
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
void Distory(Player* player, Bullet* bullet, Enemy* enemy, bool* enemy_flag, Interface* player_interface, bool* bullet_check)
{
	if (*bullet_check != false && (bullet->x == enemy->x || bullet->x == enemy->x+1 || bullet->x == enemy->x+2 || bullet->x == enemy->x + 3 || bullet->x == enemy->x + 4 || bullet->x == enemy->x + 5 || bullet->x == enemy->x + 6) && bullet->y == enemy->y)
	{
		player_interface->score += 100;
		*enemy_flag = false;
		*bullet_check = false;
		Bullet_Position(player, bullet, bullet_check);
	}
}

// 적 생성 시작 플래그
void Start_flag(bool* enemy_flag)
{
	*enemy_flag = true;
}

// 아이템으로 회복
int item_count = 0;
void Recovery(Player* player, Item* item, Interface * player_interface, bool* item_flag)
{
	if (*item_flag == false && player_interface->score != 0 && player_interface->score % 1000 == 0 && player_interface->score / 1000 != item_count)
	{
		*item_flag = true;
	}
	// 끝에 도달하면 플래그 false
	if (*item_flag == true)
	{
		gotoXY(item->x--, item->y);
	
		if (item->x < 0 || item->y < 7)
		{
			item_count++;
			*item_flag = false;
		}
	}
	// 아이템 위치 초기화
	if (*item_flag == false)
	{
		item->x = WIDTH;
		item->y = Random();
	}
	// 회복
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
	Title();
	Init();
	srand(time(NULL));

	bool enemy_flag[5] = { false, false, false, false, false };
	bool item_flag = false;

	Player player = { 6,18," →" };
	Player_wings player_wings = { player.x, player.y - 1, player.x, player.y + 1, player.x - 1, player.y, "▲", "▼", "▶" };
	Interface player_interface = { 0, 0, 0, "HP: ", "♥♥♥♥♥", "Score: ", 0};
	Enemy enemy[5] = { {WIDTH, 0, "  "},{WIDTH, 0, "★          "},{WIDTH, 0, "★          "},{WIDTH, 0, "★          "},{WIDTH, 0, "★          "} };
	Bullet bullet = { player.x, player.y, "*→" };
	Item item = { WIDTH, 0, "♥" };

	while (1)
	{
		// 플레이어 이동
		KeyBoard(&player, &bullet);
		gotoXY(player.x, player.y);

		// 회복 아이템
		Recovery(&player, &item, &player_interface, &item_flag);
		if (item_flag == true)
		{
			ShowBuffer(item.x, item.y, item.shape);
		}
		
		// 총알 이동
		Bullet_Move(&player, &bullet, &bullet_check);
		Bullet_Position(&player, &bullet, &bullet_check);

		// 적생성을 위한 플래그
		Start_flag(&enemy_flag[0]);
		Create_enemy(&enemy[0], &enemy_flag[0]);
		Enemy_Reset(&enemy[0], &enemy_flag[0]);

		// 적 생성
		if (enemy[0].x == 106) 
		{
			Start_flag(&enemy_flag[1]);
		}
		Create_enemy(&enemy[1], &enemy_flag[1]);
		Distory(&player, &bullet, &enemy[1], &enemy_flag[1], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[1], &enemy_flag[1]);

		if (enemy[0].x == 77)
		{
			Start_flag(&enemy_flag[2]);
		}
		Create_enemy(&enemy[2], &enemy_flag[2]);
		Distory(&player, &bullet, &enemy[2], &enemy_flag[2], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[2], &enemy_flag[2]);

		if (enemy[0].x == 48)
		{
			Start_flag(&enemy_flag[3]);
		}
		Create_enemy(&enemy[3], &enemy_flag[3]);
		Distory(&player, &bullet, &enemy[3], &enemy_flag[3], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[3], &enemy_flag[3]);

		if (enemy[0].x == 19)
		{
			Start_flag(&enemy_flag[4]);
		}
		Create_enemy(&enemy[4], &enemy_flag[4]);
		Distory(&player, &bullet, &enemy[4], &enemy_flag[4], &player_interface, &bullet_check);
		Enemy_Reset(&enemy[4], &enemy_flag[4]);

		// 충돌 판정
		Collision(&player_interface, &player, enemy);

		// 플레이어 
		ShowBuffer(player.x, player.y, player.shape);

		// 날개 
		Wings_Position(&player, &player_wings);
		ShowBuffer(player_wings.leftwing_x, player_wings.leftwing_y, player_wings.leftwing);
		ShowBuffer(player_wings.rightwing_x, player_wings.rightwing_y, player_wings.rightwing);
		ShowBuffer(player_wings.backwing_x, player_wings.backwing_y, player_wings.backwing);
	
		// 적
		if (enemy_flag[1] == true)
		{
			ShowBuffer(enemy[1].x, enemy[1].y, enemy[1].shape);
		}
		if (enemy_flag[2] == true)
		{
			ShowBuffer(enemy[2].x, enemy[2].y, enemy[2].shape);
		}
		if (enemy_flag[3] == true)
		{
			ShowBuffer(enemy[3].x, enemy[3].y, enemy[3].shape);
		}
		if (enemy_flag[4] == true)
		{
			ShowBuffer(enemy[4].x, enemy[4].y, enemy[4].shape);
		}
		// 총알 
		ShowBuffer(bullet.x, bullet.y, bullet.shape);

		// 인터페이스
		char score[10];
		sprintf(score, "%d", player_interface.score);
		ShowBuffer(player_interface.x + 30, player_interface.y, player_interface.hp_text);
		ShowBuffer(player_interface.x + 34, player_interface.y, player_interface.hp);
		ShowBuffer(player_interface.x + 60, player_interface.y, player_interface.score_text);
		ShowBuffer(player_interface.x + 68, player_interface.y, score);

		Sleep(25);
		//system("cls");

		// 버퍼교체
		Flipping();

		Clear();
	}
	// 버퍼를 해제
	ReleaseScreen();
	
	End_Title();

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
