#include "framework.h"
#include "menu.h"

menu_t* RealizeStartMenu(void)
{
	menu_t* hMenu = (menu_t*)malloc(sizeof(menu_t));
	if (hMenu == NULL)
	{
		PostQuitMessage(1);
		return NULL;
	}
	hMenu->buttons[0].label = malloc(16 * sizeof(WCHAR));
	if (hMenu->buttons[0].label == NULL)
		return NULL;

	hMenu->buttons[1].label = malloc(16 * sizeof(WCHAR));
	if (hMenu->buttons[1].label == NULL)
		return NULL;

	hMenu->status = WAITING;
	hMenu->curButton = STARTGAME;
	hMenu->backColor = BLACK;
	hMenu->butColor = PURPLE;

	hMenu->buttons[0].pos.left = 350;
	hMenu->buttons[0].pos.top = 100;
	hMenu->buttons[0].pos.right = hMenu->buttons[0].pos.left + BUTTONWIDTH;
	hMenu->buttons[0].pos.bottom = hMenu->buttons[0].pos.top + BUTTONHEIGHT;
	wcscpy_s(hMenu->buttons[0].label, wcslen(L"\n\nStart game") + 1, L"\n\nStart game");

	hMenu->buttons[1].pos.left = 350;
	hMenu->buttons[1].pos.top = 400;
	hMenu->buttons[1].pos.right = hMenu->buttons[1].pos.left + BUTTONWIDTH;
	hMenu->buttons[1].pos.bottom = hMenu->buttons[1].pos.top + BUTTONHEIGHT;
	wcscpy_s(hMenu->buttons[1].label, wcslen(L"\n\nExit") + 1, L"\n\nExit");
 
	return hMenu;
}

void ChangeCursor(menu_t* hMenu)
{
	if (hMenu->curButton == STARTGAME)
		hMenu->curButton = EXIT;
	else
		hMenu->curButton = STARTGAME;
}

void DrawFrame(HDC hdc, RECT button)
{
	HPEN hPen = CreatePen(PS_SOLID, 5, RED);
	SelectObject(hdc, hPen);

	MoveToEx(hdc, button.left, button.bottom, NULL);
	LineTo(hdc, button.right, button.bottom);
	LineTo(hdc, button.right, button.top);
	LineTo(hdc, button.left, button.top);
	LineTo(hdc, button.left, button.bottom);

	DeleteObject(hPen);
}

void DrawMenu(HDC hdc, menu_t menu)
{
	HBRUSH hBackBrush = CreateSolidBrush(menu.backColor);
	SelectObject(hdc, hBackBrush);
	Rectangle(hdc, 0, 0, 1920, 1080);
	
	HBRUSH hButtonBrush = CreateSolidBrush(menu.butColor);
	SelectObject(hdc, hButtonBrush);
	Rectangle(hdc, menu.buttons[0].pos.left, menu.buttons[0].pos.top, menu.buttons[0].pos.right, menu.buttons[0].pos.bottom);
	Rectangle(hdc, menu.buttons[1].pos.left, menu.buttons[1].pos.top, menu.buttons[1].pos.right, menu.buttons[1].pos.bottom);

	HFONT hFont = CreateFontA(30, 18, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, ("Arial"));
	SelectObject(hdc, hFont);
	
	SetTextColor(hdc, WHITE);
	SetBkColor(hdc, menu.butColor);
	DrawTextW(hdc, menu.buttons[0].label, -1, &menu.buttons[0].pos, DT_CENTER);
	DrawTextW(hdc, menu.buttons[1].label, -1, &menu.buttons[1].pos, DT_CENTER);

	DeleteObject(hFont);
	DeleteObject(hButtonBrush);
	DeleteObject(hBackBrush);

	DrawFrame(hdc, menu.buttons[menu.curButton].pos);
	/*place for creativity*/
}

void FreeMenu(menu_t* hMenu)
{
	if (hMenu == NULL)
		return;
	free(hMenu->buttons[1].label);
	free(hMenu->buttons[0].label);
	free(hMenu);
}