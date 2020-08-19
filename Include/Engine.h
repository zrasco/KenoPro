/*
** Engine.h
**
** This header file contains all declarations for the Keno Pro engine
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <ddraw.h>
#include "Struct.h"

/* Macro functions */
#define KP_GETBMPSIZE(pgg, sid, width, height)			\
	{													\
		BITMAP _bm;										\
		GetObject(pgg->gst[sid].hBMP,sizeof(_bm),&_bm);	\
		height = (unsigned short)(_bm.bmHeight + 1); width = (unsigned short)(_bm.bmWidth + 1);		\
	}													\

#define ZERO_OUT(var)	memset(&var,0,sizeof(var))


/* Engine functions */
int		KP_Initialize(GAME_GLOBAL*);
int		KP_Loop(GAME_GLOBAL*);
int		KP_Shutdown(GAME_GLOBAL*);
int		KP_Click(GAME_GLOBAL*, unsigned short,unsigned short);


GAME_OBJECT 
		*KP_AddObject(GAME_GLOBAL*, GAME_OBJECT*, unsigned short, GAME_OBJECT*);
GAME_OBJECT
		*KP_FindObject(GAME_GLOBAL*, GAME_OBJECT*, DWORD);
void
		KP_RemoveObjectPtr(GAME_GLOBAL*, GAME_OBJECT*, GAME_OBJECT*);
void
		KP_RemoveObject(GAME_GLOBAL*, GAME_OBJECT*, DWORD);
GAME_OBJECT
		*KP_InsertObject(GAME_GLOBAL*, GAME_OBJECT*, unsigned short, GAME_OBJECT*, GAME_OBJECT*);

void	KP_FillSurface(LPDIRECTDRAWSURFACE, unsigned int);

HRESULT
		KP_CreateSurfaceFromBitmap(GAME_GLOBAL*, LPDIRECTDRAWSURFACE*, HBITMAP*, char*);
HRESULT KP_CreateBlankSurface(GAME_GLOBAL*, LPDIRECTDRAWSURFACE*, unsigned int, unsigned int, unsigned int);

HRESULT KP_DrawBitmapOnSurface(LPDIRECTDRAWSURFACE, HBITMAP,
                              DWORD, DWORD, 
                              DWORD, DWORD);
int		KP_FadeSurface_32BPP(LPDIRECTDRAWSURFACE, int);
int		KP_FadeSurface_24BPP(LPDIRECTDRAWSURFACE, int);
int		KP_FadeSurface(GAME_GLOBAL*, LPDIRECTDRAWSURFACE, int);
void	KP_ODS(char*, ...);

/* Structures used in engine-specific tasks */
typedef struct LookupLevel
{
	unsigned __int8 Values[256];
} LookupLevel;

typedef struct LookupTable
{
	LookupLevel Levels[256];
} LookupTable;

typedef struct ColorChannels
{
	unsigned __int8 Blue;
	unsigned __int8 Green;
	unsigned __int8 Red;
	unsigned __int8 Alpha;
} ColorChannels;

union Pixel32
{
	ColorChannels Channels;
	__int32 Value;
};

/* Alpha blending effects */
__inline unsigned __int8 clipByte(int);
int InitAlphaTable();
__inline LookupLevel *LookupPointer(int);
__inline __int32 AlphaBlend(Pixel32, Pixel32, __int32);
__int32 SubtractiveBlend(Pixel32, Pixel32, __int32);
__int32 AdditiveBlend(Pixel32, Pixel32, __int32);

/* User-supplied functions */
extern	HRESULT SetupObjects(GAME_GLOBAL*);
extern	void DestroyObjects(GAME_GLOBAL*);
extern	int NotifyObject(GAME_OBJECT*, unsigned short, unsigned int);

/* #define's used by the engine */
#define NOTIFY_CODE_CLICK 1
#define NOTIFY_CODE_REFERENCE 2

#endif		/* __ENGINE_H__ */