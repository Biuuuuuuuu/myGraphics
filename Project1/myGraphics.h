#pragma once
#include <windows.h>

struct IVector2{
	int x;
	int y;
	IVector2(int x_, int y_) :x(x_), y(y_) {};
	~IVector2() = default;
};

struct IVector3 {
	int x;
	int y;
	int z;
	IVector3(int x_, int y_,int z_) :x(x_), y(y_),z(z_){};
	~IVector3() = default;
};

int innerProductInt(IVector2 v1, IVector2 v2);
int innerProductInt(IVector3 v1, IVector3 v2);

void drawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
void drawLine(HDC hdc, IVector2 p1, IVector2 p2, COLORREF c);