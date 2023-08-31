// 총알 한개로 변경 총알 구조체 배열-> 일반
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

// 맵 생성
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

// 적 y축 렌덤 셍성
int seed;
int Random()
{
	seed = rand() % 20 + 8;
	return seed;
}

// 총알 발사 true
int bullet_index = 0;
void Shoot(Player* player, Bullet* bullet, bool* bullet_check)
{
	//bullet[bullet_index].x = player->x;
	printf("**bullet_index: %d**: %d", bullet_index, *bullet_check);
	
	*bullet_check = true;
	//int bullet_Y = player->y;

}

// 총알 이동 함수
void Bullet_Move(Player* player, Bullet* bullet, bool* bullet_check)
{

	if (*bullet_check == true)
	{

		
			gotoXY(bullet->x++, player->y);

			printf("     %s      ", bullet->shape);

		}
		if (bullet->x == WIDTH)
		{
			*bullet_check = false;
			bullet->x = -1;
			bullet->y = 40;
		}
	
}

// 적 생성 플래그, 벽에 충돌화면 위치 초기화
void Create_enemy(struct Enemy* enemy, bool* flag)
{
	if (*flag == true)
	{

		gotoXY(enemy->x--, enemy->y);
		printf("%s", enemy->shape);
		if (enemy->x < 0 || enemy->y < 8)
		{
			*flag = false;
			
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

// 적과 부딪치면 데미지
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

// 총알에 맞은 적 파괴
void Distory(Bullet* bullet, Enemy* enemy, bool* flag)
{

	if (bullet->x == enemy->x && bullet->y == enemy->y)
	{
		*flag = false;
		//Create_enemy(&enemy[i], &flag[i]);
		exit(0);
		
	}

}

// 삭제예정
void Start_flag(int* delay, bool* flag)
{
	*flag = true;
}



int main()
{
	srand(time(NULL));
	int delay = 0;
	bool flag[5] = { false, false, false, false, false };

	Player player = { 6,18,"↔" };
	Interface player_interface = { 0,5,0 };
	Enemy enemy[5] = { {100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"},{100, Random(), "★"} };
	//Bullet bullet[10] = { {player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"},{player.x, player.y, "→"} };
	Bullet bullet = { player.x, player.y, "→" };
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




		Start_flag(&delay, &flag[0]);
		Create_enemy(&enemy[0], &flag[0]);
		Distory(&bullet, &enemy[0], &flag[0]);
		Enemy_Reset(&enemy[0], &flag[0]);

		Start_flag(&delay, &flag[1]);
		Create_enemy(&enemy[1], &flag[1]);
		Distory(&bullet, &enemy[1], &flag[1]);
		Enemy_Reset(&enemy[1], &flag[1]);

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
			Shoot(player, bullet, &bullet_check);
			break;
		}
	}
}
#pragma endregion
