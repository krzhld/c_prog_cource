#pragma once

#define BUTTONWIDTH 300
#define BUTTONHEIGHT 150

enum
{
	STARTGAME = 0,
	EXIT
} MenuButtons;

enum {
	WAITING = 10,
	LAUNCHED
} MenuStatuses;

typedef struct {
	RECT pos;
	WCHAR* label;
} button_t;

typedef struct {
	COLORREF butColor;
	COLORREF backColor;
	button_t buttons[2];
	int curButton;
	int status; // is it clicked startgame_b or exit_b or waiting?
} menu_t;

menu_t* RealizeStartMenu(void);

void ChangeCursor(menu_t* hMenu);

void DrawFrame(HDC hdc, RECT button);

void DrawMenu(HDC hdc, menu_t menu);

void FreeMenu(menu_t* hMenu);