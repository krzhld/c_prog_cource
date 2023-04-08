#include "framework.h"
#include "menu.h"
#include "ball.h"
#include "racket.h"
#include "bricks.h"
#include "interactions.h"
#include "level.h"

level_t* InitNewLevel(level_t* prevLevel)
{
	if (prevLevel == NULL)
	{
		level_t* newLevel = (level_t*)malloc(sizeof(level_t));
		if (newLevel == NULL)
		{
			PostQuitMessage(5);
			return newLevel;
		}
		newLevel->ball = InitNewBall(NULL);
		newLevel->bricks = InitBricks(NULL);
		newLevel->racket = InitNewRacket(NULL);
		newLevel->curLvl = 1;
		newLevel->lifes = 3;
		newLevel->score = 0;
		return newLevel;
	}
	else
	{
		prevLevel->ball = InitNewBall(prevLevel->ball);
		prevLevel->bricks = InitBricks(prevLevel->bricks);
		prevLevel->racket = InitNewRacket(prevLevel->racket);
		prevLevel->curLvl = prevLevel->curLvl + 1;
		prevLevel->lifes = prevLevel->lifes;
		prevLevel->score = prevLevel->score;
		return prevLevel;
	}
}

void FreeLevel(level_t* hLevel)
{
	if (hLevel == NULL)
		return;

	int n = BRICKSQUANTITY;
	while (n--)
		free(hLevel->bricks[n]);
	free(hLevel->bricks);
	free(hLevel->ball);
	free(hLevel->racket);
	free(hLevel);
}

BOOL IsItFreeField(level_t hLevel)
{
	for (int i = 0; i < BRICKSQUANTITY; ++i)
		if (hLevel.bricks[i]->status == ACTIVE)
			return FALSE;

	return TRUE;
}

void RecoveryBallAndRacket(level_t* hLevel)
{
	hLevel->racket = InitNewRacket(hLevel->racket);

	hLevel->ball = InitNewBall(hLevel->ball);

	--hLevel->lifes;
}

void GettingBonus(level_t* hLevel, brick_t* bonusBrick)
{
	switch (bonusBrick->bonus.type)
	{
	case LIFE:
		++hLevel->lifes;
		break;
	case SHORTRACKET:
		hLevel->racket->size = SHORTSIZE;
		break;
	case LONGRACKET:
		hLevel->racket->size = LONGSIZE;
		break;
	}
	bonusBrick->status = INVISIBLE;
}

void MoveObjects(level_t* hLevel)
{
	MoveBall(hLevel->ball);
	MoveBonuses(hLevel->bricks);
}

void ObjectsActions(level_t* hLevel)
{
	if (IsItFreeField(*hLevel))
	{
		hLevel = InitNewLevel(hLevel);
		return hLevel;
	}

	if (IsBallOutScreen(*hLevel->ball) && (hLevel->lifes > 0))
		RecoveryBallAndRacket(hLevel);

	if (IsBallOutScreen(*hLevel->ball) && (hLevel->lifes == 0))
		hLevel->lifes = -1;

	ReflectionWithWall(hLevel->ball, IsItTouchWithWall(*hLevel->ball));

	int index = IsItTouchWithBricks(hLevel->bricks, *hLevel->ball);
	if (index != -1)
	{
		ReflectionWithBrick(hLevel->bricks[index], hLevel->ball);
		hLevel->score += 100;
		if (hLevel->score == 1000)
		{
			hLevel->score = 0;
			++hLevel->lifes;
		}
	}	

	index = IsItTouchRacketAndBonus(hLevel->bricks, *hLevel->racket);
	if (index != -1)
		GettingBonus(hLevel, hLevel->bricks[index]);
	
	if (IsItTouchWithRacket(*hLevel->racket, *hLevel->ball))
		ReflectionWithRacket(*hLevel->racket, hLevel->ball);

	MoveObjects(hLevel);
}

void GameClose(HWND hWnd, menu_t* hMenu, level_t* hLevel, UINT_PTR timerPtr)
{
	KillTimer(hWnd, timerPtr);
	DestroyWindow(hWnd);
	FreeMenu(hMenu);
	FreeLevel(hLevel);
	PostQuitMessage(0);
}

button_t** ProgressBarButtons(level_t hLevel, button_t** prevBarButtons)
{
	button_t** buttons;
	if (prevBarButtons == NULL)
	{
		buttons = (button_t**)malloc(3 * sizeof(button_t*));
		if (buttons == NULL)
		{
			PostQuitMessage(6);
			return buttons;
		}
		for (int i = 0; i < 3; ++i)
		{
			buttons[i] = (button_t*)malloc(sizeof(button_t));
			if (buttons[i] == NULL)
				return NULL;
			buttons[i]->label = calloc(32, sizeof(WCHAR));
			if (buttons[i]->label == NULL)
				return NULL;
		}
	}
	else
	{
		buttons = prevBarButtons;
	}
	
	WCHAR buffer[8];

	wcscpy_s(buttons[SCORE]->label, wcslen(L"SCORE\n\n") + 1, L"SCORE\n\n");
	_itow_s(hLevel.score, buffer, 8, 10);
	wcscat_s(buttons[SCORE]->label, 32, buffer);
	wmemset(buffer, ' ', 8);
	buttons[SCORE]->pos.bottom = 500;
	buttons[SCORE]->pos.left = WINDOWWIDTH - BARWIDTH;
	buttons[SCORE]->pos.right = WINDOWWIDTH - 10;
	buttons[SCORE]->pos.top = 300;

	wcscpy_s(buttons[LIFES]->label, wcslen(L"LIFES\n\n") + 1, L"LIFES\n\n");
	_itow_s(hLevel.lifes, buffer, 8, 10);
	wcscat_s(buttons[LIFES]->label, 32, buffer);
	wmemset(buffer, ' ', 8);
	buttons[LIFES]->pos.bottom = 200;
	buttons[LIFES]->pos.left = WINDOWWIDTH - BARWIDTH;
	buttons[LIFES]->pos.right = WINDOWWIDTH - 10;
	buttons[LIFES]->pos.top = 0;

	wcscpy_s(buttons[LEVEL]->label, wcslen(L"LEVEL\n\n") + 1, L"LEVEL\n\n");
	_itow_s(hLevel.curLvl, buffer, 8, 10);
	wcscat_s(buttons[LEVEL]->label, 32, buffer);
	wmemset(buffer, ' ', 8);
	buttons[LEVEL]->pos.bottom = 800;
	buttons[LEVEL]->pos.left = WINDOWWIDTH - BARWIDTH;
	buttons[LEVEL]->pos.right = WINDOWWIDTH - 10;
	buttons[LEVEL]->pos.top = 600;

	return buttons;
}

void DrawProgressBar(HDC hdc, button_t** hButtons)
{
	HPEN hPen = CreatePen(PS_SOLID, 3, WHITE);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, WINDOWWIDTH - BARWIDTH + 2, 0, NULL);
	LineTo(hdc, WINDOWWIDTH - BARWIDTH + 2, WINDOWHEIGHT);
	DeleteObject(hPen);

	HFONT hFont = CreateFontA(30, 20, 0, 0, 70, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, ("Monotype Corsiva"));
	SelectObject(hdc, hFont);

	SetTextColor(hdc, WHITE);
	SetBkColor(hdc, BLACK);
	DrawTextW(hdc, hButtons[SCORE]->label, -1, &hButtons[SCORE]->pos, DT_CENTER);
	DrawTextW(hdc, hButtons[LEVEL]->label, -1, &hButtons[LEVEL]->pos, DT_CENTER);
	DrawTextW(hdc, hButtons[LIFES]->label, -1, &hButtons[LIFES]->pos, DT_CENTER);

}

void DrawGame(HDC hdc, level_t hLevel, button_t** hPrevBarButtons)
{
	button_t** hBarButtons = ProgressBarButtons(hLevel, hPrevBarButtons);
	DrawProgressBar(hdc, hBarButtons);
	DrawBricks(hdc, hLevel.bricks);
	DrawBonuses(hdc, hLevel.bricks);
	DrawRacket(hdc, *hLevel.racket);
	DrawBall(hdc, *hLevel.ball);
}

void DrawGameOver(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, BLACK);
	SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(BLACK);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT);

	button_t button;
	button.label = malloc(16 * sizeof(WCHAR));
	if (button.label == NULL)
		return;
	wcscpy_s(button.label, wcslen(L"GAME OVER !") + 1, L"GAME OVER !");
	button.pos.top = 300;
	button.pos.left = 200;
	button.pos.bottom = 700;
	button.pos.right = 800; 
	HFONT hFont = CreateFontA(30, 20, 0, 0, 70, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, ("Monotype Corsiva"));
	SelectObject(hdc, hFont);

	SetTextColor(hdc, WHITE);
	SetBkColor(hdc, BLACK);

	DrawTextW(hdc, button.label, -1, &button.pos, DT_CENTER);
	DeleteObject(hBrush);
	DeleteObject(hFont);
	DeleteObject(hPen);
}