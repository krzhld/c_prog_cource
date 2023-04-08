#include "framework.h"
#include "racket.h"

racket_t* InitNewRacket(racket_t* prevRacket)
{
	racket_t* hRacket;
	if (prevRacket == NULL)
	{
		hRacket = (racket_t*)malloc(sizeof(racket_t));
		if (hRacket == NULL)
		{
			PostQuitMessage(3);
			return NULL;
		}
	}
	else
	{
		hRacket = prevRacket;
	}

	hRacket->pos.x = 400.0;
	hRacket->pos.y = 700.0;

	hRacket->size = DEFAULTSIZE;

	return hRacket;
}

void MoveRacket(racket_t* hRacket, int direction)
{
	switch (direction)
	{
	case VK_LEFT:
		if ((int)(hRacket->pos.x - hRacket->size - RACKETSPEED) >= 0)
			hRacket->pos.x -= RACKETSPEED;
		break;
	case VK_RIGHT:
		if ((int)(hRacket->pos.x + hRacket->size + RACKETSPEED) <= WINDOWWIDTH - 200)
			hRacket->pos.x += RACKETSPEED;
		break;
	}
}

void DrawRacket(HDC hdc, racket_t racket)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RACKETCOLOR);
	HBRUSH hBrush = CreateSolidBrush(RACKETCOLOR);
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);
	Rectangle(hdc, racket.pos.x - racket.size, racket.pos.y, racket.pos.x + racket.size, racket.pos.y + RACKETWIDTH);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}