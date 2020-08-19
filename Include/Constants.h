/*
** Constants.h
**
** This header file defines all constants used by Keno Pro
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define MAX_FPS				30

#define SCREEN_HEIGHT		480
#define SCREEN_WIDTH		640
#define SCREEN_BPP			32

/* Macro functions */
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

/* RGB functions */
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

#endif		/* __CONSTANTS_H__ */