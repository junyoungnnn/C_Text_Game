#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void Title()
{
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t      SHOOT GAME!\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t      �����Ϸ��� SPACE�� ��������\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t    #������ : ���ؿ�  ��\n");
	printf("��      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

	char key = 0;
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 32:
				break;
			}
			break;
		}
	}
}