#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "myGraphics.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int x, y;
long c;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t className[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		className,                     // Window class
		L"绘制",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	
	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, L"确认退出?", L"退出...", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//涂黑背景
		RECT fullRect;
		fullRect.bottom = 0;
		fullRect.left = 0;
		fullRect.right = 2560;
		fullRect.top = 1080;
		FillRect(hdc, &fullRect, CreateSolidBrush(RGB(0, 0, 0)));
				
		//绘制

		//Bresenham画线
		for (int i = 0; i <= 600; i += 6) {
			drawLine(hdc, 300, 300, 600, i, RGB(i, 0, 255));
			drawLine(hdc, 300, 300, 0, i, RGB(i, 255, 0));
			drawLine(hdc, 300, 300, i, 0, RGB(0, i, 255));
			drawLine(hdc, 300, 300, i, 600, RGB(255, i, 0));
		}

		//Bresenham画圆
		drawCircle(hdc, 300, 300, 200, RGB(255, 100, 100));
		//正负法画圆
		drawCircle1(hdc, 300, 300, 250, RGB(100, 100, 255));

		//Bresenham画椭圆
		for(int i=40;i<=400;i+=40)
			drawEllipse(hdc, 700, 200+2*(i-100), i, 50, RGB(100, (i-200)*2, 50));
		for (int i = 40; i <=400; i += 40)
			drawEllipse(hdc, 200 + 2 * (i - 100), 700, 50, i, RGB((i - 200) * 2, 50, 100));
		
		//多边形填充 画名字：YHL
		std::vector<IVector2> v;
		v.emplace_back(40, 40);
		v.emplace_back(80, 40);
		v.emplace_back(120, 80);
		v.emplace_back(160, 40);
		v.emplace_back(200, 40);
		v.emplace_back(140, 100);
		v.emplace_back(140, 160);
		v.emplace_back(100, 160);
		v.emplace_back(100, 100);//Y
		fillPolygon(hdc, v, RGB(2, 100, 200));
		v.clear();
		v.emplace_back(240,40);
		v.emplace_back(280,40);
		v.emplace_back(280,80);
		v.emplace_back(320,80);
		v.emplace_back(320,40);
		v.emplace_back(360,40);
		v.emplace_back(360,160);
		v.emplace_back(320,160);
		v.emplace_back(320,120);
		v.emplace_back(280,120);
		v.emplace_back(280,160);
		v.emplace_back(240,160);//H
		fillPolygon(hdc, v, RGB(200, 100, 2));
		v.clear();
		v.emplace_back(400, 40);
		v.emplace_back(440, 40);
		v.emplace_back(440, 120);
		v.emplace_back(520, 120);
		v.emplace_back(520, 160);
		v.emplace_back(400, 160);//L
		fillPolygon(hdc, v, RGB(100, 2, 200));
		v.clear();

		//漫水填色
		for (int i = 40; i<200; i += 40)
			fillDFS(hdc, 700, 200 + 2 * (i - 100), RGB(123, i, 23));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
