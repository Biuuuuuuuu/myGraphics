#ifndef MY_GRAPHICS_HPP
#define MY_GRAPHICS_HPP
#include <windows.h>
#include <vector>

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

inline int absInt(int i) {
	return i >= 0 ? i : -i;
}

inline int colorDiff(COLORREF c1, COLORREF c2) {
	int g = absInt(GetGValue(c1) - GetGValue(c2));
	int b = absInt(GetBValue(c1) - GetBValue(c2));
	int r = absInt(GetRValue(c1) - GetRValue(c2));
	return r + g + b;
}

inline int colorDiffPower2(COLORREF c1, COLORREF c2) {
	int g = absInt(GetGValue(c1) - GetGValue(c2));
	int b = absInt(GetBValue(c1) - GetBValue(c2));
	int r = absInt(GetRValue(c1) - GetRValue(c2));
	return r * r + g * g + b * b;
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

//正负法
inline void drawCircle1(HDC hdc, int ox, int oy, int r, COLORREF c) {
	if (r < 0) r = -r;
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
			judge += - x - 1;
			x++;
		}
		else {
			judge += y - x - 1;
			x++;
			y--;
		}
	}
}

inline void drawCircle(HDC hdc, IVector2 o, int r, COLORREF c) {
	drawCircle1(hdc, o.x, o.y, r, c);
}

inline void drawEllipse(HDC hdc, int ox, int oy, int a, int b, COLORREF c) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	int x = 0;
	int y = b;
	int judge = 0;
	while ((x*x)*(a*a + b*b) < a*a*a*a
		||(y*y)*(a*a+b*b)>b*b*b*b) { //第一象限斜率0到-1部分
	//while(x<a){
		SetPixel(hdc, ox + x, oy + y, c);
		SetPixel(hdc, ox - x, oy + y, c);
		SetPixel(hdc, ox + x, oy - y, c);
		SetPixel(hdc, ox - x, oy - y, c);
		if (judge > 0) {
			judge += -b*b*(x+1);
			x++;
		}
		else {
			judge+= -b*b*(x+1)-a*a*(-y+1);
			x++;
			y--;
		} 
	}
	//int ux = x, uy = y;
	y = 0;
	x = a;
	judge = 0;
	while ((x*x)*(a*a + b*b) > a*a*a*a
		|| (y*y)*(a*a + b * b)<b*b*b*b) {
	//while(y<b){
		SetPixel(hdc, ox + x, oy + y, c);
		SetPixel(hdc, ox - x, oy + y, c);
		SetPixel(hdc, ox + x, oy - y, c);
		SetPixel(hdc, ox - x, oy - y, c);
		if (judge > 0) {
			judge += -a*a*(y+1);
			y++;
		}
		else {
			judge += -a*a*(y+1)-b*b*(1-x);
			x--;
			y++;
		}
	}
	/*drawLine(hdc, ox + ux, oy + uy, ox + x, oy + y, c);
	drawLine(hdc, ox - ux, oy + uy, ox - x, oy + y, c);
	drawLine(hdc, ox + ux, oy - uy, ox + x, oy - y, c);
	drawLine(hdc, ox - ux, oy - uy, ox - x, oy - y, c);*/
}

inline void drawEllipse(HDC hdc, IVector2 o, int a, int b, COLORREF c) {
	drawEllipse(hdc, o.x, o.y, a, b, c);
}

enum  PixelConnectivity {Connect4, Connect8};

inline void fillDFS(HDC hdc, IVector2 o,
				COLORREF c, PixelConnectivity pc = Connect4) {
	COLORREF oldC = GetPixel(hdc, o.x, o.y);
	std::vector<IVector2> fillList;
	fillList.clear();
	fillList.push_back(o);
	while (!fillList.empty()) {
		IVector2 p = fillList.back();
		fillList.pop_back();
		SetPixel(hdc, p.x, p.y, c);

		COLORREF getC;
		#define SEARCH(dx,dy) getC=GetPixel(hdc, p.x+(dx), p.y+(dy));\
		if (getC == oldC && getC != c &&absInt(p.x)<5000&&absInt(p.y)<5000)\
			fillList.emplace_back(p.x+(dx), p.y+(dy))
		
		SEARCH(0, 1);
		SEARCH(1, 0);
		SEARCH(0, -1);
		SEARCH(-1, 0);

		if (pc == Connect8) {
			SEARCH(-1, -1);
			SEARCH(-1, 1);
			SEARCH(1, -1);
			SEARCH(1, 1);
		}		
		#undef SEARCH
	}
}

inline void fillDFS(HDC hdc, int ox, int oy,
				COLORREF c, PixelConnectivity pc = Connect4) {
	IVector2 o(ox, oy);
	fillDFS(hdc, o, c, pc);
}

inline void fillApproxDFS(HDC hdc, IVector2 o,
	COLORREF c, int diff = 0, PixelConnectivity pc = Connect4) {
	COLORREF oldC = GetPixel(hdc, o.x, o.y);
	std::vector<IVector2> fillList;
	fillList.clear();
	fillList.push_back(o);
	while (!fillList.empty()) {
		IVector2 p = fillList.back();
		fillList.pop_back();
		SetPixel(hdc, p.x, p.y, c);

		COLORREF getC;
#define SEARCH(dx,dy) getC=GetPixel(hdc, p.x+(dx), p.y+(dy));\
		if (colorDiffPower2(getC,oldC)<=diff*diff\
			&& getC != c &&absInt(p.x)<5000&&absInt(p.y)<5000)\
			fillList.emplace_back(p.x+(dx), p.y+(dy))

		SEARCH(0, 1);
		SEARCH(1, 0);
		SEARCH(0, -1);
		SEARCH(-1, 0);

		if (pc == Connect8) {
			SEARCH(-1, -1);
			SEARCH(-1, 1);
			SEARCH(1, -1);
			SEARCH(1, 1);
		}
#undef SEARCH
	}
}

inline void fillApproxDFS(HDC hdc, int ox, int oy,
	COLORREF c, int diff = 0, PixelConnectivity pc = Connect4) {
	IVector2 o(ox, oy);
	fillApproxDFS(hdc, o, c, diff, pc);
}

#else
#endif