#include "framework.h"
#include "ball.h"
#include "racket.h"
#include "bricks.h"
#include "interactions.h"

BOOL IsItTouchWithRacket(racket_t hRacket, ball_t hBall)
{
	if ( (hBall.pos.y <= hRacket.pos.y) && (hBall.pos.y >= hRacket.pos.y - BALLRAD) )
	{
		if ( (hBall.pos.x + BALLRAD >= hRacket.pos.x - hRacket.size ) && (hBall.pos.x - BALLRAD <= hRacket.pos.x + hRacket.size) )
			return TRUE;
	}
	return FALSE;
}

void ReflectionWithRacket(racket_t hRacket, ball_t* hBall)
{
	double speed;
	speed = sqrt(hBall->dir.x * hBall->dir.x + hBall->dir.y * hBall->dir.y);
	
	hBall->dir.x = speed * sin((hBall->pos.x - hRacket.pos.x) / hRacket.size * PI / 4);
	hBall->dir.y = -sqrt(speed * speed - hBall->dir.x * hBall->dir.x);
	return;
 }

int IsItTouchWithBricks(brick_t** hBricks, ball_t hBall)
{
	for (int i = 0; i < BRICKSQUANTITY; ++i)
	{
		if (hBricks[i]->status == INVISIBLE || hBricks[i]->status == FALLING)
			continue;
		else
		{
			if (hBall.pos.x > hBricks[i]->pos.x && hBall.pos.x < hBricks[i]->pos.x + BRICKWIDTH)
			{
				if (hBall.pos.y >= hBricks[i]->pos.y + BRICKHEIGHT && hBall.pos.y <= hBricks[i]->pos.y + BRICKHEIGHT + (int)BALLRAD)
					return i;
				if (hBall.pos.y >= hBricks[i]->pos.y - BALLRAD && hBall.pos.y <= hBricks[i]->pos.y)
					return i;
			}
			if (hBall.pos.y > hBricks[i]->pos.y && hBall.pos.y < hBricks[i]->pos.y + BRICKHEIGHT)
			{
				if (hBall.pos.x >= hBricks[i]->pos.x + BRICKWIDTH && hBall.pos.x <= hBricks[i]->pos.x + BRICKWIDTH + BALLRAD)
					return i;
				if (hBall.pos.x >= hBricks[i]->pos.x - BALLRAD && hBall.pos.x <= hBricks[i]->pos.x)
					return i;
			}
		}
	}
	return -1; // output index of brick; input -1 if there aren't reflections
}

void ReflectionWithBrick(brick_t* hBrick, ball_t* hBall)
{
	double speed;
	speed = sqrt(hBall->dir.x * hBall->dir.x + hBall->dir.y * hBall->dir.y);

	//is ball concerning under or upper of brick?
	if (hBall->pos.x >= hBrick->pos.x && hBall->pos.x <= hBrick->pos.x + BRICKWIDTH)
	{
		if ((hBall->pos.y >= hBrick->pos.y + BRICKHEIGHT && hBall->pos.y <= hBrick->pos.y + BRICKHEIGHT + BALLRAD) ||
			(hBall->pos.y >= hBrick->pos.y - BALLRAD && hBall->pos.y <= hBrick->pos.y))
		{
			hBall->dir.y = -hBall->dir.y;
			if (hBrick->bonus.type != EMPTY)
				hBrick->status = FALLING;
			else
				hBrick->status = INVISIBLE;
			return;
		}
	}
	//is ball concerning left or right of brick?
	if (hBall->pos.y >= hBrick->pos.y && hBall->pos.y <= hBrick->pos.y + BRICKHEIGHT)
	{
		if ((hBall->pos.x >= hBrick->pos.x + BRICKWIDTH && hBall->pos.x <= hBrick->pos.x + BRICKWIDTH + BALLRAD) ||
			(hBall->pos.x >= hBrick->pos.x - BALLRAD && hBall->pos.x <= hBrick->pos.x))
		{
			hBall->dir.x = -hBall->dir.x; 
			if (hBrick->bonus.type != EMPTY)
				hBrick->status = FALLING;
			else
				hBrick->status = INVISIBLE;
			return;
		}
	}
}

int IsItTouchWithWall(ball_t hBall)
{
	int x = (int)hBall.pos.x;
	int y = (int)hBall.pos.y;
	if ( (x >= 0) && (x <= (int)BALLRAD) || (x >= WINDOWWIDTH - 200 - (int)BALLRAD) && (x <= WINDOWWIDTH - 200) )
		return SIDEWALL;
	if ((y >= 0) && (y <= (int)BALLRAD))
		return UPPERWALL;
	return FALSE;
}

void ReflectionWithWall(ball_t* hBall, int wall)
{
	switch (wall)
	{
		case SIDEWALL:
			hBall->dir.x = -hBall->dir.x;
			break;
		case UPPERWALL:
			hBall->dir.y = -hBall->dir.y;
			break;
		default:
			return;
	}
}

BOOL IsBallOutScreen(ball_t hBall)
{
	if ((int)hBall.pos.y > WINDOWHEIGHT + (int)BALLRAD)
		return TRUE;
	else
		return FALSE;
}

BOOL IsItTouchRacketAndBonus(brick_t** hBricks, racket_t racket)
{
	for (int i = 0; i < BRICKSQUANTITY; ++i)
		if (hBricks[i]->status == FALLING)
			if (hBricks[i]->bonus.pos.y >= racket.pos.y - BONUSSIZE && hBricks[i]->bonus.pos.y <= racket.pos.y + BONUSSIZE)
				if (hBricks[i]->bonus.pos.x >= racket.pos.x - racket.size - BONUSSIZE / 2 && hBricks[i]->bonus.pos.x <= racket.pos.x + racket.size + BONUSSIZE / 2)
					return i;
	return -1;
} 