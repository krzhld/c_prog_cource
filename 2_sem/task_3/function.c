#include "function.h"

void DrawCross(HDC hdc, RECT rect)
{
	MoveToEx(hdc, rect.left, rect.bottom, NULL);
	LineTo(hdc, rect.right, rect.top);
	MoveToEx(hdc, rect.left, rect.top, NULL);
	LineTo(hdc, rect.right, rect.bottom);
}

void DrawFrame(HDC hdc, RECT rect)
{
	MoveToEx(hdc, rect.left, rect.bottom, NULL);
	LineTo(hdc, rect.right, rect.bottom);
	LineTo(hdc, rect.right, rect.top);
	LineTo(hdc, rect.left, rect.top);
	LineTo(hdc, rect.left, rect.bottom);
}

void DefaultButton(button_t* hButton)
{
	hButton->color = RED;
	hButton->highlightColor = YELLOW;
	hButton->position.left = hButton->position.right = 0;
	hButton->position.top = hButton->position.bottom = BUTTONSIZE;
	hButton->name[0] = 'A';
	hButton->isSelected = FALSE;
}

void DefaultWindow(window_t* hWindow)
{
	hWindow->color = CYAN;
	hWindow->position.left = hWindow->position.right = 0;
	hWindow->position.top = hWindow->position.bottom = WINDOWSIZE;
}

menu_t* SystemOpen()
{
	menu_t* hMenu = (menu_t*)calloc(1, sizeof(menu_t));
	if (hMenu == NULL)
		return NULL;

	hMenu->isReturnDown = FALSE;
	hMenu->fp = NULL;
	hMenu->numberButtons = 0;
	hMenu->numberWindows = 0;
	hMenu->numberOfCurButton = 0;
	hMenu->buttons = NULL;
	hMenu->windows = NULL;

	return hMenu;
}

int SystemInitialize(menu_t* hMenu, const WCHAR* menuFileName)
{
	_wfopen_s(&hMenu->fp, menuFileName, L"rt");
	if (hMenu->fp == NULL)
		return FALSE;
	else
	{
		WCHAR buffer[MAX_LOADSTRING] = { 0 };
		WCHAR* bufferPtr = NULL;
		fwscanf_s(hMenu->fp, L"%s", buffer, MAX_LOADSTRING);
		if (!wcscmp(buffer, L"MenuBegin"))
		{
			while (fwscanf_s(hMenu->fp, L"%ls", buffer, MAX_LOADSTRING))
			{
				if (!wcscmp(buffer, L"WindowBegin"))
				{
					button_t* bufferPtrWindow = NULL;
					++(hMenu->numberWindows);
					bufferPtrWindow = (window_t*)realloc(hMenu->windows, (hMenu->numberWindows) * sizeof(window_t));
					if (bufferPtrWindow != NULL)
						hMenu->windows = bufferPtrWindow;
					else
					{
						free(hMenu);
						PostQuitMessage(FALSE);
						return;
					}
					DefaultWindow(hMenu->windows + hMenu->numberWindows - 1);
					do {
						fwscanf_s(hMenu->fp, L"%ls", buffer, MAX_LOADSTRING);
						if (!wcsncmp(buffer, L"Position=", wcslen(L"Position=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += wcslen(L"Position=");
							hMenu->windows[hMenu->numberWindows - 1].position.left = _wtoi(bufferPtr);
							bufferPtr = wcschr(buffer, L',');
							++bufferPtr;
							hMenu->windows[hMenu->numberWindows - 1].position.top = _wtoi(bufferPtr);
							hMenu->windows[hMenu->numberWindows - 1].position.right = hMenu->windows[hMenu->numberWindows - 1].position.left + WINDOWSIZE;
							hMenu->windows[hMenu->numberWindows - 1].position.bottom = hMenu->windows[hMenu->numberWindows - 1].position.top + WINDOWSIZE;
						}
						if (!wcsncmp(buffer, L"Color=", wcslen(L"Color=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += strlen("Color=");
							hMenu->windows[hMenu->numberWindows - 1].color = _wtoi(bufferPtr);
						}
					} while (wcscmp(buffer, L"WindowEnd"));
				}

				if (!wcscmp(buffer, L"ButtonBegin"))
				{
					window_t* bufferPtrButton = NULL;
					++(hMenu->numberButtons);
					bufferPtrButton = (button_t*)realloc(hMenu->buttons, (hMenu->numberButtons) * sizeof(button_t));
					if (bufferPtrButton != NULL)
						hMenu->buttons = bufferPtrButton;
					else
					{
						free(hMenu);
						PostQuitMessage(FALSE);
						return;
					}
					DefaultButton(hMenu->buttons + hMenu->numberButtons - 1);
					do {
						fwscanf_s(hMenu->fp, L"%ls", buffer, MAX_LOADSTRING);
						if (!wcsncmp(buffer, L"Position=", wcslen(L"Position=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += strlen("Position=");
							hMenu->buttons[hMenu->numberButtons - 1].position.left = _wtoi(bufferPtr);
							bufferPtr = wcschr(buffer, ',');
							++bufferPtr;
							hMenu->buttons[hMenu->numberButtons - 1].position.top = _wtoi(bufferPtr);
							hMenu->buttons[hMenu->numberButtons - 1].position.right = hMenu->buttons[hMenu->numberButtons - 1].position.left + BUTTONSIZE;
							hMenu->buttons[hMenu->numberButtons - 1].position.bottom = hMenu->buttons[hMenu->numberButtons - 1].position.top + BUTTONSIZE;
						}
						if (!wcsncmp(buffer, L"Color=", wcslen(L"Color=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += strlen("Color=");
							hMenu->buttons[hMenu->numberButtons - 1].color = _wtoi(bufferPtr);
						}
						if (!wcsncmp(buffer, L"HiglightColor=", wcslen(L"HiglightColor=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += strlen("HiglightColor=");
							hMenu->buttons[hMenu->numberButtons - 1].highlightColor = _wtoi(bufferPtr);
						}
						if (!wcsncmp(buffer, L"Name=", wcslen(L"Name=")))
						{
							bufferPtr = &buffer[0];
							bufferPtr += strlen("Name=");
							int k = 0;
							while (*bufferPtr != '\0')
							{
								hMenu->buttons[hMenu->numberButtons - 1].name[k] = *bufferPtr;
								++bufferPtr;
								++k;
							}
							hMenu->buttons[hMenu->numberButtons - 1].name[k] = '\0';
							bufferPtr -= k;
						}

					} while (wcscmp(buffer, L"ButtonEnd"));
				}

				if (!wcscmp(buffer, L"MenuEnd"))
				{
					break;
				}

			}
		}
	}

	return TRUE;
}

menu_t* SystemRelease(menu_t* hMenu)
{
	menu_t* rMenu = malloc(sizeof(menu_t));
	rMenu->buttons = hMenu->buttons;
	rMenu->fp = hMenu->fp;
	rMenu->isReturnDown = hMenu->isReturnDown;
	rMenu->numberButtons = hMenu->numberButtons;
	rMenu->numberOfCurButton = hMenu->numberOfCurButton;
	rMenu->numberWindows = hMenu->numberWindows;
	rMenu->windows = hMenu->windows;
	return rMenu;
}

void SystemUpdate(menu_t* hMenu, HDC hdc)
{
	HBRUSH hBrush;
	HPEN hPen;
	int i;

	for (i = 0; i < hMenu->numberWindows; i++)
	{
		hBrush = CreateSolidBrush(hMenu->windows[i].color);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, hMenu->windows[i].position.left, hMenu->windows[i].position.top, hMenu->windows[i].position.right, hMenu->windows[i].position.bottom);
		DeleteObject(hBrush);
	}
	if (hMenu->isReturnDown == TRUE)
	{
		int curBut = hMenu->numberOfCurButton;
		hBrush = CreateSolidBrush(hMenu->buttons[curBut].color);
		hPen = CreatePen(PS_SOLID, 2, hMenu->buttons[curBut].highlightColor);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, hMenu->buttons[curBut].position.left, hMenu->buttons[curBut].position.top, hMenu->buttons[curBut].position.right, hMenu->buttons[curBut].position.bottom);
		SelectObject(hdc, hPen);
		DrawFrame(hdc, hMenu->buttons[curBut].position);
		hPen = CreatePen(PS_SOLID, 2, ~hMenu->buttons[curBut].highlightColor);
		DrawText(hdc, hMenu->buttons[curBut].name, -1, &hMenu->buttons[curBut].position, DT_CENTER);
		DrawCross(hdc, hMenu->buttons[curBut].position);
		DeleteObject(hBrush);
		DeleteObject(hPen);
	}
	if (hMenu->isReturnDown == FALSE)
	{
		for (i = 0; i < hMenu->numberButtons; i++)
		{
			hBrush = CreateSolidBrush(hMenu->buttons[i].color);
			hPen = CreatePen(PS_SOLID, 2, hMenu->buttons[i].highlightColor);
			SelectObject(hdc, hBrush);
			Rectangle(hdc, hMenu->buttons[i].position.left, hMenu->buttons[i].position.top, hMenu->buttons[i].position.right, hMenu->buttons[i].position.bottom);
			SelectObject(hdc, hPen);
			DrawFrame(hdc, hMenu->buttons[i].position);
			DeleteObject(hBrush);
			DeleteObject(hPen);
		}
	}

}

int SystemClose(menu_t* hMenu)
{
	if (hMenu != NULL)
	{
		free(hMenu);
		return FALSE;
	}
	return TRUE;
}