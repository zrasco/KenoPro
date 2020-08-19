/*
** Struct.h
**
** This header file defines all structures to be used by the game
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <windows.h>
#include <ddraw.h>

#define		MAX_REFCOUNT	100			/* Reference count cant exceed this */
#define		MAX_SURFACES	256			/* # in global table */
#define		MAX_OBJECTS		512			/* Maximum number of game objects */
#define		MAX_GAMESTATES	7			/* Highest game state(+1) */

#define OBJID_INVALID		(DWORD)(-1)
#define OBJID_STATIC		(DWORD)(-2)
#define SURFACEID_INVALID	(DWORD)(-1)

typedef struct GAME_MOUSE_CLICKER
/* Used for mouse click notifications */
{
	unsigned short x;
	unsigned short y;
	BOOL bClicked;
} GAME_MOUSE_CLICKER;

typedef struct GAME_FPS_COUNTER
/* Track the fps of the game with this */
{
	DWORD		dwTime;
	DWORD		dwScopeTime;
	DWORD		dwFPS;
	DWORD		dwDelay;
} GAME_FPS_COUNTER;

typedef struct GAME_SURFACE_TABLE
/* Used for global surfaces */
{
	DWORD		dwSurfaceID;			/* Surface ID # */
	char		*pszBMPPath;			/* Path of bitmap */
	HBITMAP		hBMP;					/* Handle for image bitmap */
	LPDIRECTDRAWSURFACE
				lpdds;					/* Surface pointer */	
} GAME_SURFACE_TABLE;

typedef struct GAME_OBJECT_DIMENSIONS
/* Game object width & height */
{
	unsigned short width;				/* Width */
	unsigned short height;				/* ...and Height */
} GAME_OBJECT_DIMENSIONS;

typedef struct GAME_OBJECT
/* Game object information structure */
{
	tagPOINT	pos[MAX_REFCOUNT];		/* (x,y) position on backbuffer */
	tagPOINT	srcpos[MAX_REFCOUNT];	/* (x,y) position from source surface */
	tagPOINT	lastclick;				/* (x,y) coordinates(object-relative) of last mouse click */

	GAME_OBJECT_DIMENSIONS
				dm[MAX_REFCOUNT];		/* Width & height of frames */
	GAME_OBJECT_DIMENSIONS
				dmresize[MAX_REFCOUNT];	/* Width & height to resize to */
/*
** Game object flags overview
**
** GOF_BLINKER: The object has a blinking effect...
** To achieve this, the dwWorkValue is set to the number of total
** frames in the blink, and the reference count is set to this upon
** reaching 0, creating a loop(the "blink").
**
** GOF_NOTIFY: Lets the program know something...
** With the GOF_NOTIFY flag set, the dwWorkValue is set to the 
** reference count index in which the notify happens(usually 0).
** The program uses this by checking for this flag, and testing
** if the reference count is equal to the work value. If all 3 of these
** conditions are met, the program knows to do something.
** One example of this is a ball dropping, once it is complete the
** game knows to drop the next one.
**
** GOF_BLINKMULTIPLEFRAMES: Multiple frames are used in the blinker...
** With this flag set, blinking is achieved with multiple frames
** of animation. The dwWorkValue is set to the number of frames for
** each frame of object animation, dwWorkValue2 is set to the total 
** number of object animation frames, and dwRefCount & dwRefCount2
** are set to the same. For example, to blink a object with 3
** different animation frames for 15 frames each:
** dwWorkValue = 15; dwWorkValue2 = 3;
** dwRefCount = dwWorkValue; dwRefCount2 = dwRefCount2
**
** GOF_USEFIRSTFRAMEDATA: All animation frames use the same data...
** With this flag set, only index 0 needs x/y width/height src x/y
** data set, as all the surfaces *should* be the same. The ideal
** situation in which to use this flag is when the object is a 
** blinker.
**
** TODO: Add individual flags!!!!! For FIRST FRAME X/Y, WIDTH/HEIGHT, etc....
**
** GOF_CLICKABLE: The object responds to a mouse click...
** Setting this flag enables the object to be clicked, and once
** it is, the NotifyObject() function is called with the click
** notification code set and a pointer to the clicked object.
**
** GOF_TIMEDFRAMES: The object advances frames on a specified delay...
** An object with this flag set will add an extra delay to each frame advancement,
** but can only be used with ordinary objects. dwWorkValue = The number of frames,
** dwWorkValue2 = The delay(in ms).
**
** GOF_MODIFIER: This flag is used by the engine to look up modifier objects in the modifier table,
** This flag is only used by objects which are in the table.
**
** GOF_RESIZE: This flag is used by objects which need to have the dimensions changed on the destination.
** The object will need to have the appropriate dmresize structures filled in.
**
** GOF_SCROLLINGTEXT: This flag is used by scrolling text objects.
** The object will need a surface containing the entire string, and the dimensions will be
** for the visible area only. The text will scroll from right to left by default.
** dwWorkValue2 = The number of pixels to advance each frame.
*/
#define GOF_BLINKER					0x00000001
#define GOF_NOTIFY					0x00000002
#define GOF_BLINKMULTIPLEFRAMES		0x00000004
#define GOF_USEFIRSTFRAMEDATA		0x00000008
#define GOF_CLICKABLE				0x00000010
#define GOF_TIMEDFRAMES				0x00000020
#define GOF_MODIFIER				0x00000040
#define GOF_RESIZE					0x00000080
#define GOF_SCROLLINGTEXT			0x00000100

	DWORD		dwFlags;				/* Object flags */
	DWORD		dwWorkValue;			/* Has various uses */
	DWORD		dwWorkValue2;			/* Has other uses */
	DWORD		dwRefCount;				/* Reference count */
	DWORD		dwRefCount2;			/* Another reference count */
	DWORD		dwID;					/* Object ID */
	DWORD		dwNotifySubCode;		/* Notification sub-sode */

	LPDIRECTDRAWSURFACE 
				lpdds[MAX_REFCOUNT];	/* DD surface pointers */

	struct GAME_GLOBAL 
				*pgg;					/* Game info pointer */
	struct GAME_STATE	
				*pgs;					/* Game state pointer */
	struct GAME_OBJECT 
				*next;					/* Next object in list */

} GAME_OBJECT;

typedef struct GAME_STATE
/* Game state information structure */
{
	unsigned short
				nState;					/* Game state number */

#define GSF_NOTIFY		0x00000001		/* State is transitioning */

	DWORD		dwFlags;				/* State flags */
	DWORD		dwRefCount;				/* Reference count */
	DWORD		dwRefCount2;			/* Second reference count */
	DWORD		dwNotifySubCode;		/* What type of notification is to be done? */
	DWORD		dwWorkValue;			/* Used for general-purpose stuff */
	GAME_OBJECT ObjHead;				/* List of objects */
	GAME_OBJECT ObjDefault;				/* List of default objects */
} GAME_STATE;

typedef struct KENO_TICKET
/* Structure for a keno ticket */
{
	BOOL		bPlayed;					/* This ticket being played? */

#define TICKET_TYPE_QUICKPICK	1
#define TICKET_TYPE_STRAIGHT	2
#define TICKET_TYPE_WAYTICKET	3
#define TICKET_TYPE_SPECIAL		4
#define TICKET_TYPE_PLAYERS		5
	int			nType;						/* Type of ticket */

#define TICKET_SUBTYPE_REGULAR			0
#define TICKET_SUBTYPE_TOPANDBOTTOM		1
#define TICKET_SUBTYPE_LEFTANDRIGHT		2
#define TICKET_SUBTYPE_ODDOREVEN		3
#define TICKET_SUBTYPE_EDGE				4
#define TICKET_SUBTYPE_190WAY8_V		5
#define TICKET_SUBTYPE_190WAY8_B		6
#define TICKET_SUBTYPE_120WAY10			7
#define TICKET_SUBTYPE_108S				8
#define TICKET_SUBTYPE_810S				9
#define TICKET_SUBTYPE_HORIZONTALROWS	10
#define TICKET_SUBTYPE_DEALERSPECIAL	11
#define TICKET_SUBTYPE_VERTICALROWS		12
	int			nSubType;					/* Type of ticket(more specific) */

	int			nBet;						/* Bet amount */
	int			nBetIteration;				/* Bet iteration, in cents(1 cent, 100 cents(1 dollar), etc...) */
	int			nNumbers[22][21];			/* Numbers selected */
	int			nGroupCount;				/* Number of groups */
	GAME_OBJECT	ObjHead;					/* Chain of game objects for ticket */
	GAME_OBJECT
		ObjModifier[MAX_OBJECTS];			/* Table of object modifiers */

} KENO_TICKET;

typedef struct KENO_DATA
/* Structure used for all keno game data */
{
	int		nWon;							/* Money won */
	int		*lpnCredits;					/* Pointer to credits */
	int		nGameCredits;					/* Number of credits in the game */
	int		nDemoCredits;					/* Number of credits in the demo mode */
	int		nActiveTicket;					/* Active ticket number */
	int		nWorkTicket;					/* Temporary work ticket number */
	KENO_TICKET	tickets[10];				/* Game tickets */
	GAME_OBJECT ObjHead;					/* Chain of common game objects */

} KENO_DATA;

typedef struct GAME_GLOBAL
/* Global information structure for game */
{
#define GF_DEMOMODE		0x00000001		/* Game in demo mode? */
#define GF_NOCLICKS		0x00000002		/* No mouse clicks are to be processed */
#define GF_SHUTDOWN		0x00000004		/* Game is shutting down */

	DWORD		dwFlags;				/* Game flags */
	int			nState;					/* Game state */
	unsigned short 
				nBPP;					/* Bits per pixel */
	HINSTANCE	hInstance;				/* Instance handle */
	HWND		hWnd;					/* Handle for main window */
	GAME_STATE	gs[MAX_GAMESTATES];		/* Game state blocks */
	GAME_FPS_COUNTER
				gfc;					/* Game FPS counter */
	GAME_MOUSE_CLICKER
				gmc;					/* Game mouse clicker */

	LPDIRECTDRAW
				lpdd;					/* DirectDraw interface */
	LPDIRECTDRAWSURFACE
				lpddsPrimary;			/* Primary buffer */
	LPDIRECTDRAWSURFACE
				lpddsBackBuffer;		/* Back buffer */
	LPDIRECTDRAWSURFACE
				lpddsBackupBackBuffer;	/* Backup backbuffer(Say that 3 times fast!) */
	GAME_SURFACE_TABLE
				gst[MAX_SURFACES];		/* Global surface table */
	LPDIRECTDRAWSURFACE
				lpddsTemporary[MAX_OBJECTS];
										/* Temporary surfaces used by a few objects */
	LPDIRECTDRAWPALETTE
				lpddpal;				/* DirectDraw palette */

	KENO_DATA	kenodata;				/* Keno data */

} GAME_GLOBAL;

#endif		/* __STRUCT_H__ */