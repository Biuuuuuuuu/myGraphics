#ifndef MY_GRAPHICS_HPP
#define MY_GRAPHICS_HPP
#include <windows.h>

struct IVector2 {
	int x;
	int y;
	IVector2(int x_, int y_) :x(x_), y(y_) {};
	~IVector2() = default;
};

struct IVector3 {
	int x;
	int y;
	int z;
	IVector3(int x_, int y_, int z_) :x(x_), y(y_), z(z_) {};
	~IVector3() = default;
};

inline int innerProductInt(IVector2 v1, IVector2 v2) {
	return v1.x*v2.x + v1.y*v2.y;
}
inline int innerProductInt(IVector3 v1, IVector3 v2) {
	return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
}

inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c) {
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

inline void drawLine(HDC hdc, IVector2 p1, IVector2 p2, COLORREF c) {
	drawLine(hdc, p1.x, p1.y, p2.x, p2.y,c);
}

//Õý¸º·¨
inline void drawCircle1(HDC hdc, int ox, int oy, int r, COLORREF c) {
	int x = 0;
	int y = r;
	int judge = 0;
	while (y >= 0) {
		SetPixel(hdc, ox + x, oy + y, c);
		SetPixel(hdc, ox - x, oy + y, c);
		SetPixel(hdc, ox + x, oy - y, c);		
		SetPixel(hdc, ox - x, oy - y, c);
		if (judge < 0) {
			judge += 2 * x + 1;
			x++;
		}
		else {
			judge += -2 * y + 1;
			y--;
		}
	}
}

inline void drawCircle1(HDC hdc, IVector2 o, int r, COLORREF c) {
	drawCircle1(hdc, o.x, o.y, r, c);
}

//Bresenham
inline void drawCircle(HDC hdc, int ox, int oy, int r, COLORREF c) {
	int x = 0;
	int y = r;
	int judge = 0;
	while (y >= x) {
		SetPixel(hdc, ox + x, oy + y, c);
		SetPixel(hdc, ox + x, oy - y, c);
		SetPixel(hdc, ox - x, oy + y, c);
		SetPixel(hdc, ox - x, oy - y, c);

		SetPixel(hdc, ox + y, oy + x, c);
		SetPixel(hdc, ox + y, oy - x, c);
		SetPixel(hdc, ox - y, oy + x, c);
		SetPixel(hdc, ox - y, oy - x, c);		
		if (judge > 0) {
			judge += -2 * x - 2;
			x++;
		}
		else {
			judge += 2*y - 2*x - 2;
			x++;
			y--;
		}
	}
}

inline void drawCircle(HDC hdc, IVector2 o, int r, COLORREF c) {
	drawCircle1(hdc, o.x, o.y, r, c);
}

#else
#endif