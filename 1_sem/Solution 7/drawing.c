#include "drawing.h"

void drawRectangles_before(int* i_blockSize, int* i_blocks)
{
	for (int i = 0; i < *i_blocks; i++)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0, 1.0, 0.0);	
			glVertex2i(50, WHEIGHT-(50+i*20));
			glVertex2i(50, WHEIGHT-(50+(i+1)*20));
			glVertex2i(50+i_blockSize[i], WHEIGHT-(50+(i+1)*20));		
			glVertex2i(50+i_blockSize[i], WHEIGHT-(50+i*20));
		glEnd();

		glBegin(GL_LINE_STRIP);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(50, WHEIGHT-(50+i*20));
			glVertex2i(50, WHEIGHT-(50+(i+1)*20));
			glVertex2i(50+i_blockSize[i], WHEIGHT-(50+(i+1)*20));
			glVertex2i(50+i_blockSize[i], WHEIGHT-(50+i*20));
			glVertex2i(50, WHEIGHT-(50+i*20));
		glEnd();
	}
}

void drawRectangles_after(int* blockSize)
{
	int i = 0;
	while (*blockSize != EOB)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0, 1.0, 0.0);	
			glVertex2i(50, 50+i*20);
			glVertex2i(50, 50+(i+1)*20);
            glVertex2i(50+*blockSize, 50+(i+1)*20);
			glVertex2i(50+*blockSize, 50+i*20);
		glEnd();

		glBegin(GL_LINE_STRIP);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2i(50, 50+i*20);
			glVertex2i(50, 50+(i+1)*20);
			glVertex2i(50+*blockSize, 50+(i+1)*20);
			glVertex2i(50+*blockSize, 50+i*20);
			glVertex2i(50, 50+i*20);
		glEnd();
			
		++blockSize;
		++i;
	}
	blockSize -= i;
}
