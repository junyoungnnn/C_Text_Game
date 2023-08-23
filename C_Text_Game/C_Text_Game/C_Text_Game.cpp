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
#define Player_y_limit 6

#define MONSTER1_Y_LIMIT 20
#define MONSTER2_Y_LIMIT 16


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

int seed1 = 0;
int seed2 = 0;

int Random(int seed)
{
	srand(time(NULL));
	seed = rand() % 3 - 1; // -1, 0, +1 반환

	return seed;
}

// 좌표 이동 함수
void gotoXY(int x, int y)
{
	// x, y 좌표 설정
	COORD position = { x,y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// 맵생성
char map[WIDTH][HEIGHT];



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
			if (player->y >= Player_y_limit)
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
			if (player->y <=HEIGHT)
			{
				player->y++;
			}
			break;
		}
	}
}

// 투사체에 맞으면 체력 감소 함수
/*
void damage()
{
	if(player.x == )
}
*/


int main()
{
	Player player = { 6,18,"★"};
	struct Player_attack player_attack[5] = { {player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"},{player.x, player.y, "◎"} };
	struct Interface player_interface = { 0,5,0,1 };
	struct Monster monster[2] = { {76,12,"♣"}, { 76,24,"♣"} };
	struct Monster_attack monster_attack[2] = { {monster[0].x, monster[0].y,"☎"}, { monster[1].x, monster[1].y,"☎" } };

	while (1)
	{
		printf("\n\n");
		printf("\t\ttime: %.1f\thp : %d\t\tscore : %d\tlevel : %d", player_interface.time, player_interface.hp, player_interface.score, player_interface.level);
		player_interface.time += 0.1;

		if (monster[0].y >= Player_y_limit || monster[0].y <= MONSTER1_Y_LIMIT)
		{
			monster[0].y += Random(seed1);
		}
		if (monster[1].y >= MONSTER2_Y_LIMIT || monster[1].y <= HEIGHT)
		{
			monster[1].y += Random(seed2);
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
		if (monster[1].y == HEIGHT)
		{
			monster[1].y--;
		}

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
		for (int i = 0; i < 2; i++)
		{
			if (monster_attack[i].x < 0)
			{
				monster_attack[i].x = monster[i].x;
				monster_attack[i].y = monster[i].y;
			}
		}

		// 투사체에 맞으면 체력감소 of die
		for (int i = 0; i < 2; i++)
		{
			if (player.x == monster_attack[i].x && player.y == monster_attack[i].y)
			{
				player_interface.hp--;
				if (player_interface.hp < 0)
				{
					return 0;
				}
			}
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

		gotoXY(monster[0].x, monster[0].y);
		printf("%s", monster[0].shape);
		gotoXY(monster_attack[0].x--, monster_attack[0].y);
		printf("%s", monster_attack[0].attack);

		gotoXY(monster[1].x, monster[1].y);
		printf("%s", monster[1].shape);
		gotoXY(monster_attack[1].x--, monster_attack[1].y);
		printf("%s", monster_attack[1].attack);
		
		Sleep(100);
		system("cls");

	}

	return 0;
}

