#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#pragma region ���� ���۸�

	// HANDLE �ε����� �����ؼ� ���۸� ��ü��Ű�� ����
	int screenIndex = 0;
	
	// ������ ũ��
	int width = 116;
	int height = 30;
	
	// ���� ����
	HANDLE Screen[2];
	
	// [0] : Front Buffer
	// [1] : Back Buffer
	
	
	// ���۸� �ʱ�ȭ �ϴ� �Լ�
	void Init()
	{
		CONSOLE_CURSOR_INFO cursor;
	
		// ������ ���� ������, ���� ������
		COORD size = { width, height };
	
		// LEFT, TOP, RIGHT, BOTTOM
		SMALL_RECT rect = { 0,0,width - 1, height - 1 };
	
		// ȭ�� 2���� �����մϴ�.
		// FRONT BUFFER
		Screen[0] = CreateConsoleScreenBuffer
		(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
	
		SetConsoleScreenBufferSize(Screen[0], size);
	
		SetConsoleWindowInfo(Screen[0], TRUE, &rect);
	
		// BACK BUFFER
		Screen[1] = CreateConsoleScreenBuffer
		(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
	
		SetConsoleScreenBufferSize(Screen[1], size);
	
		SetConsoleWindowInfo(Screen[1], TRUE, &rect);
	
		// Ŀ���� Ȱ��ȭ ����
		// false : ����
		// true : ��
		cursor.bVisible = false;
	
		SetConsoleCursorInfo(Screen[0], &cursor);
		SetConsoleCursorInfo(Screen[1], &cursor);
	}
	
	// ���۸� ��ä�ϴ� �Լ�
	void Flipping()
	{
		// ���۴� �ϳ��� Ȱ��ȭ ��ų �� �ֽ��ϴ�.
		SetConsoleActiveScreenBuffer(Screen[screenIndex]);
	
		// true <- false
		screenIndex = !screenIndex;
	}
	
	// ���۸� �����
	// ��ü�� ���۸� �����ִ� �Լ�
	void Clear()
	{
		COORD coord = { 0,0 };
	
		DWORD dw;
	
		FillConsoleOutputCharacter
		(
			Screen[screenIndex],
			' ',
			width * height,
			coord,
			&dw
		);
	}
	
	// ���۸� �����ϴ� �Լ�
	void ReleaseScreen()
	{
		CloseHandle(Screen[0]);
		CloseHandle(Screen[1]);
	}
	
	// ���۸� �̿��ؼ� ����ϴ� �Լ�
	void ShowBuffer(int x, int y, const char* string)
	{
		COORD cursorPosition = { x,y };
	
		DWORD dw;
	
		SetConsoleCursorPosition(Screen[screenIndex], cursorPosition);
	
		WriteFile
		(
			Screen[screenIndex],
			string,
			strlen(string),
			&dw,
			NULL
		);
	}

#pragma endregion