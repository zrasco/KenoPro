/*
** Engine.cpp
**
** This file implements all functions of the Keno Pro engine.
** The KP engine is based on DirectX, although it can be modified
** to use something else(such as GDI). The DirectX is built into
** the game objects(animation frames, primary & backbuffers, etc),
** the KP startup & shutdown routines, and the renderer.
**
** The following items must be declared outside the engine itself
**
** #defines:
** SCREEN_HEIGHT			Vertical resolution, in pixels
** SCREEN_WIDTH				Horizontal resolution, in pixels
** SCREEN_BPP				Color depth(Bits Per Pixel)
** MAX_FPS					Maximum allowed FPS
**
** Functions(these must be supplied by the programmer):
** 1) BOOL SetupObjects(GAME_GLOBAL *pgg)
** This function will take the pointer to the game info block and
** add all game states & objects to all game states. The renderer
** will only draw those objects are in the current game state &
** are visible.
** 2) void DestroyObjects(GAME_GLOBAL *pgg)
** This function is the opposite of #1, here is where all the objects
** and game state data are deallocated.
**
** 3) int NotifyObject(GAME_OBJECT *pgo, unsigned short nState, unsigned int code)
** This function is called whenever an object recieves a notice of some type, a good example is a mouse click.
**
** 4) void UpdateObjects(GAME_GLOBAL *pgg)
** This function can optionally called after the loop to automatically update objects such
** as text, bet meters, etc... which amounts or text have been changed by player action.
** 
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#include "../include/KenoPro.h"
#include "../include/Engine.h"
#include "../include/Constants.h"
#include "../include/Objects.h"

/* Lookup tables */
unsigned char rgb_pct[100][256];
LookupTable at;
LookupLevel *SourceTable;
LookupLevel *DestTable;
GAME_OBJECT *pgoNotify = NULL;

int	KP_Initialize(GAME_GLOBAL *pgg)
/*
** KP_Initialize()
** This is the entry point for the KP engine, sets up all states &
** game objects.
*/
{
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	DDCOLORKEY col_key;
	HRESULT hr;
	int count, count2;
	
	memset(&ddsd,0,sizeof(ddsd)); ddsd.dwSize = sizeof(ddsd);

	/* Create lookup tables */
	for (count = 0; count < 256; count++)
	{
		for (count2 = 0; count2 < 100; count2++)
		{
			rgb_pct[count2][count] = (unsigned char)((float)count2 / (float)100 * count);
		}
	}

	InitAlphaTable();

	if (DirectDrawCreate(NULL,&pgg->lpdd,NULL) != DD_OK)
	/* Create our main DirectDraw object */
	{
		MessageBox(pgg->hWnd,"Unable to create DirectDraw object.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	/* Set cooperative mode & display resolution */
	pgg->lpdd->SetCooperativeLevel(pgg->hWnd,
		DDSCL_ALLOWMODEX |
		DDSCL_FULLSCREEN |
		DDSCL_EXCLUSIVE |
		DDSCL_ALLOWREBOOT);

	pgg->nBPP = SCREEN_BPP;

	if (pgg->lpdd->SetDisplayMode(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		pgg->nBPP) != DD_OK)
	/* Unable to set resolution to 640x480x32 */
	{
		/* Try again, with 24-bit color instead */
		pgg->nBPP = 24;

		if (pgg->lpdd->SetDisplayMode(
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			pgg->nBPP) != DD_OK)
		{
			MessageBox(pgg->hWnd,"Unable to set resolution.","Fatal Error",MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	/* Setup primary, backbuffer, and backup backbuffer surfaces */
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = 
		DDSCAPS_PRIMARYSURFACE |
		DDSCAPS_FLIP |
		DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;

	if (pgg->lpdd->CreateSurface(&ddsd,&pgg->lpddsPrimary,NULL) != DD_OK)
	/* Unable to create primary surface */
	{
		MessageBox(pgg->hWnd,"Unable to create primary surface.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	/* Get backbuffer surface */
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

	if (pgg->lpddsPrimary->GetAttachedSurface(&ddscaps,&pgg->lpddsBackBuffer)
		!= DD_OK)
	{
		MessageBox(pgg->hWnd,"Unable to create backbuffer surface.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth        = SCREEN_WIDTH;
    ddsd.dwHeight       = SCREEN_HEIGHT;

	if ((pgg->lpdd->CreateSurface(&ddsd,&pgg->lpddsBackupBackBuffer,NULL) != DD_OK))
	/* Unable to create backup backbuffer surface */
	{
		MessageBox(pgg->hWnd,"Unable to create backup backbuffer surface.","Error",MB_OK);
		return hr;
	}

	/* Set transparency key for backbuffer */
	col_key.dwColorSpaceLowValue = 0;
	col_key.dwColorSpaceHighValue = 0;

	pgg->lpddsBackBuffer->SetColorKey(DDCKEY_SRCBLT,&col_key);

	/* The "work ticket"(temporary ticket) will be stored as ticket #9 */
	pgg->kenodata.nWorkTicket = 9;

	/* Set up all user-defined objects */
	if (FAILED(hr = SetupObjects(pgg)))
	{
		MessageBox(pgg->hWnd,"Unable to set up game objects.","Fatal Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	/* Initialize the RNG */
	srand(GetTickCount());

	/* Finally, lock in the FPS delay threshold */
	pgg->gfc.dwDelay = 1000 / MAX_FPS;

	ShowCursor(TRUE);

	return 1;
}
int	KP_Loop(GAME_GLOBAL *pgg)
/*
** KP_Loop()
** Performs all rendering and frame calculation for Keno Pro
*/
{
	int count, x = 0, y = 0, refcount, refcount2, nStateF = pgg->nState;
	BOOL bMouseClick = FALSE, bMouseProcessed = FALSE;
	BOOL bSkip = FALSE, bSkipTransition = FALSE;
	GAME_OBJECT *temp, *curr = NULL;
	RECT SrcRect, DestRect, ExtraRect[4];
	DDBLTFX ddbltfx;
	DDSURFACEDESC ddsd;
	HRESULT hr = NULL;

	if (pgg->dwFlags & GF_SHUTDOWN)
		return 0;

	memset(&ddbltfx,0,sizeof(&ddbltfx)); ddbltfx.dwSize = sizeof(ddbltfx);
	memset(&ddsd,0,sizeof(ddsd)); ddsd.dwSize = sizeof(ddsd);
	memset(&ExtraRect,0,sizeof(ExtraRect));

	/* Lock in fixed FPS */
	pgg->gfc.dwScopeTime = GetTickCount();

	if (GetTickCount() - 1000 >= pgg->gfc.dwTime)
	/* One second has elapsed */
	{
		char buf[256];

		sprintf(buf,"FPS=%d\n",pgg->gfc.dwFPS);
		pgg->gfc.dwFPS = 0;
		pgg->gfc.dwTime = GetTickCount();

		OutputDebugString(buf);
	}

	/* Check for mouse clicks */
	if (pgg->gmc.bClicked)
	{
		bMouseClick = TRUE;
		x = pgg->gmc.x; y = pgg->gmc.y;
	}

	/* Clear backbuffer */
	ddbltfx.dwFillColor = 0;
	pgg->lpddsBackupBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);

	/*
	** The objects will be rendered in the following order:
	** 1) Objects which are on every ticket(except during the startup screen)
	** 2) All default objects for that game state(Quick pick buttons, for example)
	** 3) Objects added to tickets during game play(X's on tickets, etc...)  
	*/

	for (count = 0; count <= 2; count++)
	{
		if (count == 0)
		/* Pass #1: Render objects which are on every ticket(except during the startup screen). */
		{
			if (pgg->nState == GAME_STATE_STARTUP)
			/* On the startup screen, skip this step */
				continue;
			else
				curr = &(pgg->kenodata.ObjHead);
		}
		else if (count == 1)
		/* Pass #2: Render all default objects */
			curr = &(pgg->gs[pgg->nState].ObjDefault);
		else if (count == 2)
		/* Pass #3: Render all objects added to tickets */
			curr = &(pgg->gs[pgg->nState].ObjHead);

		while (curr->next)
		/* Render all objects to backbuffer */
		{
			curr = curr->next;

			if (bMouseClick &&
				(!(pgg->dwFlags & GF_NOCLICKS)) &&
				(curr->dwFlags & GOF_CLICKABLE) &&
				(x >= curr->pos[0].x && x <= curr->pos[0].x + curr->dm[0].width) &&
				(y >= curr->pos[0].y && y <= curr->pos[0].y + curr->dm[0].height))
			/* A mouse click occured on a clickable object */
			{
				/* The engine has done its work, pass it on to the developers' notifcation function */
				curr->lastclick.x = x - curr->pos[0].x; curr->lastclick.y = y - curr->pos[0].y;

				/* KP_ODS("Mouse click at (%d,%d)",curr->lastclick.x,curr->lastclick.y); */

				if (NotifyObject(curr,(unsigned short)pgg->nState,NOTIFY_CODE_CLICK) == -2)
					bSkip = TRUE;

				pgg->gmc.bClicked = FALSE; bMouseProcessed = TRUE;
			}

			/* Check in the modifier table for this object */
			if (curr->dwID != OBJID_STATIC && curr->dwID != OBJID_INVALID)
			{
				temp = &(pgg->kenodata.tickets[pgg->kenodata.nWorkTicket].ObjModifier[curr->dwID]);

				if (curr->dwID < 0 || curr->dwID > 100)
				{
					KP_ODS("nState==%d,pgg->nState==%d",pgg->nState,pgg->nState);
					KP_ODS("Checking modifier table: temp==0x%x,curr->dwID==%d,curr==0x%x,&pgg->gs[pgg->nState].ObjHead.next==%x",temp,curr->dwID,curr,&pgg->gs[pgg->nState].ObjHead.next);
				}

				if (temp->dwFlags & GOF_MODIFIER)
				/* This object has a modifier associated with it */
				{
					/* Switch current object pointer with modifier */
					temp->next = curr->next;
					curr = temp;
				}
			}

			if (curr->dwFlags & GOF_BLINKMULTIPLEFRAMES)
				refcount = curr->dwRefCount2;
			else
				refcount = curr->dwRefCount;

			if (curr->lpdds[refcount])
			/* Process this frame */
			{
				/* Save old reference count */
				refcount2 = refcount;

				if (curr->dwFlags & GOF_USEFIRSTFRAMEDATA)
					refcount = 0;
					
				/* Set destination rectangle */
				DestRect.top = curr->pos[refcount].y;
				DestRect.left = curr->pos[refcount].x;

				if (curr->dwFlags & GOF_SCROLLINGTEXT)
				/* Scrolling text object */
				{
					/* TEMP: Set threshold manually here */
					int threshold = 120;
					BOOL bOffsetDest = FALSE;

					refcount = 0;

					if (curr->srcpos[refcount].x < 0)
						bOffsetDest = TRUE;

					/* dmresize is the dimensions of the displayed text */
					DestRect.bottom = DestRect.top + curr->dmresize[refcount].height - 1;
					DestRect.right = DestRect.left + curr->dmresize[refcount].width - 1;

					if (bOffsetDest == TRUE)
					/* Bump the text up a little bit */
						DestRect.left += (0 - (curr->srcpos[refcount].x));

					/* Source rectangle(First) */
					SrcRect.top = curr->srcpos[refcount].y;
					SrcRect.bottom = SrcRect.top + curr->dmresize[refcount].height - 1;

					SrcRect.left = curr->srcpos[refcount].x;

					if (curr->srcpos[refcount].x + curr->dmresize[refcount].width > 
						curr->dm[refcount].width)
					/* Blit only a portion */
					{
						SrcRect.right = curr->dm[refcount].width - 1;
						DestRect.right = DestRect.left + (SrcRect.right - SrcRect.left) - 1;

						if ((SrcRect.right - SrcRect.left) + threshold <
							curr->dmresize[refcount].width)
						/* 
						** In this case, we will be blitting 2 rectangles, so to let
						** the blitter know this, we will set dwRefCount2 to -1,
						** ExtraRect[0] as the source rectangle, and ExtraRect[1] as the
						** destination rectangle.
						*/
						{
							curr->dwRefCount2 = (DWORD)(-1);

							ExtraRect[0].left = 0;
							ExtraRect[0].right = (curr->dmresize[refcount].width - 
								((SrcRect.right - SrcRect.left) + threshold)) - 1;
							ExtraRect[0].top = SrcRect.top; ExtraRect[0].bottom = SrcRect.bottom;

							ExtraRect[1].left = curr->pos[refcount].x + (SrcRect.right - SrcRect.left) +
								threshold;
							ExtraRect[1].right = curr->pos[refcount].x + curr->dmresize[refcount].width;
							ExtraRect[1].top = DestRect.top; ExtraRect[1].bottom = DestRect.bottom;

						}

					}
					else
					/* Regular blit */
					{
						if (bOffsetDest == FALSE)
						{
							SrcRect.left = curr->srcpos[refcount].x;
							SrcRect.right = SrcRect.left + curr->dmresize[refcount].width - 1;

						}
						else
						{
							SrcRect.left = 0;
							SrcRect.right = curr->dmresize[refcount].width + curr->srcpos[refcount].x;
						}
					}

					curr->srcpos[refcount].x += curr->dwWorkValue2;

					if (curr->srcpos[refcount].x >= curr->dm[0].width)
						curr->srcpos[refcount].x = 0 - threshold;
					

				}
				else
				{
					if (curr->dwFlags & GOF_RESIZE)
					/* The object needs to be resized */
					{
						DestRect.bottom = DestRect.top + curr->dmresize[refcount].height - 1;
						DestRect.right = DestRect.left + curr->dmresize[refcount].width - 1;
					}
					else
					/* Use the default size */
					{
						DestRect.bottom = DestRect.top + curr->dm[refcount].height - 1;
						DestRect.right = DestRect.left + curr->dm[refcount].width - 1;
					}

					/* And source rectangle */
					SrcRect.top = curr->srcpos[refcount].y;
					SrcRect.bottom = SrcRect.top + curr->dm[refcount].height - 1;
					SrcRect.left = curr->srcpos[refcount].x;
					SrcRect.right = SrcRect.left + curr->dm[refcount].width - 1;
				}

				/* Restore old reference count */
				refcount = refcount2;

				/* Draw the image to the backbuffer */
				hr = pgg->lpddsBackupBackBuffer->Blt(&DestRect,curr->lpdds[refcount],&SrcRect,DDBLT_WAIT | DDBLT_KEYSRC, &ddbltfx);

				if (FAILED(hr))
				{
					int count;

					DDSURFACEDESC ddsd;

					ddsd.dwSize = sizeof(ddsd);
					ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
					
					curr->lpdds[refcount]->GetSurfaceDesc(&ddsd);


					KP_ODS("Unable to Blt OID#%i, error #%x",curr->dwID,(unsigned int)hr);
					KP_ODS("d(t=%d,l=%d,b=%d,r=%d),s(t=%d,l=%d,b=%d,r=%d)",
						DestRect.top,
						DestRect.left,
						DestRect.bottom,
						DestRect.right,
						SrcRect.top,
						SrcRect.left,
						SrcRect.bottom,
						SrcRect.right);

					for (count = 0; count < MAX_SURFACES; count++)
					{
						if (pgg->gst[count].lpdds == curr->lpdds[refcount])
						{
							KP_ODS("Object SID==%d, refcount==%d",count,refcount);
							break;
						}
					}

					KP_ODS("surface h/w=%dx%d",ddsd.dwHeight,ddsd.dwWidth);
					pgg->lpddsBackBuffer->GetSurfaceDesc(&ddsd);
				}

				if (curr->dwFlags & GOF_SCROLLINGTEXT && curr->dwRefCount2 == (DWORD)(-1))
				/* Blit second rectangle for scrolling text object */
				{
					/* Draw the image to the backbuffer */
					hr = pgg->lpddsBackupBackBuffer->Blt(&ExtraRect[1],curr->lpdds[refcount],&ExtraRect[0],DDBLT_WAIT | DDBLT_KEYSRC, &ddbltfx);

					curr->dwRefCount2 = 0;

					if (FAILED(hr))
					{
						int count;

						KP_ODS("Unable to Blt second part of OID#%i, error #%x",curr->dwID,(unsigned int)hr);
						KP_ODS("d(t=%d,l=%d,b=%d,r=%d),s(t=%d,l=%d,b=%d,r=%d)",
							ExtraRect[1].top,
							ExtraRect[1].left,
							ExtraRect[1].bottom,
							ExtraRect[1].right,
							ExtraRect[0].top,
							ExtraRect[0].left,
							ExtraRect[0].bottom,
							ExtraRect[0].right);
					}					
				}
			}

			if (curr->dwFlags & GOF_TIMEDFRAMES)
			/* Object is on a timed frame advance */
			{
				DWORD time = GetTickCount();

				if (!curr->dwRefCount2)
				/* First frame */
				{
					curr->dwRefCount2 = time;

					/* Don't advance this frame yet */
					continue;
				}

				else if (time - curr->dwWorkValue2 < curr->dwRefCount2)
				/* Don't advance this frame yet */
					continue;
				else
				/* The frame will be advanced below, so update the information */
				{
					curr->dwRefCount2 = time;
				}

			}

			if ((curr->dwFlags & GOF_BLINKMULTIPLEFRAMES)
				&& (curr->dwFlags & GOF_BLINKER))
			/* Blinker with multiple frames */
			{
				curr->dwRefCount--;

				if (!curr->dwRefCount)
				/* Next blink frame */
				{
					if (!curr->dwRefCount2)
					/* Loop back to beginning of blink */
						curr->dwRefCount2 = curr->dwWorkValue2 - 1;
					else
					/* Decrease secondary reference count */
						curr->dwRefCount2--;

					/* Next blink frame, reset reference count */
					curr->dwRefCount = curr->dwWorkValue;
				}
			}
			else if (!bSkip)
			{
				if (curr->dwRefCount)
				/* Decrement reference count */
				{
					curr->dwRefCount--;
				}
				else
				/* Reference count is 0 */
				{
					if (curr->dwFlags & GOF_BLINKER)
					/* Roll over the blinker loop */
						curr->dwRefCount = curr->dwWorkValue;
					else if (curr->dwFlags & GOF_NOTIFY)
					/* Let the developer know what's up */
					{
						if (NotifyObject(curr,(unsigned short)pgg->nState,NOTIFY_CODE_REFERENCE) == -3)
						{
							bSkipTransition = TRUE;
							KP_ODS("Skipping transition");
						}

					}
				}
			}
		}
	}

	/* Frame created, now perform screen transition effects */
	if (!bSkipTransition && pgg->gs[pgg->nState].dwFlags & GSF_NOTIFY)
	{
		KP_ODS("In transition effect, pgg->nState==%d",pgg->nState);

		if (pgg->gs[pgg->nState].dwNotifySubCode == GSNSC_FADEOUT ||
			pgg->gs[pgg->nState].dwNotifySubCode == GSNSC_FADEIN)
		{
			if (pgg->gs[pgg->nState].dwRefCount)
			{
				HRESULT hr = NULL;
				long tc;
				int alpha = (int)(255 * (float)pgg->gs[pgg->nState].dwRefCount / (float)pgg->gs[pgg->nState].dwRefCount2);
				RECT rect;

				pgg->gs[pgg->nState].dwRefCount--;

				if (pgg->gs[pgg->nState].dwNotifySubCode == GSNSC_FADEIN)
					alpha = 255 - alpha;

				/* Fade the backup backbuffer */
				KP_FadeSurface(pgg,pgg->lpddsBackupBackBuffer,alpha);
			}
			else
			/* Time to perform switch */
			{
				int nOldState = pgg->nState;

				if (pgg->gs[pgg->nState].dwNotifySubCode == GSNSC_FADEOUT)
				/* Screen is completley faded out */
				{
					pgg->nState = pgg->gs[nOldState].dwWorkValue;

					if (nOldState == GAME_STATE_STARTUP)
					{
						/* Transfer changes to the work ticket */
						memcpy(&pgg->kenodata.tickets[pgg->kenodata.nWorkTicket],&pgg->kenodata.tickets[pgg->kenodata.nActiveTicket],sizeof(pgg->kenodata.tickets[pgg->kenodata.nActiveTicket]));

						//						pgg->gs[pgg->nState].ObjHead.next = pgg->kenodata.tickets[pgg->kenodata.nWorkTicket].ObjHead.next;

						CreateTicketSpecificObjects(pgg,&pgg->kenodata.tickets[pgg->kenodata.nWorkTicket]);

						pgg->gs[pgg->nState].ObjHead.next = pgg->kenodata.tickets[pgg->kenodata.nWorkTicket].ObjHead.next;


					}

					/* Clear backbuffer */
					ddbltfx.dwFillColor = 0;
					pgg->lpddsBackupBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
				}
				else
				/* Screen has completed fade-in */
				{
					pgg->dwFlags ^= GF_NOCLICKS;
				}

				pgg->gs[nOldState].dwFlags ^= GSF_NOTIFY;
				pgg->gs[nOldState].dwNotifySubCode = 0;
				pgg->gs[nOldState].dwRefCount2 = pgg->gs[nOldState].dwRefCount = 0;
				pgg->gs[nOldState].dwWorkValue = 0;
			}
		}
	}

	/* Copy the backup backbuffer to the backbuffer */
	hr = pgg->lpddsBackBuffer->BltFast(0,0,pgg->lpddsBackupBackBuffer,NULL, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

	/* Flip the primary & backbuffer */
	while (pgg->lpddsPrimary->Flip(NULL,DDFLIP_WAIT) != DD_OK);

	if (!bMouseProcessed)
	/* Discard the mouse click if no object captured it */
	{
		pgg->gmc.x = 0;
		pgg->gmc.y = 0;
		pgg->gmc.bClicked = FALSE;
	}

	/* Lock in fixed FPS */
	while (GetTickCount() - pgg->gfc.dwDelay < pgg->gfc.dwScopeTime)
	{
		if (KEY_DOWN(VK_ESCAPE))
		/* User is exiting */
			return -1;
	}

	pgg->gfc.dwFPS++;

	return 0;
}

int	KP_Shutdown(GAME_GLOBAL *pgg)
/*
** KP_Shutdown()
** This is called when the game is going to shutdown, it frees up
** all used resources.
*/
{
	int count;

	for (count = 0; pgg->gst[count].lpdds != NULL; count++)
	/* Release surfaces in surface table */
	{
		pgg->gst[count].lpdds->Release();
		pgg->gst[count].lpdds = NULL;
	}

	if (pgg->lpddsBackupBackBuffer)
	/* Release backup backbuffer surface */
		pgg->lpddsBackupBackBuffer->Release();

	if (pgg->lpddsBackBuffer)
	/* Release backbuffer surface */
		pgg->lpddsBackBuffer->Release();

	if (pgg->lpddsPrimary)
	/* Release primary surface */
		pgg->lpddsPrimary->Release();

	if (pgg->lpdd)
	/* Release our DD object */
		pgg->lpdd->Release();

	pgg->lpddsBackupBackBuffer = NULL;
	pgg->lpddsBackBuffer = NULL;
	pgg->lpddsPrimary = NULL;
	pgg->lpdd = NULL;

	pgg->dwFlags |= GF_SHUTDOWN;

	//free(pgg);
	//pgg = NULL;
	return 0;
}

int	KP_Click(GAME_GLOBAL *pgg, unsigned short x,unsigned short y)
/*
** KP_Click()
** This function is to be called by the system when a mouse click occurs
*/
{
	if (!pgg->gmc.bClicked)
	/* Only process the first click */
	{
		pgg->gmc.x = x; pgg->gmc.y = y; pgg->gmc.bClicked = TRUE;
	}

	return 0;
}

GAME_OBJECT *KP_AddObject(GAME_GLOBAL *pgg, GAME_OBJECT *pgoListHead, unsigned short nState, GAME_OBJECT *pgoInfo)
/*
** KP_AddObject()
** Adds an object to the specified game state object chain,
** using the game object pointer as the data to add.
** Returns: NULL if failed, or a pointer to the object added.
**
** NOTE: The objects are rendered from the first object to the last
** (i.e., the last object is in the foreground)
** Also note that while the engine allows multiple instances of an
** object with the same ID #, they cannot be in the same game state.
*/
{
	int count;
	GAME_OBJECT *curr;


	curr = pgoListHead;

	if (!curr || nState > MAX_GAMESTATES)
		return NULL;

	while (curr->next)
	/* Find end of object chain */
	{
		curr = curr->next;

		if (pgoInfo->dwID != OBJID_STATIC &&
			curr->dwID == pgoInfo->dwID)
		/* Object with ID # exists */
		{
			KP_ODS("KP_AddObject failed! curr->dwID == pgoInfo->dwID == %d",curr->dwID);
			return NULL;
		}
	}

	/* Create new object at end */
	curr->next = (GAME_OBJECT*)calloc(1,sizeof(GAME_OBJECT));	
	curr = curr->next;

	if (curr == NULL)
	/* Allocation error */
		return curr;

	/* Execute field-by-field copy of structure */
	curr->dwFlags = pgoInfo->dwFlags;
	curr->dwID = pgoInfo->dwID;
	curr->dwRefCount = pgoInfo->dwRefCount;
	curr->dwRefCount2 = pgoInfo->dwRefCount2;
	curr->dwWorkValue = pgoInfo->dwWorkValue;
	curr->dwWorkValue2 = pgoInfo->dwWorkValue2;

	for (count = 0; count < MAX_REFCOUNT; count++)
	/* Copy over all values */
	{
		curr->dm[count].height = pgoInfo->dm[count].height;
		curr->dm[count].width = pgoInfo->dm[count].width;
		curr->dmresize[count].height = pgoInfo->dmresize[count].height;
		curr->dmresize[count].width = pgoInfo->dmresize[count].width;
		curr->lpdds[count] = pgoInfo->lpdds[count];
		curr->pos[count].x = pgoInfo->pos[count].x;
		curr->pos[count].y = pgoInfo->pos[count].y;
		curr->srcpos[count].x = pgoInfo->srcpos[count].x;
		curr->srcpos[count].y = pgoInfo->srcpos[count].y;
	}

	/* Copy over the appropriate values for the rest */
	curr->pgg = pgg;
	curr->pgs = &(pgg->gs[nState]);
	curr->next = NULL;

	return curr;
}

GAME_OBJECT *KP_FindObject(GAME_GLOBAL *pgg, GAME_OBJECT *pgoListHead, DWORD dwID)
/*
** KP_FindObject()
** Finds the object with the specified ID in the list
*/
{
	GAME_OBJECT *curr = pgoListHead;

	while (curr->next)
	/* Find target object */
	{
		curr = curr->next;

		if (curr->dwID == dwID)
		/* Gotcha! */
			return curr;
	}

	return NULL;
}

void KP_RemoveObjectPtr(GAME_GLOBAL *pgg, GAME_OBJECT *pgoListHead, GAME_OBJECT *pgoTarget)
/*
** KP_RemoveObjectPtr()
** Removes the specified object from the object chain, using the pointer as the
** object to remove.
** NOTE: All pointers inside must be de-allocated!!
*/
{
	GAME_OBJECT *prev, *curr = pgoListHead;

	int test = 0;

	prev = curr;

	while (curr->next)
	/* Find target object */
	{
		test++;

		curr = curr->next;

		if (curr == pgoTarget)
		/* Gotcha! Remove from list and de-allocate */
		{
			prev->next = curr->next;

			ZERO_OUT(*curr);
			free(curr);
			curr = NULL;

			return;
		}

		prev = curr;
	}

	return;

}

void KP_RemoveObject(GAME_GLOBAL *pgg, GAME_OBJECT *pgoListHead, DWORD dwID)
/*
** KP_RemoveObject()
** Removes the specified object from the object chain with the game
** state specified.
** NOTE: All pointers in structures must be de-allocated first!!
*/
{
	GAME_OBJECT *prev, *curr = pgoListHead;

	prev = curr;

	while (curr->next)
	/* Find target object */
	{
		curr = curr->next;

		if (curr->dwID == dwID)
		/* Gotcha! Remove from list and de-allocate */
		{
			prev->next = curr->next;

			curr->next = NULL;
			free(curr);
			curr = NULL;

			return;
		}

		prev = curr;
	}

	return;
}

GAME_OBJECT *KP_InsertObject(GAME_GLOBAL *pgg, GAME_OBJECT *pgoListHead, unsigned short nState, GAME_OBJECT *pgoPrevious, GAME_OBJECT *pgoInfo)
/*
** KP_InsertObject()
** Works just like KP_AddObject, except it inserts it after the specified
** object in the chain. Object is inserted right after pgoPrevious!
** Returns: NULL if error, otherwise pointer to newly inserted object
*/
{
	GAME_OBJECT *pgoNew = KP_AddObject(pgg,pgoListHead,nState,pgoInfo);

	if (pgoNew)
	/* Insert at end of the list */
	{
		GAME_OBJECT *curr = pgoListHead;

		while (curr->next)
		/* Get the node prior to the end object */
		{
			curr = curr->next;

			if (curr->next == pgoNew)
			/* Got it! Remove from end of list and insert it at the insertion point */
			{
				curr->next = NULL;
				pgoNew->next = pgoPrevious->next;
				pgoPrevious->next = pgoNew;
				break;
			}
		}
	}

	return pgoNew;
}

HRESULT KP_CreateSurfaceFromBitmap(GAME_GLOBAL *pgg, LPDIRECTDRAWSURFACE *lplpdds, HBITMAP *lphBMP, char *pszBitmap)
/*
** KP_CreateSurfaceFromBitmap()
** Loads a bitmap into memory and creates a surface with the characteristics of it
** Returns: The result of the surface creation
*/
{
    HRESULT        hr;
    HBITMAP        hBMP = NULL;
    BITMAP         bmp;
    DDSURFACEDESC ddsd;
	LPDIRECTDRAWSURFACE lpdds = NULL;
	DDCOLORKEY	   col_key;

    //  Try to load the bitmap as a resource, if that fails, try it as a file
    hBMP = (HBITMAP) LoadImage( GetModuleHandle(NULL), pszBitmap, 
                                IMAGE_BITMAP, 0, 0, 
                                LR_CREATEDIBSECTION );
    if( hBMP == NULL )
    {
        hBMP = (HBITMAP) LoadImage( NULL, pszBitmap, 
                                    IMAGE_BITMAP, 0, 0, 
                                    LR_LOADFROMFILE | LR_CREATEDIBSECTION );
        if( hBMP == NULL )
		{
			char buf[256];

			sprintf(buf, "LoadImage() failed on bitmap %s",pszBitmap);
			MessageBox(pgg->hWnd,buf,"Error",MB_OK);
            return NULL;
		}
    }

    // Get size of the bitmap
    GetObject( hBMP, sizeof(bmp), &bmp );

    // Create a DirectDrawSurface for this bitmap
    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    //ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth        = bmp.bmWidth;
    ddsd.dwHeight       = bmp.bmHeight;

	if (hr = (pgg->lpdd->CreateSurface(&ddsd,&lpdds,NULL) != DD_OK))
	{
		MessageBox(pgg->hWnd,"CreateSurface() failed","Error",MB_OK);
		return hr;
	}

	/* Set the transparency key of this surface */
	col_key.dwColorSpaceLowValue = 0;
	col_key.dwColorSpaceHighValue = 0;

	lpdds->SetColorKey(DDCKEY_SRCBLT,&col_key);

    // Draw the bitmap on this surface
    if( FAILED( hr = KP_DrawBitmapOnSurface(lpdds,hBMP,0,0,0,0) ) )
    {
		MessageBox(pgg->hWnd,"KP_DrawBitmapOnSurface() failed","Error",MB_OK);
        DeleteObject( hBMP );
        return hr;
    }

	if (lphBMP == NULL)
		DeleteObject( hBMP );
	else
	/* Leave it up to the caller to work with the bitmap handle afterwords */
		*lphBMP = hBMP;

	/* Return result & fill in passed pointer to surface pointer */
	*lplpdds = lpdds;

    return DD_OK;
}

HRESULT KP_CreateBlankSurface(GAME_GLOBAL *pgg, LPDIRECTDRAWSURFACE *lplpdds, unsigned int nWidth, unsigned int nHeight, unsigned int nFillColor)
/*
** KP_CreateBlankSurface
** Creates a blank surface and fills it with the specified color
*/
{
    HRESULT        hr;
    DDSURFACEDESC ddsd;
	LPDIRECTDRAWSURFACE lpdds = NULL;
	DDCOLORKEY	   col_key;
	DDBLTFX			ddbltfx;

    /* Create the blank DD surface */
    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    //ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth        = nWidth;
    ddsd.dwHeight       = nHeight;

	if (hr = (pgg->lpdd->CreateSurface(&ddsd,&lpdds,NULL) != DD_OK))
	{
		MessageBox(pgg->hWnd,"CreateSurface() failed","Error",MB_OK);
		return hr;
	}

	/* Set the transparency key of this surface */
	col_key.dwColorSpaceLowValue = 0;
	col_key.dwColorSpaceHighValue = 0;

	lpdds->SetColorKey(DDCKEY_SRCBLT,&col_key);

    /* Fill the surface with the specified color */
	ZeroMemory(&ddbltfx,sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = nFillColor;
	lpdds->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);

	/* Return result & fill in passed pointer to surface pointer */
	*lplpdds = lpdds;

    return DD_OK;
}

HRESULT KP_DrawBitmapOnSurface(LPDIRECTDRAWSURFACE lpdds, HBITMAP hBMP,
                              DWORD dwBMPOriginX, DWORD dwBMPOriginY, 
                              DWORD dwBMPWidth, DWORD dwBMPHeight )
/*
** KP_DrawBitmapOnSurface
** Draws the specified bitmap on the specified surface, and performs all stretching if needed.
*/
{
    HDC            hDCImage;
    HDC            hDC;
    BITMAP         bmp;
    DDSURFACEDESC ddsd;
    HRESULT        hr;

    if( hBMP == NULL)
        return E_INVALIDARG;

    // Make sure this surface is restored.
    if( FAILED( hr = lpdds->Restore() ) )
        return hr;

    // Get the surface.description
    ddsd.dwSize  = sizeof(ddsd);
    lpdds->GetSurfaceDesc( &ddsd );

    if( ddsd.ddpfPixelFormat.dwFlags == DDPF_FOURCC )
        return E_NOTIMPL;

    // Select bitmap into a memoryDC so we can use it.
    hDCImage = CreateCompatibleDC( NULL );
    if( NULL == hDCImage )
        return E_FAIL;

    SelectObject( hDCImage, hBMP );

    // Get size of the bitmap
    GetObject( hBMP, sizeof(bmp), &bmp );

    // Use the passed size, unless zero
    dwBMPWidth  = ( dwBMPWidth  == 0 ) ? bmp.bmWidth  : dwBMPWidth;     
    dwBMPHeight = ( dwBMPHeight == 0 ) ? bmp.bmHeight : dwBMPHeight;

    // Stretch the bitmap to cover this surface
    if( FAILED( hr = lpdds->GetDC( &hDC ) ) )
        return hr;

    StretchBlt( hDC, 0, 0, 
                ddsd.dwWidth, ddsd.dwHeight, 
                hDCImage, dwBMPOriginX, dwBMPOriginY,
                dwBMPWidth, dwBMPHeight, SRCCOPY );

    if( FAILED( hr = lpdds->ReleaseDC( hDC ) ) )
        return hr;

    DeleteDC( hDCImage );

    return S_OK;
}

int	KP_FadeSurface(GAME_GLOBAL *pgg, LPDIRECTDRAWSURFACE lpdds, int alpha)
/*
** KP_FadeSurface()
** Stub function to call the correct fader
*/
{
	if (pgg->nBPP == 32)
		return KP_FadeSurface_32BPP(lpdds,alpha);
	else if (pgg->nBPP == 24)
		return KP_FadeSurface_24BPP(lpdds,alpha);

	return 0;
}

int	KP_FadeSurface_24BPP(LPDIRECTDRAWSURFACE lpdds, int alpha)
{
	DDSURFACEDESC ddsd, ddsddm;
	int i, jump, lpitch32, width, height;
	unsigned __int8 *pctptr, *video_buffer, *temp, color;

	if (alpha >= 255)
		return 0;

	SourceTable = LookupPointer(alpha);
	DestTable = LookupPointer(255 - alpha);

	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	memset(&ddsddm,0,sizeof(ddsddm));
	ddsddm.dwSize = sizeof(ddsddm);
	ddsddm.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	
	/* Get surface dimensions */
	lpdds->GetSurfaceDesc(&ddsddm);
	width = ddsddm.dwWidth; height = ddsddm.dwHeight;

	/* Lock the surface */
	lpdds->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);

	lpitch32 = ddsd.lPitch / 3;
	temp = video_buffer = (unsigned __int8*)ddsd.lpSurface;

	jump = lpitch32 - width;

	do
	/* Go through each row */
	{
		i = width;

		while (i-- > 0)
		/* Scan each pixel in this row */
		{

			*temp = SourceTable->Values[*temp]; 
			temp++;
			*temp = SourceTable->Values[*temp]; 
			temp++;
			*temp = SourceTable->Values[*temp];

			/*
			*temp = _RGB32BIT(0,
				(unsigned char)(pct * (color & 0xff0000)),
				(unsigned char)(pct * (color & 0xff00)),
				(unsigned char)(pct * (color & 0xff)));
				*/

			/* Go to next pixel */
			temp++;
		}

		/* Skip the linear pitch */
		temp += jump;

	} while (--height > 0);

	/* All done */
	lpdds->Unlock(NULL);

	return 0;
}

int	KP_FadeSurface_32BPP(LPDIRECTDRAWSURFACE lpdds, int alpha)
/*
** KP_FadeSurface_32BPP
** Fades out a 32-bit color surface, 0% = totally black, 100% = no fading
** Returns: 0 if successful
*/
{
	DDSURFACEDESC ddsd, ddsddm;
	int i, jump, lpitch32, width, height;
	unsigned char *pctptr;
	unsigned long color, *temp, *video_buffer;

	Pixel32 SourceColor, DestColor;

	DestColor.Value = 0;

	SourceTable = LookupPointer(alpha);
	DestTable = LookupPointer(255 - alpha);

	if (alpha >= 255)
		return 0;

	// pctptr = rgb_pct[percent];

	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	memset(&ddsddm,0,sizeof(ddsddm));
	ddsddm.dwSize = sizeof(ddsddm);
	ddsddm.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	
	/* Get surface dimensions */
	lpdds->GetSurfaceDesc(&ddsddm);
	width = ddsddm.dwWidth; height = ddsddm.dwHeight;

	/* Lock the surface */
	lpdds->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);

	lpitch32 = ddsd.lPitch >> 2;
	temp = video_buffer = (unsigned long*)ddsd.lpSurface;

	jump = lpitch32 - width;

	do
	/* Go through each row */
	{
		i = width;

		while (i-- > 0)
		/* Scan each pixel in this row */
		{
			SourceColor.Value = *temp;

			*temp = AlphaBlend(DestColor,SourceColor,alpha);
			/*
			*temp = _RGB32BIT(0,
				(unsigned char)(pct * (color & 0xff0000)),
				(unsigned char)(pct * (color & 0xff00)),
				(unsigned char)(pct * (color & 0xff)));
				*/

			/* Go to next pixel */
			temp++;
		}

		/* Skip the linear pitch */
		temp += jump;

	} while (--height > 0);

	/* All done */
	lpdds->Unlock(NULL);

	return 0;
}

void KP_ODS(char *buffer, ...)
/*
** KP_ODS()
** This function outputs a string to the debugger(if attached) using printf-style formatting.
*/
{
	va_list vArgs;
	char buf[2048];

	va_start(vArgs,buffer);
	vsprintf(buf,buffer,vArgs);
	va_end(vArgs);

	strcat(buf,"\r\n");

	/* Output string */
	OutputDebugString(buf);
}


__inline unsigned __int8 clipByte(int value)
/*
** clipByte()
** Clips a byte from a value
*/
{
	value = (0 & (-(int)(value < 0))) | (value & (-(int)!(value < 0)));
	value = (255 & (-(int)(value > 255))) | (value & (-(int)!(value > 255)));
	return value;
}

int InitAlphaTable()
{
	float fValue, fAlpha;
	int iValue, iAlpha;

	for (iAlpha = 0; iAlpha < 256; iAlpha++)
	{
		fAlpha = ((float)iAlpha) / 255;

		for (iValue = 0; iValue < 256; iValue++)
		{
			fValue = ((float)iValue) / 255;
			at.Levels[iAlpha].Values[iValue] = clipByte((int)((fValue * fAlpha) * 255));
		}
	}

	return 0;
}

__inline LookupLevel *LookupPointer(int alpha)
{
	return &at.Levels[alpha];
}

__inline __int32 AlphaBlend(Pixel32 DestColor, Pixel32 SourceColor, __int32 Alpha)
{
	Pixel32 NewColor;

	NewColor.Channels.Red = SourceTable->Values[SourceColor.Channels.Red] + 
		DestTable->Values[DestColor.Channels.Red];
	NewColor.Channels.Green = SourceTable->Values[SourceColor.Channels.Green] + 
		DestTable->Values[DestColor.Channels.Green];
	NewColor.Channels.Blue = SourceTable->Values[SourceColor.Channels.Blue] + 
		DestTable->Values[DestColor.Channels.Blue];

	return NewColor.Value;
}

void KP_FillSurface(LPDIRECTDRAWSURFACE lpdds, unsigned int nFillColor)
/*
** KP_FillSurface()
** Fills the surface with the specified color
*/
{
	DDBLTFX ddbltfx;

	ZERO_OUT(ddbltfx);

	ddbltfx.dwSize = sizeof(ddbltfx);

	ddbltfx.dwFillColor = nFillColor;
	lpdds->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
}