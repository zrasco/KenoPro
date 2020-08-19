/*
** KenoPro.cpp
**
** This file contains the interface code used by the game Keno Pro,
** including all DirectX & Windows calls.
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#include "../include/KenoPro.h"
#include "../include/Constants.h"
#include "../include/Struct.h"
#include "../include/Engine.h"

/* Global variables */
GAME_GLOBAL	*pgg;							/* Main game info */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
/*
** WinMain()
** This function is the entry point for Keno Pro
*/
{
	WNDCLASSEX wc;
	MSG Msg;

	/* Turn on debug CRT */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_DELAY_FREE_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	/* Register main window structure */
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "KENOPRO";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	/* Big trouble here */
	{
		MessageBox(NULL,"Unable to register main window.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	/* Initialize game global object */
	pgg = (GAME_GLOBAL*)calloc(1,sizeof(GAME_GLOBAL));

	pgg->hInstance = hInstance;

	pgg->hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		wc.lpszClassName,
		"Keno Pro",
		WS_POPUP | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		200,
		200,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!pgg->hWnd)
	/* Another trouble situation */
	{
		MessageBox(NULL,"Unable to create main window.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	/* Start our window maximized, since we'll be running in full screen */
	ShowWindow(pgg->hWnd, SW_MAXIMIZE);
	UpdateWindow(pgg->hWnd);

	/* Initialize game */
	if (!KP_Initialize(pgg))
	/* Unable to start game */
		return 0;

	SetActiveWindow(pgg->hWnd);
	SetForegroundWindow(pgg->hWnd);
	GetFocus();

	while (TRUE)
	/* The message pump */
	{
		if (PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
		/* Check messages */
		{
			if (Msg.message == WM_QUIT)
				break;

			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		if (KP_Loop(pgg) == -1)
		/* Game over */
			DestroyWindow(pgg->hWnd);

		UpdateObjects(pgg);
	}

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
/*
** WndProc()
** This is the callback function for the main window
*/
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;
		case WM_DESTROY:
		{
			KP_Shutdown(pgg);
			PostQuitMessage(0);
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			unsigned int xPos = LOWORD(lParam), yPos = HIWORD(lParam);

			KP_Click(pgg,xPos,yPos);
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}
	
	return 0;
}
