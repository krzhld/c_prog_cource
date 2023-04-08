#pragma once

#define RACKETCOLOR BLUE
#define RACKETWIDTH 10
#define RACKETSPEED 10

enum {
	DEFAULTSIZE = 50,
	SHORTSIZE = 10,
	LONGSIZE = 100
} RacketSizes;

typedef struct
{
	DPOINT pos;
	int size;
} racket_t;

racket_t* InitNewRacket(racket_t* prevRacket);

void MoveRacket(racket_t* hRacket, int direction);

void DrawRacket(HDC hdc, racket_t racket);