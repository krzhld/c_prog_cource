#pragma once

double Length(SEGMENTTYPE lineSegment);

BOOL CalculateTriangles(int curIter, SEGMENTTYPE* lineSegments);

int GeomProgr(int power);

void Orientation(SEGMENTTYPE* lineSegment);

double DirCos(SEGMENTTYPE lineSegment);

double DirSin(SEGMENTTYPE lineSegment);