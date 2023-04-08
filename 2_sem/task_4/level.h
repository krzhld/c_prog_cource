#pragma once

#define lol 282

enum {
	SCORE = 0,
	LIFES,
	LEVEL
} BarButtons;

typedef struct
{
	int curLvl;
	int score;
	int lifes;
	ball_t* ball;
	racket_t* racket;
	brick_t** bricks;
} level_t;

level_t* InitNewLevel(level_t* prevLevel);

void FreeLevel(level_t* hLevel);

BOOL IsItFreeField(level_t hLevel);

void RecoveryBallAndRacket(level_t* hLevel);

void GettingBonus(level_t* hLevel, brick_t* bonusBrick);

void MoveObjects(level_t* hLevel);

void ObjectsActions(level_t* hLevel);

void GameClose(HWND hWnd, menu_t* hMenu, level_t* hLevel, UINT_PTR timerPtr);

button_t** ProgressBarButtons(level_t hLevel, button_t** prevBarButtons);

void DrawProgressBar(HDC hdc, button_t** hButtons);

void DrawGame(HDC hdc, level_t hLevel, button_t** hPrevBarButtons);

void DrawGameOver(HDC hdc);