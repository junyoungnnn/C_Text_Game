#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BULLET_SIZE 5

struct Bullet
{
    int x;
    int y;
    const char* shape;
};

void gotoXY(int x, int y) {
    //x, y 좌표 설정
    COORD pos = { x,y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


static int index = 0;

void Launch(Bullet* enemy)
{
    index++;

    if (index % BULLET_SIZE == 0)
    {
        index = 0;
    }
}

int main()
{
    srand(time(NULL));

    Bullet enemy[BULLET_SIZE];

    int delay = 0;

    for (int i = 0; i < BULLET_SIZE; i++)
    {
        enemy[i].x = 30;
        enemy[i].y = 10;
        enemy[i].shape = "←";
    }

    while (1)
    {
        delay += 1;
        for (int i = 0; i <= index; i++)
        {
            gotoXY(enemy[i].x--, enemy[i].y);
            printf("%s\n", enemy[i].shape);
        }

        if (delay % 20 == 0)
        {
            Launch(enemy);
        }

        Sleep(100);
        system("cls");

    }
}