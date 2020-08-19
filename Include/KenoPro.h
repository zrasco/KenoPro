/*
** KenoPro.h
**
** This is the header file for the main interface for Keno Pro
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __KENOPRO_H__
#define __KENOPRO_H__

#define _CRTDBG_MAP_ALLOC

#include "../include/Struct.h"
#include <windows.h>
#include <ddraw.h>
#include <crtdbg.h>


/* Game states for Keno Pro */
#define GAME_STATE_STARTUP			1
#define GAME_STATE_STRAIGHT_TICKET	2
#define GAME_STATE_WAY_TICKET		3
#define GAME_STATE_QUICKPICK_TICKET	4
#define	GAME_STATE_PLAYERS_TICKET	5
#define GAME_STATE_SPECIAL_TICKET	6

/* Function prototypes */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* External functions */
extern	void UpdateObjects(GAME_GLOBAL*);

#endif		/* __KENOPRO_H__ */