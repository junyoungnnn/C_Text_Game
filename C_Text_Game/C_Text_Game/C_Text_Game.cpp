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
#define Player_y_limit 7

#define MONSTER1_Y_LIMIT 20
#define MONSTER2_Y_LIMIT 16

#pragma region 구조체

struct Player {
	int x;
	int y;
	const char* shape;
};

struct Monster {
	int x;
	int y;
	const char* shape;
};

struct Player_attack
{
	int x;
	int y;
	const char* attack;
};

struct Monster_attack
{
	int x;
	int y;
	const char* attack;
};

struct Interface {
	float time;
	int hp;
	int score;
	int level;
};

#pragma endregion


int Random()
{
	int seed = rand() % 3 - 1; // -1, 0, +1 반환

	return seed;
}

// 맵생성
char map[WIDTH][HEIGHT];

void CreateMap(struct Interface player_interface)
{
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\ttime : %.1f\t\thp : %d\t\t\tscore : %d\t\tlevel : %d\t\t■\n", player_interface.time, player_interface.hp, player_interface.score, player_interface.level);
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■\t\t\t\t\t\t\t\t\t\t\t\t\t\t■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	for (int i = 8;i < HEIGHT - 1; i++)
	{
		printf("\n");
	}
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
			if (player->x <Player_x_limit)
			{
				player->x += 2;
			}
			break;
		case DOWN:
			if (player->y <HEIGHT - 3)
			{
				player->y++;
			}
			break;
		}
	}
}
#pragma endregion

// 투사체에 맞으면 체력 감소 함수
/*
void damage()
{
	if(player.x == )
}
*/


int main()
{
	srand(time(NULL));

	struct Player player = { 6,18,"★"};
	struct Player_attack player_attack[5] = { {player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"} };
	struct Interface player_interface = { 0,5,0,1 };
	struct Monster monster[2] = { {76,12,"♣"}, { 76,24,"♣"} };
	struct Monster_attack monster1_attack[6] = { {monster[0].x, monster[0].y,"☎"},{monster[0].x, monster[0].y,"☎"},{monster[0].x, monster[0].y,"☎"},{monster[0].x, monster[0].y,"☎"},{monster[0].x, monster[0].y,"☎"},{monster[0].x, monster[0].y,"☎"}};
	struct Monster_attack monster2_attack[6] = { {monster[1].x, monster[1].y,"☎"},{monster[1].x, monster[1].y,"☎"},{monster[1].x, monster[1].y,"☎"},{monster[1].x, monster[1].y,"☎"},{monster[1].x, monster[1].y,"☎"},{monster[1].x, monster[1].y,"☎"}};

	while (1)
	{
		CreateMap(player_interface);

		//printf("\t\ttime: %.1f\thp : %d\t\tscore : %d\tlevel : %d", player_interface.time, player_interface.hp, player_interface.score, player_interface.level);
		player_interface.time += 0.1;

#pragma region monster의 움직임

		if (monster[0].y >= Player_y_limit || monster[0].y <= MONSTER1_Y_LIMIT)
		{
			monster[0].y += Random();

			gotoXY(monster[0].x, monster[0].y);
			printf("%s", monster[0].shape);
		}

		if (monster[1].y >= MONSTER2_Y_LIMIT && monster[1].y < HEIGHT-3)
		{
			monster[1].y += Random();

			gotoXY(monster[1].x, monster[1].y);
			printf("%s", monster[1].shape);
		}

		// 벽에 부딪히면 다시 움직이게함
		if (monster[0].y == Player_y_limit)
		{
			monster[0].y++;
		}
		if (monster[0].y == MONSTER1_Y_LIMIT)
		{
			monster[0].y--;
		}
		if (monster[1].y == MONSTER2_Y_LIMIT)
		{
			monster[1].y++;
		}
		if (monster[1].y == HEIGHT-3)
		{
			monster[1].y--;
		}

#pragma endregion


		// 플레이어 투사체가 끝에 도달하면 삭제
		for (int i = 0; i < 5; i++)
		{
			if (player_attack[i].x < 0)
			{
				player_attack[i].x = player.x;
				player_attack[i].y = player.y;
			}
		}
		// 적 투사체가 끝에 도달하면 삭제
		for (int i = 0; i < 6; i++)
		{
			if (monster1_attack[i].x < 0)
			{
				monster1_attack[i].x = monster[0].x;
				monster1_attack[i].y = monster[0].y;
			}
			if (monster2_attack[i].x < 0)
			{
				monster2_attack[i].x = monster[1].x;
				monster2_attack[i].y = monster[1].y;
			}
		}

		// 투사체에 맞으면 체력감소 of die
		for (int i = 0; i < 6; i++)
		{
			if (player.x == monster1_attack[i].x && player.y == monster1_attack[i].y || player.x == monster2_attack[i].x && player.y == monster2_attack[i].y)
			{
				player_interface.hp--;
				if (player_interface.hp < 0)
				{
					return 0;
				}
			}
		}

		int attack_delay1 = 0;
		int attack_delay2 = 0;
		if (attack_delay1 <= 0)
		{
			attack_delay1 = Random() % 4 + 2;
			
		}
		if (attack_delay2 <= 0)
		{
			attack_delay2 = Random() % 4 + 2;
		}
		// 여기서부터 시작int attack_time1 = 0;
		// attack_time1 += 0.1;
		//if (attack_delay1 < attack_time1)
		{

		}

		KeyBoard(&player);
		gotoXY(player.x, player.y);
		printf("%s", player.shape);
		gotoXY(player_attack[0].x++, player_attack[0].y);
		printf("%s", player_attack[0].attack);
		gotoXY(player_attack[1].x++, player_attack[1].y);
		printf("%s", player_attack[1].attack);
		gotoXY(player_attack[2].x++, player_attack[2].y);
		printf("%s", player_attack[2].attack);
		gotoXY(player_attack[3].x++, player_attack[3].y);
		printf("%s", player_attack[3].attack);
		gotoXY(player_attack[4].x++, player_attack[4].y);
		printf("%s", player_attack[4].attack);


		gotoXY(monster1_attack[0].x--, monster1_attack[0].y);
		printf("%s", monster1_attack[0].attack);

		gotoXY(monster2_attack[1].x--, monster2_attack[1].y);
		 printf("%s", monster2_attack[1].attack);
		
		Sleep(100);
		system("cls");

	}

	return 0;
}

