#include "myGraphics.h"

int innerProductInt(IVector2 v1, IVector2 v2) {
	return v1.x*v2.x + v1.y*v2.y;
}
int innerProductInt(IVector3 v1, IVector3 v2) {
	return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
}

void drawLine(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c) {
	int x, y;
	
	if (x1 == x2) {
		x = x1;
		int sgn = y2 > y1 ? 1 : -1;
		for (y = y1; y != y2+sgn; y += sgn) {
			SetPixel(hdc, x, y, c);
		}
		return;
	}
	else if (y1 == y2) {
		y = y1;
		int sgn = x2 > x1 ? 1 : -1;
		for (x= x1; x != x2 + sgn; x += sgn) {
			SetPixel(hdc, x, y, c);
		}
		return;
	}
	//Bresenham
	if (x1 > x2) {//swap to ensure x1<x2
		int tx = x1, ty = y1;
		x1 = x2; y1 = y2;
		x2 = tx; y2 = ty;
	}

	
}

void drawLine(HDC hdc, IVector2 p1, IVector2 p2, COLORREF c) {
	drawLine(hdc, p1.x, p1.y, p2.x, p2.y,c);
}