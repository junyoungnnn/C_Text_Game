#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#pragma region 더블 버퍼링

	// HANDLE 인덱스에 접근해서 버퍼를 교체시키는 변수
	int screenIndex = 0;
	
	// 버퍼의 크기
	int width = 116;
	int height = 30;
	
	// 버퍼 생성
	HANDLE Screen[2];
	
	// [0] : Front Buffer
	// [1] : Back Buffer
	
	
	// 버퍼를 초기화 하는 함수
	void Init()
	{
		CONSOLE_CURSOR_INFO cursor;
	
		// 버퍼의 가로 사이즈, 세로 사이즈
		COORD size = { width, height };
	
		// LEFT, TOP, RIGHT, BOTTOM
		SMALL_RECT rect = { 0,0,width - 1, height - 1 };
	
		// 화면 2개를 생성합니다.
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
	
		// 커서의 활성화 여부
		// false : 거짓
		// true : 참
		cursor.bVisible = false;
	
		SetConsoleCursorInfo(Screen[0], &cursor);
		SetConsoleCursorInfo(Screen[1], &cursor);
	}
	
	// 버퍼를 교채하는 함수
	void Flipping()
	{
		// 버퍼는 하나만 활성화 시킬 수 있습니다.
		SetConsoleActiveScreenBuffer(Screen[screenIndex]);
	
		// true <- false
		screenIndex = !screenIndex;
	}
	
	// 버퍼를 지우다
	// 교체된 버퍼를 지워주는 함수
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
	
	// 버퍼를 해제하는 함수
	void ReleaseScreen()
	{
		CloseHandle(Screen[0]);
		CloseHandle(Screen[1]);
	}
	
	// 버퍼를 이용해서 출력하는 함수
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