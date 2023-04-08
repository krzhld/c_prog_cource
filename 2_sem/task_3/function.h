#pragma once

#include "framework.h"
#include "Resource.h"
#include "targetver.h"

#define BUTTONSIZE 40
#define WINDOWSIZE 300

#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define CYAN RGB(0,255,255)
#define MAGENTA RGB(255,0,255)
#define YELLOW RGB(255,255,0)
#define WHITE RGB(255,255,255)

typedef struct {
	COLORREF color;
	COLORREF highlightColor;
	RECT position;
	WCHAR name[16];
	BOOL isSelected;
} button_t;

typedef struct {
	COLORREF color;
	RECT position;
} window_t;

typedef struct {
	button_t* buttons;
	int numberButtons;
	window_t* windows;
	int numberWindows;
	FILE* fp;
	BOOL isReturnDown;
	int numberOfCurButton;
} menu_t;

void DrawCross(HDC hdc, RECT rect);

void DrawFrame(HDC hdc, RECT rect);

void DefaultButton(button_t* hMenu);

void DefaultWindow(window_t* hMenu);

menu_t* SystemOpen();

int SystemClose(menu_t* hMenu);

int SystemInitialize(menu_t* hMenu, const WCHAR* menuFileName);

menu_t* SystemRelease(menu_t* hMenu);

void SystemUpdate(menu_t* hMenu, HDC hdc);