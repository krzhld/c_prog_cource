#pragma once

#define BRICKSQUANTITY 32
#define BRICKWIDTH 100.0
#define BRICKHEIGHT 40.0
#define BONUSSPEED 10.0
#define BONUSSIZE 40.0

enum {
	ACTIVE = 40,
	FALLING,
	INVISIBLE
} BrickStatus;

enum {
	LIFE = 50,
	SHORTRACKET,
	LONGRACKET,
	EMPTY
} BrickBonuses;

typedef struct
{
	int type;
	DPOINT pos;
} bonus_t;

typedef struct
{
	DPOINT pos;
	bonus_t bonus;
	int color;
	BOOL status;
} brick_t;

brick_t** InitBricks(brick_t** prevBricks);

void MoveBonuses(brick_t** hBricks);

void DrawBonuses(HDC hdc, brick_t** hBricks);

void DrawBricks(HDC hdc, brick_t** hBricks);