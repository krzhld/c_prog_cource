#include "main.h"
#include "calculations.h"

BOOL CalculateTriangles(int curIter, SEGMENTTYPE* lineSegments)
{
	double _x0, _x1, _x2, _x3, _y0, _y1;
	int indLastSegm = GeomProgr(curIter - 1) - 1;
	int indFirstSegm;
	if (curIter == 1)
		indFirstSegm = indLastSegm;
	else
		indFirstSegm = GeomProgr(curIter - 2);

	if ((lineSegments[indLastSegm].orientation == NONE))
		Orientation(lineSegments + indLastSegm);

	double lineLength = Length(lineSegments[indFirstSegm]);

	for (int i = indFirstSegm; i <= indLastSegm; ++i)
	{
		double _dirCos = DirCos(lineSegments[i]);
		double _dirSin = DirSin(lineSegments[i]);
		_x0 = lineSegments[i].pt1.x * _dirCos - lineSegments[i].pt1.y * _dirSin;
		_x3 = lineSegments[i].pt2.x * _dirCos - lineSegments[i].pt2.y * _dirSin;
		_x1 = _x0 + (_x3 - _x0) / 4;
		_x2 = _x0 + 3 * (_x3 - _x0) / 4;

		_y0 = lineSegments[i].pt1.x * _dirSin + lineSegments[i].pt1.y * _dirCos;

		if (lineSegments[i].orientation == POS)
		{
			_y1 = _y0 - lineLength * sqrt(3) / 4;
			lineSegments[3 * i + 1].orientation = NEG;
			lineSegments[3 * i + 2].orientation = POS;
			lineSegments[3 * i + 3].orientation = NEG;
		}
		else
		{
			_y1 = _y0 + lineLength * sqrt(3) / 4;
			lineSegments[3 * i + 1].orientation = POS;
			lineSegments[3 * i + 2].orientation = NEG;
			lineSegments[3 * i + 3].orientation = POS;
		}

		lineSegments[3 * i + 1].pt1.x = _x0 * _dirCos + _y0 * _dirSin;
		lineSegments[3 * i + 1].pt1.y = -_x0 * _dirSin + _y0 * _dirCos;
		lineSegments[3 * i + 1].pt2.x = _x1 * _dirCos + _y1 * _dirSin;
		lineSegments[3 * i + 1].pt2.y = -_x1 * _dirSin + _y1 * _dirCos;
		
		lineSegments[3 * i + 2].pt1 = lineSegments[3 * i + 1].pt2;
		lineSegments[3 * i + 2].pt2.x = _x2 * _dirCos + _y1 * _dirSin;
		lineSegments[3 * i + 2].pt2.y = -_x2 * _dirSin + _y1 * _dirCos;

		lineSegments[3 * i + 3].pt1 = lineSegments[3 * i + 2].pt2;
		lineSegments[3 * i + 3].pt2.x = _x3 * _dirCos + _y0 * _dirSin;
		lineSegments[3 * i + 3].pt2.y = -_x3 * _dirSin + _y0 * _dirCos;
	}
	
	return TRUE;
}

double Length(SEGMENTTYPE lineSegment)
{
	double x = lineSegment.pt1.x - lineSegment.pt2.x;
	double y = lineSegment.pt1.y - lineSegment.pt2.y;
	return sqrt(x * x + y * y);
}

double DirCos(SEGMENTTYPE lineSegment)
{
	double cathetus = lineSegment.pt2.x - lineSegment.pt1.x;
	double result = cathetus / Length(lineSegment);
	return result;
}

double DirSin(SEGMENTTYPE lineSegment)
{
	double cathetus = lineSegment.pt1.y - lineSegment.pt2.y;
	double result = cathetus / Length(lineSegment);
	return result;
}

void Orientation(SEGMENTTYPE* lineSegment)
{
	if ((lineSegment->pt2.x >= lineSegment->pt1.x) && (lineSegment->pt2.y <= lineSegment->pt1.y))
		lineSegment->orientation = POS;
	else
		lineSegment->orientation = NEG;
}

int GeomProgr(int power)
{
	int result = (pow(3, power + 1) - 1) / 2;
	return result;
}