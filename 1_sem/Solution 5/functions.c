#include <windows.h>
#include <gl/gl.h>
#include "functions.h"

int direction = NONE;
int i;
struct point_type {
    float x, y;
};
struct point_type lines[FREQ];

void DrawLine(float r, float g, float b, float alpha, int width)
{
    glLineWidth(width);
    glBegin(GL_LINES);
        glColor4f(r, g, b, 1); glVertex2f(OFF, OFF);
        glColor4f(r, g, b, 1); glVertex2f(-OFF, -OFF);
    glEnd();
}

void DrawLines()
{
    glLoadIdentity();
    for (i = FREQ - 1; i > 0; --i)
    {
    glPushMatrix();
    glTranslatef(lines[i].x, lines[i].y, 0);
    DrawLine(1.0, 0.0, 0.0, 0.0, THIN); //следы отрезка
    glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(lines[0].x, lines[0].y, 0);
    DrawLine(0.0, 0.0, 0.0, 1, THICK); //сам отрезок
    glPopMatrix();
}

void Reload()
{
    for (i = 1; i < FREQ - 1; ++i)
    {
        lines[i].x = lines[i+1].x;
        lines[i].y = lines[i+1].y;
    }
    lines[FREQ-1].x = lines[0].x;
    lines[FREQ-1].y = lines[0].y;
    if (direction == RIGHT)
    {
        if (lines[0].x + OFF >= RBORDER)
            direction = LEFT;
        else lines[0].x += STEP;
    }
    if (direction == LEFT)
    {
        if (lines[0].x - OFF <= LBORDER)
            direction = RIGHT;
        else lines[0].x -= STEP;
    }
    if (direction == UP)
    {
        if (lines[0].y + OFF >= RBORDER)
            direction = DOWN;
        else lines[0].y += STEP;
    }
    if (direction == DOWN)
    {
        if (lines[0].y - OFF <= LBORDER)
            direction = UP;
        else lines[0].y -= STEP;
    }
}
