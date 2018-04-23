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
	
	int dx = x2 - x1;
	int dy = y2 - y1;
	int xsgn = dx > 0 ? 1 : -1;
	int ysgn = dy > 0 ? 1 : -1;

	int absdx = dx * xsgn;
	int absdy = dy * ysgn;

	x = 0;
	y = 0;

	if (absdx >= absdy) {
		int judge = absdy - absdx;
		while (x < absdx) {
			SetPixel(hdc, xsgn*x + x1, ysgn*y + y1, c);
			if (judge < 0) {
				x++;
				judge += 2 * absdy;
			}
			else {
				x++;
				y++;
				judge += 2 * absdy - 2 * absdx;
			}
		}
	}
	else {
		int judge = absdx - absdy;
		while (y < absdy) {
			SetPixel(hdc, xsgn*x + x1, ysgn*y + y1, c);
			if (judge < 0) {
				y++;
				judge += 2 * absdx;
			}
			else {
				x++;
				y++;
				judge += 2 * absdx - 2 * absdy;
			}
		}
	}

	
}

void drawLine(HDC hdc, IVector2 p1, IVector2 p2, COLORREF c) {
	drawLine(hdc, p1.x, p1.y, p2.x, p2.y,c);
}