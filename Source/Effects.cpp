/*
** Effects.cpp
**
** This file contains all the graphical effects
** functions for Keno Pro.
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#include "..\Include\Effects.h"

int Effect_Startup_1(GAME_GLOBAL *pgg, unsigned int nState, BOOL bPhaseOut, int frames, GAME_OBJECT *pgoSelected)
/*
** Effect_Startup_1
** Sets up the startup screen for Effect #1(Buttons going up and down)
** Returns: 0 if successful, -1 if error occurred
*/
{
	GAME_OBJECT *curr = &pgg->gs[nState].ObjDefault;
	BOOL bUp = TRUE;
	int count, y_top = 300, y_topreal = y_top - pgoSelected->dm[0].height, y_bottom = 425;
	int y_origin = 0, offset;

	if (bPhaseOut == TRUE)
	{
		while (curr->next)
		/* Find the startup buttons */
		{
			curr = curr->next;

			if (curr->dwID == pgoSelected->dwID)
			/* Found the button selected */
			{
				pgg->dwFlags |= GF_NOCLICKS;
				pgoSelected->dwFlags |= GOF_BLINKER | GOF_TIMEDFRAMES;
				pgoSelected->dwWorkValue = 1;
				pgoSelected->dwWorkValue2 = 150;
				pgoSelected->dwRefCount = 1;
				pgoSelected->dwRefCount2 = 0;
			}
			else if (curr->dwID == OBJID_STARTUP_STRAIGHT ||
					curr->dwID == OBJID_STARTUP_QUICKPICK ||
					curr->dwID == OBJID_STARTUP_WAY ||
					curr->dwID == OBJID_STARTUP_SPECIAL ||
					curr->dwID == OBJID_STARTUP_PLAYERSCHOICE)
				/* Next button to manipulate(Obviously the selected button will not execute this code) */
			{
				curr->dwFlags = GOF_NOTIFY;
				curr->dwNotifySubCode = ONSC_EFFECTDONE;
				curr->dwRefCount = frames;
				y_origin = curr->pos[0].y;

				for (count = frames; count >= 1; count--)
				/* Calculate offset of each frame */
				{
					curr->srcpos[count].x = curr->srcpos[0].x;
					curr->srcpos[count].y = curr->srcpos[0].y;
					curr->dm[count].width = curr->dm[0].width;
					curr->dm[count].height = curr->dm[0].height;
					curr->lpdds[count] = curr->lpdds[0];
					curr->pos[count].x = curr->pos[0].x;
					curr->pos[count].y = curr->pos[0].y;

					if (bUp)
					{
						/* Get frame y position */
						curr->pos[count].y = y_topreal + (int)( (float)((float)count / (float)frames) * (y_origin - y_topreal) );

						if (curr->pos[count].y < y_top)
						/* Below the cutoff point */
						{
							curr->dm[count].height = curr->dm[0].height - (y_top - curr->pos[count].y);
							curr->srcpos[count].y = (y_top - curr->pos[count].y);
							curr->pos[count].y = y_top;
						}
					}
					else
					{
						curr->pos[count].y = y_bottom - (int)( (float)((float)count / (float)frames) * (y_bottom - y_origin) );

						if (curr->pos[count].y + curr->dm[count].height >= y_bottom)
						/* Past the cutoff point */
						{
							curr->dm[count].height = y_bottom - curr->pos[count].y;
						}
					}

					//KP_ODS("count==%d,curr->pos[count].y==%d,curr->dwID==%d",count,curr->pos[count].y,curr->dwID);
				}
				curr->lpdds[0] = NULL;
				bUp == TRUE ? bUp = FALSE : bUp = TRUE;
			}
		}
	}

	return 0;
}

int Effect_TicketChange(GAME_GLOBAL *pgg, unsigned int nStateFrom, unsigned int nStateTo, int frames, GAME_OBJECT *pgoSelected)
/*
** Effect_TicketChange()
** This effect will show when the player goes from one ticket to another
*/
{
	int nObjects[20], ocount, count, nIncrement = 0;
	GAME_OBJECT *curr = NULL;

	memset(&nObjects[0],0,sizeof(nObjects));

	/* Step 1: Select the objects to apply the effect to */
	switch (nStateFrom)
	{
		case GAME_STATE_QUICKPICK_TICKET:
		{
			nObjects[0] = OBJID_QPTICKET_BUTTONFRAME;
			nObjects[1] = OBJID_QPTICKET_TWOSPOT;
			nObjects[2] = OBJID_QPTICKET_THREESPOT;
			nObjects[3] = OBJID_QPTICKET_FOURSPOT;
			nObjects[4] = OBJID_QPTICKET_FIVESPOT;
			nObjects[5] = OBJID_QPTICKET_SIXSPOT;
			nObjects[6] = OBJID_QPTICKET_SEVENSPOT;
			nObjects[7] = OBJID_QPTICKET_EIGHTSPOT;
			nObjects[8] = OBJID_QPTICKET_NINESPOT;
			nObjects[9] = OBJID_QPTICKET_TENSPOT;
			nObjects[10] = OBJID_QPTICKET_TWENTYSPOT;
		}
		break;
		case GAME_STATE_WAY_TICKET:
		{
			nObjects[0] = OBJID_WAYTICKET_BUTTONFRAME;
			nObjects[1] = OBJID_WAYTICKET_TWOWAY;
			nObjects[2] = OBJID_WAYTICKET_THREEWAY;
			nObjects[3] = OBJID_WAYTICKET_FOURWAY;
			nObjects[4] = OBJID_WAYTICKET_FIVEWAY;
			nObjects[5] = OBJID_WAYTICKET_SIXWAY;
			nObjects[6] = OBJID_WAYTICKET_SEVENWAY;
			nObjects[7] = OBJID_WAYTICKET_EIGHTWAY;
			nObjects[8] = OBJID_WAYTICKET_NINEWAY;
			nObjects[9] = OBJID_WAYTICKET_TENWAY;
			nObjects[10] = OBJID_WAYTICKET_TWENTYWAY;
			nObjects[11] = OBJID_WAYTICKET_GROUPIT;
		}
		break;
		case GAME_STATE_PLAYERS_TICKET:
		{
			nObjects[0] = OBJID_PCTICKET_BUTTONFRAME;
			nObjects[1] = OBJID_PCTICKET_190WAY8_V;
			nObjects[2] = OBJID_PCTICKET_190WAY8_B;
			nObjects[3] = OBJID_PCTICKET_120WAY10;
			nObjects[4] = OBJID_PCTICKET_810S;
			nObjects[5] = OBJID_PCTICKET_108S;
			nObjects[6] = OBJID_PCTICKET_HORIZONTALROWS;
			nObjects[7] = OBJID_PCTICKET_DEALERSPECIAL;
			nObjects[8] = OBJID_PCTICKET_VERTICALROWS;
		}
		break;
		case GAME_STATE_SPECIAL_TICKET:
		{
			nObjects[0] = OBJID_SPECIALTICKET_BUTTONFRAME;
			nObjects[1] = OBJID_SPECIALTICKET_TOPANDBOTTOMBTN;
			nObjects[2] = OBJID_SPECIALTICKET_TOPANDBOTTOMICON;
			nObjects[3] = OBJID_SPECIALTICKET_LEFTANDRIGHTBTN;
			nObjects[4] = OBJID_SPECIALTICKET_LEFTANDRIGHTICON;
			nObjects[5] = OBJID_SPECIALTICKET_EDGEBTN;
			nObjects[6] = OBJID_SPECIALTICKET_EDGEICON;
			nObjects[7] = OBJID_SPECIALTICKET_ODDOREVENBTN;
			nObjects[8] = OBJID_SPECIALTICKET_ODDOREVENICON;
		}
		break;
	}

	/* Step 2: Add effect to objects on the "from" state */

	for (ocount = 0; nObjects[ocount]; ocount++)
	/* Set the effects for the specified game state */
	{
		curr = KP_FindObject(pgg,&pgg->gs[nStateFrom].ObjDefault,nObjects[ocount]);
		curr->dwRefCount = frames + 1;

		curr->pos[curr->dwRefCount].x = curr->pos[0].x;

		if (!ocount)
			nIncrement = (SCREEN_WIDTH - curr->pos[curr->dwRefCount].x) / curr->dwRefCount;

		for (count = curr->dwRefCount; count > 0; count--)
		{
			if (count == curr->dwRefCount)
				curr->pos[curr->dwRefCount].x = curr->pos[0].x;
			else
			{
				curr->pos[count].x = curr->pos[curr->dwRefCount].x + ((curr->dwRefCount - count) * nIncrement);
				
				if (curr->pos[count].x >= SCREEN_WIDTH)
				{
					curr->pos[count].x = 0;
					curr->lpdds[count] = NULL;
					continue;
				}
			}

			/* Set other values */
			curr->srcpos[count].x = curr->srcpos[0].x;
			curr->srcpos[count].y = curr->srcpos[0].y;
			curr->dm[count].height = curr->dm[0].height;
			curr->lpdds[count] = curr->lpdds[0];
			curr->pos[count].y = curr->pos[0].y;


			if (curr->pos[count].x + curr->dm[0].width > SCREEN_WIDTH)
			/* Adjust the width to fit on the screen */
			{
				curr->dm[count].width = SCREEN_WIDTH - curr->pos[count].x;
			}
			else
			/* Use default width */
				curr->dm[count].width = curr->dm[0].width;
		}
	}


	/* Step 3: Add effect to objects on the "to" state */

	/* Step 4: Update all engine reference values */
	pgg->dwFlags |= GF_NOCLICKS;

	pgoSelected->dwFlags |= GOF_NOTIFY;
	pgoSelected->dwNotifySubCode = ONSC_EFFECTDONE;
	pgoSelected->dwRefCount = frames;

	return 0;
}