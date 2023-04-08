#pragma once

#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

enum {
	SIDEWALL = 60,
	UPPERWALL
} WallTypes;

BOOL IsItTouchWithRacket(racket_t hRacket, ball_t hBall);

void ReflectionWithRacket(racket_t hRacket, ball_t* hBall);

int IsItTouchWithBricks(brick_t** hBricks, ball_t hBall);

void ReflectionWithBrick(brick_t* hBrick, ball_t* hBall);

int IsItTouchWithWall(ball_t hBall);

void ReflectionWithWall(ball_t* hBall, int wall);

BOOL IsBallOutScreen(ball_t hBall);

BOOL IsItTouchRacketAndBonus(brick_t** hBricks, racket_t racket);

