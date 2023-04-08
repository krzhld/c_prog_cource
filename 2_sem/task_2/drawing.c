#include "main.h"
#include "drawing.h"

void DrawTriangle(HDC hdc, int curIter, SEGMENTTYPE* lineSegments)
{
	for (int i = GeomProgr(curIter - 1); i < GeomProgr(curIter); ++i)
	{
		MoveToEx(hdc, lineSegments[i].pt1.x, lineSegments[i].pt1.y, NULL);
		LineTo(hdc, lineSegments[i].pt2.x, lineSegments[i].pt2.y);
	}
}

void Rope(HDC hdc, SEGMENTTYPE* lineSegments)
{
	MoveToEx(hdc, lineSegments->pt1.x, lineSegments->pt1.y, NULL);
	LineTo(hdc, lineSegments->pt2.x, lineSegments->pt2.y);
}