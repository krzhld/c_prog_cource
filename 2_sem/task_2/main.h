#pragma once

#include "resource.h"
#include "framework.h"
#include <math.h>

typedef enum {
NEG = -1,
NONE,
POS
} convex_t;

typedef struct {
    double x;
    double y;
} POINTTYPE;

typedef struct {
    POINTTYPE pt1;
    POINTTYPE pt2;
    BOOL orientation;
} SEGMENTTYPE;