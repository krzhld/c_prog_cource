#include "framework.h"
#include "ball.h"

ball_t* InitNewBall(ball_t* prevBall)
{
	ball_t* hBall;
	if (prevBall == NULL)
	{
		hBall = (ball_t*)malloc(sizeof(ball_t));
		if (hBall == NULL)
		{
			PostQuitMessage(2);
			return NULL;
		}
	}
	else
	{
		hBall = prevBall;
	}
	
	srand((unsigned int)time(NULL));

	hBall->pos.x = 400.0;
	hBall->pos.y = 692.9;

	hBall->dir.x = sin(rand());
	hBall->dir.y = -6.0;

	return hBall;
}

void MoveBall(ball_t* hBall)
{
	hBall->pos.x += hBall->dir.x;
	hBall->pos.y += hBall->dir.y;
}

void DrawBall(HDC hdc, ball_t ball)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, BALLCOLOR);
	HBRUSH hBrush = CreateSolidBrush(BALLCOLOR);
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);
	Ellipse(hdc, (int)ball.pos.x - BALLRAD, (int)ball.pos.y - BALLRAD, (int)ball.pos.x + BALLRAD, (int)ball.pos.y + BALLRAD);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}