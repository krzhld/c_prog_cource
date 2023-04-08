#ifndef DRAWING_H_INCLUDED

#include <windows.h>
#include <gl/gl.h>

#define WHEIGHT 1000
#define WWIDTH 1000
#define EOB -3 //end of blocks

void drawRectangles_before(int* i_blockSize, int* i_blocks);
void drawRectangles_after(int* blockSize);

#endif