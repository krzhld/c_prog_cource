#pragma once

#define BALLRAD 7.0

#define BALLCOLOR WHITE

typedef struct
{
	DPOINT pos; //radius-vector
	DPOINT dir; //vector of speed
} ball_t;

ball_t* InitNewBall(ball_t* prevBall);

void MoveBall(ball_t* hBall);

void DrawBall(HDC hdc, ball_t ball);