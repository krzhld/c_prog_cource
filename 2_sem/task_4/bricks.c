#include "framework.h"
#include "bricks.h"

brick_t** InitBricks(brick_t** prevBricks)
{
	brick_t** hBricks;
	if (prevBricks == NULL)
	{
		hBricks = (brick_t**)malloc(BRICKSQUANTITY * sizeof(brick_t*));
		if (hBricks == NULL)
		{
			PostQuitMessage(4);
			return NULL;
		}
		for (int i = 0; i < BRICKSQUANTITY; ++i)
		{
			hBricks[i] = (brick_t*)malloc(sizeof(brick_t));
			if (hBricks[i] == NULL)
				return NULL;
		}
	}
	else
	{
		hBricks = prevBricks;
	}
		
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < BRICKSQUANTITY/4; ++j)
		{
			hBricks[(BRICKSQUANTITY/4) * i + j]->status = ACTIVE;
			switch (rand() % 6)
			{
			case 0:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = RED;
				break;
			case 1:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = ORANGE;
				break;
			case 2:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = YELLOW;
				break;
			case 3:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = GREEN;
				break;
			case 4:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = CYAN;
				break;
			case 5:
				hBricks[(BRICKSQUANTITY/4) * i + j]->color = MAGENTA;
				break;
			}
			hBricks[(BRICKSQUANTITY / 4) * i + j]->pos.y = i * BRICKHEIGHT;
			hBricks[(BRICKSQUANTITY / 4) * i + j]->pos.x = j * BRICKWIDTH;

			// init bonuses
			switch (rand() % 20)
			{
			case 0:
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.type = LIFE;
				break;
			case 1:
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.type = SHORTRACKET;
				break;
			case 2:
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.type = LONGRACKET;
				break;
			default:
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.type = EMPTY;
				break;
			}
			
			if (hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.type != EMPTY)
			{
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.pos.x = hBricks[(BRICKSQUANTITY / 4) * i + j]->pos.x + BRICKWIDTH / 2;
				hBricks[(BRICKSQUANTITY / 4) * i + j]->bonus.pos.y = hBricks[(BRICKSQUANTITY / 4) * i + j]->pos.y + BRICKHEIGHT / 2;
			}
		}
	}
	return hBricks;
}

void MoveBonuses(brick_t** hBricks)
{
	for (int i = 0; i < BRICKSQUANTITY; ++i)
	{
		if ((hBricks[i]->status == FALLING) &&(hBricks[i]->bonus.type != EMPTY))
			hBricks[i]->bonus.pos.y += BONUSSPEED;
	}
}

void DrawBonuses(HDC hdc, brick_t** hBricks)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, BLACK);
	SelectObject(hdc, hPen);

	HBRUSH hPurpleBrush = CreateSolidBrush(PURPLE);
	HBRUSH hYellowBrush = CreateSolidBrush(YELLOW);
	HBRUSH hRedBrush = CreateSolidBrush(RED);

	for (int i = 0; i < BRICKSQUANTITY; ++i)
	{
		if (hBricks[i]->status == FALLING && hBricks[i]->bonus.type != EMPTY)
		{
			switch (hBricks[i]->bonus.type)
			{
			case LIFE:
				SelectObject(hdc, hRedBrush);
				break;
			case SHORTRACKET:
				SelectObject(hdc, hYellowBrush);
				break;
			case LONGRACKET:
				SelectObject(hdc, hPurpleBrush);
				break;
			}
			Rectangle(hdc, hBricks[i]->bonus.pos.x - BONUSSIZE / 2, hBricks[i]->bonus.pos.y - BONUSSIZE / 2, hBricks[i]->bonus.pos.x + BONUSSIZE / 2, hBricks[i]->bonus.pos.y + BONUSSIZE / 2);
		}
	}
		
		
	DeleteObject(hPen);
	DeleteObject(hPurpleBrush);
	DeleteObject(hYellowBrush);
	DeleteObject(hRedBrush);
}

void DrawBricks(HDC hdc, brick_t** hBricks)
{
	HBRUSH hRedBrush = CreateSolidBrush(RED);
	HBRUSH hOrangeBrush = CreateSolidBrush(ORANGE);
	HBRUSH hYellowBrush = CreateSolidBrush(YELLOW);
	HBRUSH hGreenBrush = CreateSolidBrush(GREEN);
	HBRUSH hCyanBrush = CreateSolidBrush(CYAN);
	HBRUSH hMagentaBrush = CreateSolidBrush(MAGENTA);

	HPEN hPen = CreatePen(PS_SOLID, 2, BLACK);
	SelectObject(hdc, hPen);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < BRICKSQUANTITY/4; ++j)
		{
			if (hBricks[(BRICKSQUANTITY/4) * i + j]->status == ACTIVE) 
			{
				switch (hBricks[(BRICKSQUANTITY/4) * i + j]->color)
				{
				case RED:
					SelectObject(hdc, hRedBrush);
					break;
				case ORANGE:
					SelectObject(hdc, hOrangeBrush);
					break;
				case YELLOW:
					SelectObject(hdc, hYellowBrush);
					break;
				case GREEN:
					SelectObject(hdc, hGreenBrush);
					break;
				case CYAN:
					SelectObject(hdc, hCyanBrush);
					break;
				case MAGENTA:
					SelectObject(hdc, hMagentaBrush);
					break;
				}
				Rectangle(hdc, hBricks[(BRICKSQUANTITY/4) * i + j]->pos.x, hBricks[(BRICKSQUANTITY/4) * i + j]->pos.y,
					hBricks[(BRICKSQUANTITY/4) * i + j]->pos.x + BRICKWIDTH, hBricks[(BRICKSQUANTITY/4) * i + j]->pos.y + BRICKHEIGHT);
			}
		}
	}
	DeleteObject(hPen);
	DeleteObject(hRedBrush);
	DeleteObject(hOrangeBrush);
	DeleteObject(hYellowBrush);
	DeleteObject(hGreenBrush);
	DeleteObject(hCyanBrush);
	DeleteObject(hMagentaBrush);
}