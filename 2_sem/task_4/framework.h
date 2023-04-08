#pragma once

#include "targetver.h"
#include "Resource.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <time.h>

#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1000
#define BARWIDTH 200
#define PI 3.141593

enum {
	RED = RGB(255, 0, 0),
	ORANGE = RGB(255, 125, 0),
	YELLOW = RGB(255, 255, 0),
	GREEN = RGB(0, 255, 0),
	CYAN = RGB(0, 255, 255),
	BLUE = RGB(0, 0, 255),
	MAGENTA = RGB(255, 0, 255),
	BLACK = RGB(0, 0, 0),
	WHITE = RGB(255, 255, 255),
	PURPLE = RGB(148, 148, 255)
} Colors;

typedef struct
{
	double x, y;
} DPOINT;