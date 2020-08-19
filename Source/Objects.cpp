/*
** Objects.cpp
**
** This file contains all the object initialization and shutdown
** functions for Keno Pro.
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#include "../include/Objects.h"
#include "../include/KenoPro.h"

static int TktXCoords[] = { 0, 4, 39, 74, 109, 145, 180, 215, 251, 286, 321 };
static int TktYCoords[] = { 3, 36, 70, 104, 143, 177, 211, 244 };

static unsigned long rnum[2];// single 64 bit number

/* Define all surfaces to be used in the game here */
GAME_SURFACE_TABLE gst[] =
{
	{ SURFACEID_BACKGROUND_STARTUP, "Bitmaps\\Background\\Startup_Background.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_STARTUP, "Bitmaps\\Buttons\\Startup_Buttons.bmp", NULL, NULL },
	{ SURFACEID_FRAME_METERS, "Bitmaps\\Frames\\Meters.bmp", NULL, NULL },
	{ SURFACEID_FRAME_SAVED, "Bitmaps\\Frames\\SavedTickets_Frame.bmp", NULL, NULL },
	{ SURFACEID_FRAME_SCROLLTEXT, "Bitmaps\\Frames\\ScrollingText_Frame.bmp", NULL, NULL },
	{ SURFACEID_FRAME_QUICKPICK, "Bitmaps\\Frames\\QuickPick_Frame.bmp", NULL, NULL },
	{ SURFACEID_FRAME_STRAIGHT, "Bitmaps\\Frames\\StraightTicketText_Frame.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_TICKETTAB, "Bitmaps\\Buttons\\TicketTab_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_CLEARSAVED, "Bitmaps\\Buttons\\ClearSaved_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_TICKETTYPE, "Bitmaps\\Buttons\\TicketType_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_GAMEINFO, "Bitmaps\\Buttons\\GameInfo_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_GAMEPLAY, "Bitmaps\\Buttons\\GamePlay_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_MONEY, "Bitmaps\\Buttons\\Money_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_TICKET, "Bitmaps\\Background\\UnmarkedTicket_Background.bmp", NULL, NULL },
	{ SURFACEID_ICON_TICKET, "Bitmaps\\Icons\\Ticket_Icons.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_BET, "Bitmaps\\Background\\BetAmount_Background.bmp", NULL, NULL },
	{ SURFACEID_FONT_TICKETBET, "Bitmaps\\Fonts\\Ticketbet_Numbers.bmp", NULL, NULL },
	{ SURFACEID_FONT_METERNBRS, "Bitmaps\\Fonts\\Meter_Numbers.bmp", NULL, NULL },
	{ SURFACEID_LABEL_220SPOT, "Bitmaps\\Labels\\2-20_Spot_Labels.bmp", NULL, NULL },
	{ SURFACEID_LABEL_STRAIGHTTICKET, "Bitmaps\\Labels\\StraightTicket_Label.bmp", NULL, NULL },
	{ SURFACEID_LABEL_QUICKPICK, "Bitmaps\\Labels\\QuickPick_Label.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_QUICKPICK, "Bitmaps\\Buttons\\QuickPick_Buttons.bmp", NULL, NULL },
	{ SURFACEID_LABEL_WAYTICKET, "Bitmaps\\Labels\\WayTicket_Label.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_WAYTICKET, "Bitmaps\\Buttons\\Way_Buttons.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_GROUPIT, "Bitmaps\\Buttons\\GroupIt_Buttons.bmp", NULL, NULL },
	{ SURFACEID_ICON_WAYLETTERS, "Bitmaps\\Icons\\Way_Icons.bmp", NULL, NULL },
	{ SURFACEID_LABEL_PLAYERSCHOICE, "Bitmaps\\Labels\\Players_Label.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_PLAYERSCHOICE, "Bitmaps\\Buttons\\Players_Buttons.bmp", NULL, NULL },
	{ SURFACEID_LABEL_SPECIALTICKET, "Bitmaps\\Labels\\SpecialTicket_Label.bmp", NULL, NULL },
	{ SURFACEID_BUTTON_SPECIALTICKET, "Bitmaps\\Buttons\\Special_Buttons.bmp", NULL, NULL },
	{ SURFACEID_ICON_SPECIAL_TB, "Bitmaps\\Icons\\TopBottom_Icon.bmp", NULL, NULL },
	{ SURFACEID_ICON_SPECIAL_LR, "Bitmaps\\Icons\\LeftRight_Icon.bmp", NULL, NULL },
	{ SURFACEID_ICON_SPECIAL_EDGE, "Bitmaps\\Icons\\Edge_Icon.bmp", NULL, NULL },
	{ SURFACEID_ICON_SPECIAL_OE, "Bitmaps\\Icons\\OddEven_Icon.bmp", NULL, NULL },
	{ SURFACEID_LABEL_CHANGEBET, "Bitmaps\\Labels\\ChangeBet_Label.bmp", NULL, NULL },
	{ SURFACEID_FRAME_WAYTICKET, "Bitmaps\\Frames\\WayTicket_Frame.bmp", NULL, NULL },
	{ SURFACEID_FRAME_PCTICKET, "Bitmaps\\Frames\\PlayersChoice_Frame.bmp", NULL, NULL },
	{ SURFACEID_FRAME_SPECIALTICKET, "Bitmaps\\Frames\\SpecialTicket_Frame.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_QUICKPICK, "Bitmaps\\Background\\QuickPick_Background.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_STRAIGHT, "Bitmaps\\Background\\Straight_Background.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_SPECIAL, "Bitmaps\\Background\\Special_Background.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_WAYTICKET, "Bitmaps\\Background\\WayTicket_Background.bmp", NULL, NULL },
	{ SURFACEID_BACKGROUND_PLAYERSTICKET, "Bitmaps\\Background\\PlayersTicket_Background.bmp", NULL, NULL },
	{ SURFACEID_FRAME_TICKETINFO, "Bitmaps\\Frames\\TicketInfo_Frame.bmp", NULL, NULL },
	{ SURFACEID_LABEL_PLAYERSTYPE, "Bitmaps\\Labels\\PlayersTicketType_Label.bmp", NULL, NULL },
	{ SURFACEID_FONT_WAYNUMBERS, "Bitmaps\\Fonts\\Way_Numbers.bmp", NULL, NULL },
	{ SURFACEID_ICON_SPECIAL_LETTERS, "Bitmaps\\Icons\\Special_Letters.bmp", NULL, NULL },
	{ SURFACEID_LABEL_SPECIALTYPE, "Bitmaps\\Labels\\SpecialType_Label.bmp", NULL, NULL },
	{ SURFACEID_FONT_SCROLLINGTEXT, "Bitmaps\\Fonts\\Scrolling_Alphabet.bmp", NULL, NULL },
	{ SURFACEID_BALLS, "Bitmaps\\Balls\\Balls.bmp", NULL, NULL },

	{ SURFACEID_INVALID, NULL, NULL, NULL }
};

HRESULT SetupObjects(GAME_GLOBAL *pgg)
/*
** SetupObjects()
** This function is called by the KP engine to set up all objects
** for the game.
*/
{
	GAME_OBJECT goInfo;
	HRESULT hr = NULL;
	unsigned short sid, count;

	memset(&goInfo,0,sizeof(goInfo));

	/* Set game state to startup screen */
	pgg->nState = GAME_STATE_STARTUP;

	/* Default startup is not in demo mode */
	pgg->kenodata.lpnCredits = &pgg->kenodata.nGameCredits;
	pgg->kenodata.nGameCredits = 1000;

	/* Each ticket must have... */
	for (count = 0; count <= 8; count++)
	{

		/* ... at least one group */
		pgg->kenodata.tickets[count].nGroupCount = 1;

		/* ... a tendency to be a straight ticket by default */
		pgg->kenodata.tickets[count].nType = TICKET_TYPE_STRAIGHT;

		/* ... and a $1 bet */
		pgg->kenodata.tickets[count].nBet = 100;
		pgg->kenodata.tickets[count].nBetIteration = 100;
	}

	/* Apply these attributes to the work ticket as well */
	memcpy(&pgg->kenodata.tickets[pgg->kenodata.nWorkTicket],&pgg->kenodata.tickets[0],sizeof(pgg->kenodata.tickets[0]));

	/* Create all our surfaces inside the table */
	if (FAILED(hr = RestoreSurfaces(pgg,TRUE)))
		return hr;

	/* Set up startup screen */
	if (!Setup_Startup(pgg,GAME_STATE_STARTUP))
		return NULL;

	/* Add all common ticket objects(ticket background, etc...) */
	if (!AddCommonTicketObjects(pgg,0))
		return NULL;

	/* Add ticket-specific objects */
	if (!SetupTicket_QuickPick(pgg,GAME_STATE_QUICKPICK_TICKET))
		return NULL;

	if (!SetupTicket_Straight(pgg,GAME_STATE_STRAIGHT_TICKET))
		return NULL;

	if (!SetupTicket_Way(pgg,GAME_STATE_WAY_TICKET))
		return NULL;

	if (!SetupTicket_PlayersChoice(pgg,GAME_STATE_PLAYERS_TICKET))
		return NULL;

	if (!SetupTicket_SpecialTicket(pgg,GAME_STATE_SPECIAL_TICKET))
		return NULL;

	/* Create onscreen objects for the working ticket */
	if (CreateTicketSpecificObjects(pgg, &(pgg->kenodata.tickets[pgg->kenodata.nWorkTicket])))
	{
		KP_ODS("CreateTicketSpecificObjects() failed!");
	}

	return DD_OK;
}

void DestroyObjects(GAME_GLOBAL *pgg)
/*
** DestroyObjects()
** This function is called as the engine shuts down, to free objects
*/
{
	return;
}

int NotifyObject(GAME_OBJECT *pgo, unsigned short nState, unsigned int code)
/*
** NotifyObject()
** This function is called when an object is to be notified of an
** event.
** Returns: 0 if successful, -2 to skip reference count processing for the rest of the frame,
** -3 to skip transitioning the screen until the next frame
*/
{
	switch (pgo->dwID)
	/* Find the object ID # */
	{
		case OBJID_TICKET_ONE:
		case OBJID_TICKET_TWO:
		case OBJID_TICKET_THREE:
		case OBJID_TICKET_FOUR:
		case OBJID_TICKET_FIVE:
		case OBJID_TICKET_SIX:
		case OBJID_TICKET_SEVEN:
		case OBJID_TICKET_EIGHT:
		{
			if (code == NOTIFY_CODE_CLICK)
			/* Player clicked one of the tickets on the top */
			{
				/* NOTE: Assumption made that OBJID_TICKET_ONE - OBJID_TICKET_EIGHT are in sequence!! */
				int nNewTicket = 1;
				nNewTicket += pgo->dwID;
				nNewTicket -= OBJID_TICKET_ONE;

				if (nNewTicket != pgo->pgg->kenodata.nActiveTicket)
				/* Switch to the corresponding ticket */
				{
					ShowTicket(pgo->pgg,nNewTicket);

					SetTicketTab(pgo->pgg,pgo->pgg->kenodata.nActiveTicket,TICKET_TAB_DONTCHANGE,FALSE);

					pgo->pgg->kenodata.nActiveTicket = nNewTicket;

					SetTicketTab(pgo->pgg,nNewTicket,TICKET_TAB_DONTCHANGE,TRUE);
				}

			}
		}
		break;

		case OBJID_TICKET_STRAIGHTBTN:
		case OBJID_TICKET_QPBTN:
		case OBJID_TICKET_WAYBTN:
		case OBJID_TICKET_SPECIALBTN:
		case OBJID_TICKET_PLAYERSBTN:
		{
			int nStateTo, nTypeTo;

			if (pgo->dwID == OBJID_TICKET_STRAIGHTBTN)
			{
				nStateTo = GAME_STATE_STRAIGHT_TICKET;
				nTypeTo = TICKET_TYPE_STRAIGHT;
			}
			else if (pgo->dwID == OBJID_TICKET_QPBTN)
			{
				nStateTo = GAME_STATE_QUICKPICK_TICKET;
				nTypeTo = TICKET_TYPE_QUICKPICK;
			}
			else if (pgo->dwID == OBJID_TICKET_WAYBTN)
			{
				nStateTo = GAME_STATE_WAY_TICKET;
				nTypeTo = TICKET_TYPE_WAYTICKET;
			}
			else if (pgo->dwID == OBJID_TICKET_SPECIALBTN)
			{
				nStateTo = GAME_STATE_SPECIAL_TICKET;
				nTypeTo = TICKET_TYPE_SPECIAL;
			}
			else if (pgo->dwID == OBJID_TICKET_PLAYERSBTN)
			{
				nStateTo = GAME_STATE_PLAYERS_TICKET;
				nTypeTo = TICKET_TYPE_PLAYERS;
			}

			if (code == NOTIFY_CODE_CLICK)
			/* One of the ticket type buttons was clicked */
				Effect_TicketChange(pgo->pgg,pgo->pgg->nState,nStateTo,5,pgo);

			else if (code == NOTIFY_CODE_REFERENCE)
			{
				if (pgo->dwNotifySubCode == ONSC_EFFECTDONE)
				{
					KENO_TICKET *pWorkTkt = &(pgo->pgg->kenodata.tickets[pgo->pgg->kenodata.nWorkTicket]);

					/* The effect is done, switch to the next game state */
					pgo->pgg->nState = nStateTo;
					pWorkTkt->nType = nTypeTo;

					CreateTicketSpecificObjects(pgo->pgg,pWorkTkt);

					pgo->pgg->dwFlags ^= GF_NOCLICKS;

					pgo->dwFlags ^= GOF_NOTIFY;
					pgo->dwNotifySubCode = 0;

					/* Reset the correct objects */
					if (pWorkTkt->nType == TICKET_TYPE_STRAIGHT)
						SetupTicket_Straight(pgo->pgg,nStateTo);
					else if (pWorkTkt->nType == TICKET_TYPE_QUICKPICK)
						SetupTicket_QuickPick(pgo->pgg,nStateTo);
					else if (pWorkTkt->nType == TICKET_TYPE_WAYTICKET)
						SetupTicket_Way(pgo->pgg,nStateTo);
					else if (pWorkTkt->nType == TICKET_TYPE_SPECIAL)
						SetupTicket_SpecialTicket(pgo->pgg,nStateTo);
					else if (pWorkTkt->nType == TICKET_TYPE_PLAYERS)
						SetupTicket_PlayersChoice(pgo->pgg,nStateTo);

				}
			}
		}
		break;

		case OBJID_STARTUP_STRAIGHT:
		case OBJID_STARTUP_QUICKPICK:
		case OBJID_STARTUP_WAY:
		case OBJID_STARTUP_SPECIAL:
		case OBJID_STARTUP_PLAYERSCHOICE:
		{
			if (code == NOTIFY_CODE_CLICK)
			/* One of the startup buttons was clicked */
			{
				int AT = pgo->pgg->kenodata.nWorkTicket;

				Effect_Startup_1(pgo->pgg,pgo->pgg->nState,TRUE,15,pgo);

				ZERO_OUT(pgo->pgg->kenodata.tickets[AT]);

				/* To make buttons move at the same time, skip the rest of 'em */
				return -2;
			}
			else if (code == NOTIFY_CODE_REFERENCE)
			/* Something has happened */
			{
				if (pgo->dwNotifySubCode == ONSC_BLINKDONE)
				/* Button is done being blinked */
				{
					pgo->dwFlags ^= GOF_TIMEDFRAMES | GOF_NOTIFY;
					pgo->dwNotifySubCode = ONSC_INVALID;
					pgo->dwWorkValue2 = 0;
					pgo->pgg->dwFlags ^= GF_NOCLICKS;

					switch (pgo->dwID)
					/* Switch to the corresponding ticket */
					{
						case OBJID_STARTUP_STRAIGHT:
							pgo->pgg->nState = GAME_STATE_STRAIGHT_TICKET;
						break;
						case OBJID_STARTUP_QUICKPICK:
							pgo->pgg->nState = GAME_STATE_QUICKPICK_TICKET;
						break;
						case OBJID_STARTUP_WAY:
							pgo->pgg->nState = GAME_STATE_WAY_TICKET;
						break;
						case OBJID_STARTUP_SPECIAL:
							pgo->pgg->nState = GAME_STATE_SPECIAL_TICKET;
						break;
						case OBJID_STARTUP_PLAYERSCHOICE:
							pgo->pgg->nState = GAME_STATE_PLAYERS_TICKET;
						break;
					}
				}
				else if (pgo->dwNotifySubCode == ONSC_EFFECTDONE)
				/* The screen effect is done */
				{
					GAME_OBJECT *pgoTemp = NULL;

					int objid[] = { OBJID_STARTUP_STRAIGHT,
						OBJID_STARTUP_QUICKPICK,
						OBJID_STARTUP_WAY,
						OBJID_STARTUP_SPECIAL,
						OBJID_STARTUP_PLAYERSCHOICE,
						OBJID_INVALID },
					objstate[] = { GAME_STATE_STRAIGHT_TICKET,
						GAME_STATE_QUICKPICK_TICKET,
						GAME_STATE_WAY_TICKET,
						GAME_STATE_SPECIAL_TICKET,
						GAME_STATE_PLAYERS_TICKET,
						0 },
					/* HACK: Set ticket types here */
					types[] = { TICKET_TYPE_STRAIGHT,
						TICKET_TYPE_QUICKPICK,
						TICKET_TYPE_WAYTICKET,
						TICKET_TYPE_SPECIAL,
						TICKET_TYPE_PLAYERS,
						0 },
						count = 0;

					for (count = 0; objid[count] != OBJID_INVALID; count++)
					/* Use the buttons */
					{
						pgoTemp = KP_FindObject(pgo->pgg,&pgo->pgg->gs[nState].ObjDefault,objid[count]);

						if (pgoTemp)
						/* Got one of 'em */
						{
							if (pgoTemp->dwFlags & GOF_NOTIFY)
							/* This is one of buttons which moved */
							{
								pgoTemp->dwFlags ^= GOF_NOTIFY;
								pgoTemp->dwNotifySubCode = 0;
							}
							else
							/* This is the only button which did not move */
							{
								/* Fade the screen out */
								pgoTemp->pgg->gs[nState].dwFlags |= GSF_NOTIFY;
								pgoTemp->pgg->gs[nState].dwNotifySubCode = GSNSC_FADEOUT;
								pgoTemp->pgg->gs[nState].dwRefCount2 = 
									pgoTemp->pgg->gs[nState].dwRefCount = 8;
								pgoTemp->pgg->gs[nState].dwWorkValue = objstate[count];

								/* Fade the new screen in */
								pgoTemp->pgg->gs[objstate[count]].dwFlags |= GSF_NOTIFY;
								pgoTemp->pgg->gs[objstate[count]].dwNotifySubCode = GSNSC_FADEIN;
								pgoTemp->pgg->gs[objstate[count]].dwRefCount2 = 
									pgoTemp->pgg->gs[objstate[count]].dwRefCount = 8;

								/* HACK: Set the ticket type here! */
								pgoTemp->pgg->kenodata.nActiveTicket = 1;
								pgoTemp->pgg->kenodata.tickets[pgo->pgg->kenodata.nActiveTicket].nType = types[count];
								SetTicketTab(pgoTemp->pgg,pgoTemp->pgg->kenodata.nActiveTicket,TICKET_TAB_DONTCHANGE,TRUE);
							}
						}
					}

					/* Skip the screen transition this frame */
					return -3;
				}
			}
		}
		break;
		case OBJID_TICKET:
		/* The big ticket was clicked */
		{
			int AT = pgo->pgg->kenodata.nWorkTicket,
				nNumber = GetNumberFromCoords(pgo->lastclick.x,pgo->lastclick.y);
			KENO_TICKET *pTkt = &(pgo->pgg->kenodata.tickets[AT]);
			
			/* TEMP: Output the relative coordinates */
			KP_ODS("Ticket clicked at (%d,%d)",pgo->lastclick.x,pgo->lastclick.y);
			KP_ODS("Number clicked is: %d",GetNumberFromCoords(pgo->lastclick.x,pgo->lastclick.y));

			if (nNumber)
			{
				int nGroup = GetTicketGroup(pTkt,nNumber);

				if (nState == GAME_STATE_STRAIGHT_TICKET)
				/* Straight ticket */
				{
					if (nGroup != -1)
					/* Player de-selecting a number */
					{
						KP_ODS("Removing number %d, nGroup==%d",nNumber,nGroup);

						RemoveNumber(pTkt,nNumber);
					}
					else
					/* Player selecting a number */
					{
						if (AddNumber(pTkt,1,nNumber))
						/* Successfully added number */
							KP_ODS("Number %d added to group 1",nNumber);
						else
							KP_ODS("Number %d NOT added, too many in ticket");
					}

					/* Update the display */
					CreateTicketSpecificObjects(pgo->pgg,pTkt);
				}
				else if (nState == GAME_STATE_WAY_TICKET)
				/* Way ticket */
				{
					if (nGroup == -1)
					/* Player selecting a new number */
					{
						if (AddNumber(pTkt,pTkt->nGroupCount,nNumber))
						/* Successfully added number */
							KP_ODS("Number %d added to group %d",nNumber,pTkt->nGroupCount);
						else
							KP_ODS("Number %d NOT added, too many in group");
					}
					else
					/* Player de-selecting a number */
					{
						if (pTkt->nGroupCount > 1)
						/* Adjust the groups */
						{
							int count, count2;

							KP_ODS("Adjusting groups. pTkt->nGroupCount==%d,nGroup==%d",pTkt->nGroupCount,nGroup);

							for (count = nGroup + 1; count < 21; count++)
							/* Go through each remaining group */
							{
								for (count2 = 0; count2 < 21 && pTkt->nNumbers[count - 1][count2]; count2++)
								/* Copy over all the numbers */
									pTkt->nNumbers[count - 1][count2] = pTkt->nNumbers[count][count2];
							}

							ZERO_OUT(pTkt->nNumbers[pTkt->nGroupCount]);

							pTkt->nGroupCount--;
						}
						else
							ZERO_OUT(pTkt->nNumbers[nGroup]);
					}

					/* Update the display */
					CreateTicketSpecificObjects(pgo->pgg,pTkt);
				}
			}
		}
		break;
		case OBJID_TICKET_CREDITMETER:
		/* The credit meter was clicked, add $10.00 */
		{
			ChangeCredits(pgo->pgg,(*(pgo->pgg->kenodata.lpnCredits)) + 1000);
		}
		break;
		default:
		/* Highlight the button on default */
		{
			if (code == NOTIFY_CODE_CLICK)
			/* By default, blink the button */
			{
				pgo->dwFlags |= GOF_TIMEDFRAMES | GOF_NOTIFY;
				pgo->dwNotifySubCode = ONSC_BLINKDONE;
				pgo->dwRefCount++;
				pgo->dwWorkValue2 = 50;
				pgo->dwRefCount2 = 0;
				pgo->pgg->dwFlags |= GF_NOCLICKS;
			}
			else if (code == NOTIFY_CODE_REFERENCE)
			/* Default behavior for button blinking */
			{
				if (pgo->dwNotifySubCode == ONSC_BLINKDONE)
				/*
				** If you just want a button to highlight for little while but still process it,
				** then this is your place to do so
				*/
				{
					int AT = pgo->pgg->kenodata.nWorkTicket;
					KENO_TICKET *pTkt = &(pgo->pgg->kenodata.tickets[AT]);

					pgo->dwFlags ^= GOF_TIMEDFRAMES | GOF_NOTIFY;
					pgo->dwNotifySubCode = ONSC_INVALID;
					pgo->dwWorkValue2 = 0;
					pgo->pgg->dwFlags ^= GF_NOCLICKS;

					switch (pgo->dwID)
					{
						case OBJID_TICKET_SAVETICKET:
						{
							SaveTicket(pgo->pgg,pgo->pgg->kenodata.nActiveTicket);

							if (pgo->pgg->kenodata.nActiveTicket < 8)
							/* Move on to the next available ticket */
							{
								pgo->pgg->kenodata.nActiveTicket++;
								ShowTicket(pgo->pgg,pgo->pgg->kenodata.nActiveTicket);
							}

							SetTicketTab(pgo->pgg,pgo->pgg->kenodata.nActiveTicket,TICKET_TAB_DONTCHANGE,TRUE);
						}
						break;
						case OBJID_SPECIALTICKET_TOPANDBOTTOMBTN:
						/* "Top and bottom" button */
						{
							pTkt->nType = TICKET_TYPE_SPECIAL;
							pTkt->nSubType = TICKET_SUBTYPE_TOPANDBOTTOM;
							CreateTicketSpecificObjects(pgo->pgg,pTkt);
						}
						break;
						case OBJID_SPECIALTICKET_LEFTANDRIGHTBTN:
						/* "Left and right" button */
						{
							pTkt->nType = TICKET_TYPE_SPECIAL;
							pTkt->nSubType = TICKET_SUBTYPE_LEFTANDRIGHT;
							CreateTicketSpecificObjects(pgo->pgg,pTkt);
						}
						break;
						case OBJID_SPECIALTICKET_EDGEBTN:
						/* "Edge" button */
						{
							pTkt->nType = TICKET_TYPE_SPECIAL;
							pTkt->nSubType = TICKET_SUBTYPE_EDGE;
							CreateTicketSpecificObjects(pgo->pgg,pTkt);
						}
						break;
						case OBJID_SPECIALTICKET_ODDOREVENBTN:
						/* "Odd or even" button */
						{
							pTkt->nType = TICKET_TYPE_SPECIAL;
							pTkt->nSubType = TICKET_SUBTYPE_ODDOREVEN;
							CreateTicketSpecificObjects(pgo->pgg,pTkt);
						}
						break;
						case OBJID_WAYTICKET_GROUPIT:
						/* "Group it" button on way ticket */
						{
							if (pTkt->nGroupCount < 21 && pTkt->nNumbers[pTkt->nGroupCount][0])
								pTkt->nGroupCount++;
						}
						break;
						case OBJID_PCTICKET_190WAY8_V:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_190WAY8_V);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));
						}
						break;
						case OBJID_PCTICKET_190WAY8_B:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_190WAY8_B);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));
						}
						break;
						case OBJID_PCTICKET_120WAY10:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_120WAY10);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));							
						}
						break;
						case OBJID_PCTICKET_108S:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_108S);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));							
						}
						break;
						case OBJID_PCTICKET_810S:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_810S);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));
						}
						break;
						case OBJID_PCTICKET_DEALERSPECIAL:
						{
							CreatePlayersChoiceTicket(&(pgo->pgg->kenodata.tickets[AT]),TICKET_SUBTYPE_DEALERSPECIAL);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));
						}
						break;

						case OBJID_QPTICKET_TWOSPOT:
						case OBJID_QPTICKET_THREESPOT:
						case OBJID_QPTICKET_FOURSPOT:
						case OBJID_QPTICKET_FIVESPOT:
						case OBJID_QPTICKET_SIXSPOT:
						case OBJID_QPTICKET_SEVENSPOT:
						case OBJID_QPTICKET_EIGHTSPOT:
						case OBJID_QPTICKET_NINESPOT:
						case OBJID_QPTICKET_TENSPOT:
						case OBJID_QPTICKET_TWENTYSPOT:
						{
							int nSpots;

							/* Mark the correct number of spots */
							if (pgo->dwID == OBJID_QPTICKET_TWENTYSPOT)
								nSpots = 20;
							else
							{
								nSpots = 2;
								nSpots += pgo->dwID;
								nSpots -= OBJID_QPTICKET_TWOSPOT;
							}

							CreateQuickPick(&(pgo->pgg->kenodata.tickets[AT]),nSpots);
							CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));
						}
						break;
						case OBJID_TICKET_CANCEL:
						{
							/* HACK: Cancel will go back to beginning, for now */
							int AT = pgo->pgg->kenodata.nWorkTicket;

							ZERO_OUT(pgo->pgg->kenodata.tickets[AT]);
							pgo->pgg->kenodata.tickets[AT].nBet = 100;

							Setup_Startup(pgo->pgg,GAME_STATE_STARTUP);
							pgo->pgg->nState = GAME_STATE_STARTUP;

						}
						break;

						case OBJID_TICKET_ONECENT:
						case OBJID_TICKET_FIVECENTS:
						case OBJID_TICKET_ONEQUARTER:
						case OBJID_TICKET_ONEDOLLAR:
						{
							int btns[] =
							{
								OBJID_TICKET_ONECENT,
								OBJID_TICKET_FIVECENTS,
								OBJID_TICKET_ONEQUARTER,
								OBJID_TICKET_ONEDOLLAR,
								OBJID_INVALID
							};
							int amt[] =
							{
								1,
								5,
								25,
								100,
								0
							};

							int count, iteration, AT = pgo->pgg->kenodata.nWorkTicket;

							for (count = 0; btns[count] != OBJID_INVALID; count++)
							/* Process the bet change */
							{
								if (pgo->dwID == btns[count])
								/* Found button clicked */
								{
									iteration = pgo->pgg->kenodata.tickets[AT].nBetIteration;

									if (!iteration ||
										iteration != amt[count])
									/* Clicked new bet amount */
									{
										pgo->pgg->kenodata.tickets[AT].nBetIteration = 
											pgo->pgg->kenodata.tickets[AT].nBet = amt[count];
									}
									else
									/* Clicked same bet amount as before */
										pgo->pgg->kenodata.tickets[AT].nBet += iteration;

									CreateTicketSpecificObjects(pgo->pgg,&(pgo->pgg->kenodata.tickets[AT]));

									break;
								}
							}

						}
						break;
					}
				}
			}
		}
		break;
	}

	return 0;
}

HRESULT RestoreSurfaces(GAME_GLOBAL *pgg, BOOL bMapEntries)
/*
** RestoreSurfaces()
** This function takes all the surfaces in the game surface table and redraws them
** NOTE: EVERY BITMAP HANDLE IN pgg->gst[].hBMP WILL BECOME VALID(Assuming bMapEntries == TRUE)!!
** AND IF bMapEntries == FALSE, THE HANDLES *MUST* BE VALID!!
*/
{
	int count, index;
	HRESULT hr;

	for (count = 0; (bMapEntries && gst[count].dwSurfaceID != SURFACEID_INVALID); count++)
	/* Map entries of local surface table into the global one */
	{
		/* Next map point */
		index = gst[count].dwSurfaceID;

		pgg->gst[index].dwSurfaceID = index;
		pgg->gst[index].pszBMPPath = gst[count].pszBMPPath;
		
		/* Create the surface */
		if (FAILED(hr = KP_CreateSurfaceFromBitmap(pgg,&pgg->gst[index].lpdds,&pgg->gst[index].hBMP,pgg->gst[index].pszBMPPath)))
		{
			KP_ODS("Unable to create surface, ID#%d",index);
			return hr;
		}
	}

	if (!bMapEntries)
	/* We have lost the surfaces, so let's restore them */
	{
		for (count = 0; pgg->gst[count].dwSurfaceID != SURFACEID_INVALID; count++)
		/* Restore and redraw all of our surfaces */
		{
			if (FAILED(hr = (pgg->gst[count].lpdds)->Restore()))
				return hr;

			if (FAILED(hr = KP_DrawBitmapOnSurface(pgg->gst[count].lpdds,pgg->gst[count].hBMP,0,0,0,0)))
				return hr;
		}
	}

	return DD_OK;
}

int Setup_Startup(GAME_GLOBAL *pgg, unsigned short nState)
/*
** Setup_Startup()
** Sets up the main startup screen for Keno Pro
** Returns: 1 if sucessful, 0 if not
*/
{
	GAME_OBJECT goInfo;
	HRESULT hr = NULL;
	unsigned short sid;
	int x = 0;

	ZERO_OUT(goInfo);

	/* HACK: Clear all current items! */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* Startup background */
	sid = SURFACEID_BACKGROUND_STARTUP;
	goInfo.dwID = OBJID_STARTUP_BACKGROUND;

	KP_GETBMPSIZE(pgg, sid, goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	/* Startup buttons */
	sid = SURFACEID_BUTTON_STARTUP;
	goInfo.dwFlags = GOF_CLICKABLE;

	/* Straight ticket button */
	x = 25;
	goInfo.dwID = OBJID_STARTUP_QUICKPICK;
	goInfo.dm[1].height = goInfo.dm[0].height = 94; goInfo.dm[1].width = goInfo.dm[0].width = 112;
	goInfo.pos[1].x = goInfo.pos[0].x = x; goInfo.pos[1].y = goInfo.pos[0].y = 312;
	goInfo.srcpos[1].y = goInfo.dm[1].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	/* Quick pick ticket button */
	x += (unsigned short)(goInfo.dm[0].width + 5);
	goInfo.dwID = OBJID_STARTUP_WAY;
	goInfo.dm[1].height = goInfo.dm[0].height = 94; goInfo.dm[1].width = goInfo.dm[0].width = 112;
	goInfo.pos[1].x = goInfo.pos[0].x = x; goInfo.pos[1].y = goInfo.pos[0].y = 312;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.srcpos[1].y = goInfo.dm[1].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	/* Way ticket button */
	x += goInfo.dm[0].width + 5;
	goInfo.dwID = OBJID_STARTUP_SPECIAL;
	goInfo.dm[1].height = goInfo.dm[0].height = 94; goInfo.dm[1].width = goInfo.dm[0].width = 112;
	goInfo.pos[1].x = goInfo.pos[0].x = x; goInfo.pos[1].y = goInfo.pos[0].y = 312;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.srcpos[1].y = goInfo.dm[1].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	/* Special ticket button */
	x += goInfo.dm[0].width + 5;
	goInfo.dwID = OBJID_STARTUP_STRAIGHT;
	goInfo.dm[1].height = goInfo.dm[0].height = 94; goInfo.dm[1].width = goInfo.dm[0].width = 112;
	goInfo.pos[1].x = goInfo.pos[0].x = x; goInfo.pos[1].y = goInfo.pos[0].y = 312;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.srcpos[1].y = goInfo.dm[1].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	/* Player's choice button */
	x += goInfo.dm[0].width + 5;
	goInfo.dwID = OBJID_STARTUP_PLAYERSCHOICE;
	goInfo.dm[1].height = goInfo.dm[0].height = 94; goInfo.dm[1].width = goInfo.dm[0].width = 112;
	goInfo.pos[1].x = goInfo.pos[0].x = x; goInfo.pos[1].y = goInfo.pos[0].y = 312;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.srcpos[1].y = goInfo.dm[1].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return hr;

	return 1;
}

int AddCommonTicketObjects(GAME_GLOBAL *pgg, unsigned short nState)
/*
** AddCommonTicketObjects()
** Adds all objects which are in every ticket game state(ticket background, meters, etc...)
** Returns: 0 if failed, 1 if sucessful
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, x = 0, y = 0;

	memset(&goInfo,0,sizeof(goInfo));

	/* #1: The saved ticket frame */
	sid = SURFACEID_FRAME_SAVED;

	goInfo.dwID = OBJID_TICKET_SAVEDFRAME;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.pos[0].x = 0; goInfo.pos[0].y = 0;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #2-#9: The saved tickets and "clear all saved tickets" buttons */
	sid = SURFACEID_BUTTON_TICKETTAB;
	goInfo.dwFlags |= GOF_CLICKABLE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].width /= 3;
	goInfo.dm[0].height /= 2;
	goInfo.srcpos[0].x = goInfo.dm[0].width;		/* "Open ticket" button */
	goInfo.pos[0].x += 6; goInfo.pos[0].y += 7;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	/* #2: Ticket #1 */
	goInfo.dwID = OBJID_TICKET_ONE;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #3: Ticket #2 */
	goInfo.dwID = OBJID_TICKET_TWO;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #4: Ticket #3 */
	goInfo.dwID = OBJID_TICKET_THREE;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #5: Ticket #4 */
	goInfo.dwID = OBJID_TICKET_FOUR;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #6: Ticket #5 */
	goInfo.dwID = OBJID_TICKET_FIVE;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #7: Ticket #6 */
	goInfo.dwID = OBJID_TICKET_SIX;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #8: Ticket #7 */
	goInfo.dwID = OBJID_TICKET_SEVEN;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #9: Ticket #8 */
	goInfo.dwID = OBJID_TICKET_EIGHT;
	goInfo.pos[0].x += goInfo.dm[0].width;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #10: "Clear all saved tickets" button */
	sid = SURFACEID_BUTTON_CLEARSAVED;
	goInfo.dwFlags |= GOF_CLICKABLE;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 5; 
	goInfo.pos[1].y = goInfo.pos[0].y += 2;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[1].width = goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.dwID = OBJID_TICKET_CLEARSAVED;
	goInfo.srcpos[0].x = 0; goInfo.srcpos[0].y = 0;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #10 #11 & #12: Bet, Won, and Credits meters */
	sid = SURFACEID_FRAME_METERS;
	goInfo.dwFlags = 0;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 3; y = 0;
	goInfo.srcpos[0].y = 0; goInfo.srcpos[0].x = 0;
	goInfo.pos[0].x = 0;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	/* #10: Bet meter */
	goInfo.pos[0].y = 84;
	goInfo.dwID = OBJID_TICKET_BETMETER;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #11: Won meter */
	goInfo.srcpos[0].y += goInfo.dm[0].height + goInfo.dm[0].height;
	goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.dwID = OBJID_TICKET_WONMETER;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #12: Credits meter */

	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.srcpos[0].y -= goInfo.dm[0].height;
	goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.dwID = OBJID_TICKET_CREDITMETER;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #13, #14, #15 & #16: Cash out, Proof of win, Paytable, and Help buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_GAMEINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[1].height = goInfo.dm[0].height);
	goInfo.dwFlags |= GOF_CLICKABLE;
	goInfo.dm[1].width = goInfo.dm[0].width /= 4;
	goInfo.srcpos[1].y = goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	/* #13: Cash out button */
	goInfo.pos[1].y = goInfo.pos[0].y = 210;
	goInfo.pos[1].x = goInfo.pos[0].x = 8;
	goInfo.dwID = OBJID_TICKET_CASHOUT;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #14: Proof of Win button */
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.dwID = OBJID_TICKET_POW;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #15: Paytable button */
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.dwID = OBJID_TICKET_PAYTABLE;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #16: Help button */
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.dwID = OBJID_TICKET_HELP;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #17: The scrolling text frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_SCROLLTEXT;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	goInfo.pos[0].x = 10;
	goInfo.pos[0].y = 425;
	goInfo.dwID = OBJID_TICKET_SCROLLINGTEXT;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #18, #19, #20 & #21: Start game, Cancel, Auto play, and Save ticket buttons */

	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_GAMEPLAY;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[1].width = goInfo.dm[0].width /= 4;
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* #18: "Save ticket" button */
	goInfo.pos[1].x = goInfo.pos[0].x = 475;
	goInfo.pos[1].y = goInfo.pos[0].y = 285;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width;
	goInfo.dwID = OBJID_TICKET_SAVETICKET;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #19: "Cancel" button */
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 2;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 0;
	goInfo.dwID = OBJID_TICKET_CANCEL;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #20: "Start game" button */
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 2;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 2;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 2;
	goInfo.dwID = OBJID_TICKET_STARTGAME;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #21: "Auto play" button */
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 2;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 3;
	goInfo.dwID = OBJID_TICKET_AUTOPLAY;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #22: "Change bet" label(Bet buttons are relative to this label) */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_CHANGEBET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	goInfo.pos[0].x = 500;
	goInfo.pos[0].y = 365;
	goInfo.dwID = OBJID_TICKET_CHANGEBET;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #23, #24, #25 & #26: Bet denomination buttons */
	sid = SURFACEID_BUTTON_MONEY;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[1].width = goInfo.dm[0].width /= 4;
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* #23: The one cent button */
	goInfo.pos[1].x = goInfo.pos[0].x -= 20;
	goInfo.pos[1].y = goInfo.pos[0].y += 15;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 3;
	goInfo.dwID = OBJID_TICKET_ONECENT;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #24: The five cent button */
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 2;
	goInfo.dwID = OBJID_TICKET_FIVECENTS;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #25: The one quarter button */
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width;
	goInfo.dwID = OBJID_TICKET_ONEQUARTER;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #26: The one dollar button */
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 0;
	goInfo.dwID = OBJID_TICKET_ONEDOLLAR;

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #27: The bet amount */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FONT_METERNBRS;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dwID = OBJID_TICKET_BETAMOUNT;
	goInfo.pos[0].x = 11;
	goInfo.pos[0].y = 102;
	goInfo.dm[0].width = 70;

	if (KP_CreateBlankSurface(pgg,&goInfo.lpdds[0],goInfo.dm[0].width,goInfo.dm[0].height,0)
		!= DD_OK)
		return 0;

	/* Keep this surface for later use */
	pgg->lpddsTemporary[goInfo.dwID] = goInfo.lpdds[0];

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #28: The won amount */
	goInfo.dwID = OBJID_TICKET_WONAMOUNT;
	goInfo.pos[0].y = 140;

	if (KP_CreateBlankSurface(pgg,&goInfo.lpdds[0],goInfo.dm[0].width,goInfo.dm[0].height,0)
		!= DD_OK)
		return 0;

	/* Keep this surface for later use */
	pgg->lpddsTemporary[goInfo.dwID] = goInfo.lpdds[0];

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	/* #29: The credit amount */
	goInfo.dwID = OBJID_TICKET_CREDITAMOUNT;
	goInfo.pos[0].y = 178;

	if (KP_CreateBlankSurface(pgg,&goInfo.lpdds[0],goInfo.dm[0].width,goInfo.dm[0].height,0)
		!= DD_OK)
		return 0;

	/* Keep this surface for later use */
	pgg->lpddsTemporary[goInfo.dwID] = goInfo.lpdds[0];

	if (!KP_AddObject(pgg,&(pgg->kenodata.ObjHead), 0,&goInfo))
		return 0;

	return 1;
}

int	SetupTicket_QuickPick(GAME_GLOBAL *pgg, unsigned short nState)
/*
** SetupTicket_QuickPick()
** Sets up all objects on the quick pick ticket.
** Returns: 1 if successful, 0 if failed
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, x = 0, y = 0;

	/* Remove all current items */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* #1: Add the ticket type buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_TICKETTYPE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 5;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;
	
	/* Way ticket */
	goInfo.pos[0].x = 475;
	goInfo.srcpos[0].y = goInfo.dm[0].height;
	goInfo.dwID = OBJID_TICKET_WAYBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Players choice ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 3;
	goInfo.dwID = OBJID_TICKET_PLAYERSBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Straight ticket */
	goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 4;
	goInfo.dwID = OBJID_TICKET_STRAIGHTBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Special ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.dwID = OBJID_TICKET_SPECIALBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #2: Add the quick pick buttons frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_QUICKPICK;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 475;
	goInfo.pos[0].y = 73;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_QPTICKET_BUTTONFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #3: Add the quick pick buttons(relative to frame) */
	sid = SURFACEID_BUTTON_QUICKPICK;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 4;
	goInfo.dm[1].width = goInfo.dm[0].width /= 5;
	goInfo.pos[1].x = goInfo.pos[0].x += 10;
	goInfo.pos[1].y = goInfo.pos[0].y += 13;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* 2 Spots */
	goInfo.dwID = OBJID_QPTICKET_TWOSPOT;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 3 Spots */
	goInfo.dwID = OBJID_QPTICKET_THREESPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 4 Spots */
	goInfo.dwID = OBJID_QPTICKET_FOURSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 5 Spots */
	goInfo.dwID = OBJID_QPTICKET_FIVESPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 6 Spots */
	goInfo.dwID = OBJID_QPTICKET_SIXSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 7 Spots */
	goInfo.dwID = OBJID_QPTICKET_SEVENSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 0;
	goInfo.srcpos[1].y += goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 8 Spots */
	goInfo.dwID = OBJID_QPTICKET_EIGHTSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 9 Spots */
	goInfo.dwID = OBJID_QPTICKET_NINESPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 10 Spots */
	goInfo.dwID = OBJID_QPTICKET_TENSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 20 Spots */
	goInfo.dwID = OBJID_QPTICKET_TWENTYSPOT;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + 1;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the green background */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_QUICKPICK;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 93;
	goInfo.pos[0].y = 84;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_QPTICKET_QPTICKETBG;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the ticket info frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_TICKETINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 89;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_INFOFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the quick pick label */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_QUICKPICK;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 104;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_QPTICKET_LABEL;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red bet amount background */
	sid = SURFACEID_BACKGROUND_BET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 360;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_BETBACKGROUND;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;
	
	/* The ticket */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_TICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 130;
	goInfo.dwID = OBJID_TICKET;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), 0,&goInfo))
		return 0;


	/* Change ticket transparency key of ticket to something not likley to occur */
	DDCOLORKEY col_key;

	col_key.dwColorSpaceLowValue = 99999;
	col_key.dwColorSpaceHighValue = 99999;
	
	goInfo.lpdds[0]->SetColorKey(DDCKEY_SRCBLT,&col_key);

	/* Scrolling text for the quick pick ticket */
	ZERO_OUT(goInfo);

	goInfo.pos[0].x = 15;
	goInfo.pos[0].y = 435;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dwFlags |= GOF_SCROLLINGTEXT;

	CreateScrollingTextSurface(pgg,"CHOOSE 2 TO 10 NUMBERS, OR A 20 SPOT SPECIAL. THE COMPUTER WILL GENERATE YOUR NUMBERS.",&goInfo.lpdds[0],&goInfo.dm[0].width,&goInfo.dm[0].height);

	goInfo.dmresize[0].width = 442;
	goInfo.dmresize[0].height = goInfo.dm[0].height;
	goInfo.dwWorkValue2 = 5;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return 0;

	return 1;
}

int SetupTicket_Straight(GAME_GLOBAL *pgg, unsigned short nState)
/*
** SetupTicket_Straight()
** Sets up all items on the straight ticket
** Returns: 1 if successful, otherwise, 0
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, x = 0, y = 0;

	ZERO_OUT(goInfo);

	/* Remove all current items */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* #1: Add the ticket type buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_TICKETTYPE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 5;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;
	
	/* Way ticket */
	goInfo.pos[0].x = 475;
	goInfo.srcpos[0].y = goInfo.dm[0].height;
	goInfo.dwID = OBJID_TICKET_WAYBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Players choice ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 3;
	goInfo.dwID = OBJID_TICKET_PLAYERSBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Quick pick ticket */
	goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[0].y = 0;
	goInfo.dwID = OBJID_TICKET_QPBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Special ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.dwID = OBJID_TICKET_SPECIALBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the purple background */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_STRAIGHT;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 93;
	goInfo.pos[0].y = 84;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_STRAIGHTTICKET_STRAIGHTBG;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the ticket info frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_TICKETINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 89;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_INFOFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the straight ticket label */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_STRAIGHTTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 104;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_STRAIGHTTICKET_LABEL;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red bet amount background */
	sid = SURFACEID_BACKGROUND_BET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 360;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_BETBACKGROUND;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* The ticket */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_TICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 130;
	goInfo.dwID = OBJID_TICKET;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), 0,&goInfo))
		return 0;

	/* Change ticket transparency key of ticket to something not likley to occur */
	DDCOLORKEY col_key;

	col_key.dwColorSpaceLowValue = 99999;
	col_key.dwColorSpaceHighValue = 99999;
	
	goInfo.lpdds[0]->SetColorKey(DDCKEY_SRCBLT,&col_key);

	/* Scrolling text for the straight ticket */
	ZERO_OUT(goInfo);

	goInfo.pos[0].x = 15;
	goInfo.pos[0].y = 435;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dwFlags |= GOF_SCROLLINGTEXT;

	CreateScrollingTextSurface(pgg,"PLEASE CHOOSE FROM 2 TO 10 NUMBERS OR A SPECIAL 20 SPOT.",&goInfo.lpdds[0],&goInfo.dm[0].width,&goInfo.dm[0].height);

	goInfo.dmresize[0].width = 442;
	goInfo.dmresize[0].height = goInfo.dm[0].height;
	goInfo.dwWorkValue2 = 5;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return 0;

	return 1;
}

int SetupTicket_Way(GAME_GLOBAL *pgg, unsigned short nState)
/*
** SetupTicket_Way()
** Sets up the way ticket objects
** Returns: 1 if successful, 0 if failed
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, nBtnYSpc = 4, nBtnXSpc = 2;

	/* Remove all current items */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* #1: Add the ticket type buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_TICKETTYPE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 5;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;
	
	/* Quick pick ticket */
	goInfo.pos[0].x = 475;
	goInfo.srcpos[0].y = 0;
	goInfo.dwID = OBJID_TICKET_QPBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Players choice ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 3;
	goInfo.dwID = OBJID_TICKET_PLAYERSBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Straight ticket */
	goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 4;
	goInfo.dwID = OBJID_TICKET_STRAIGHTBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Special ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.dwID = OBJID_TICKET_SPECIALBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #2: Add the way buttons frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_WAYTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 475;
	goInfo.pos[0].y = 73;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_WAYTICKET_BUTTONFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #3: Add the way ticket buttons(relative to frame) */
	sid = SURFACEID_BUTTON_WAYTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 4;
	goInfo.dm[1].width = goInfo.dm[0].width /= 5;
	goInfo.pos[1].x = goInfo.pos[0].x += 10;
	goInfo.pos[1].y = goInfo.pos[0].y += 13;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* 2 Way */
	goInfo.dwID = OBJID_WAYTICKET_TWOWAY;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 3 Way */
	goInfo.dwID = OBJID_WAYTICKET_THREEWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + nBtnXSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 4 Way */
	goInfo.dwID = OBJID_WAYTICKET_FOURWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + nBtnXSpc;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + nBtnYSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 5 Way */
	goInfo.dwID = OBJID_WAYTICKET_FIVEWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + nBtnXSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 6 Way */
	goInfo.dwID = OBJID_WAYTICKET_SIXWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + nBtnXSpc;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + nBtnYSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 7 Way */
	goInfo.dwID = OBJID_WAYTICKET_SEVENWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 0;
	goInfo.srcpos[1].y += goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + nBtnXSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 8 Way */
	goInfo.dwID = OBJID_WAYTICKET_EIGHTWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + nBtnXSpc;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + nBtnYSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 9 Way */
	goInfo.dwID = OBJID_WAYTICKET_NINEWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + nBtnXSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 10 Way */
	goInfo.dwID = OBJID_WAYTICKET_TENWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + nBtnXSpc;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + nBtnYSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 20 Way */
	goInfo.dwID = OBJID_WAYTICKET_TWENTYWAY;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x += goInfo.dm[0].width;
	goInfo.pos[1].x = goInfo.pos[0].x += goInfo.dm[0].width + nBtnXSpc;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Group it button(Relative to the "20 way" button */
	goInfo.pos[1].x = goInfo.pos[0].x -= goInfo.dm[0].width + 3;
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 5;

	sid = SURFACEID_BUTTON_GROUPIT;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.dm[1].width = goInfo.dm[0].width;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.srcpos[0].y = goInfo.srcpos[1].x = goInfo.srcpos[0].x = 0;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;
	goInfo.dwID = OBJID_WAYTICKET_GROUPIT;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red background */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_WAYTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 93;
	goInfo.pos[0].y = 84;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_WAYTICKET_WAYTICKETBG;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the ticket info frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_TICKETINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 89;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_INFOFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the way ticket label */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_WAYTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 104;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_WAYTICKET_LABEL;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red bet amount background */
	sid = SURFACEID_BACKGROUND_BET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 360;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_BETBACKGROUND;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* The ticket */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_TICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 130;
	goInfo.dwID = OBJID_TICKET;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), 0,&goInfo))
		return 0;

	/* Change ticket transparency key of ticket to something not likley to occur */
	DDCOLORKEY col_key;

	col_key.dwColorSpaceLowValue = 99999;
	col_key.dwColorSpaceHighValue = 99999;
	
	goInfo.lpdds[0]->SetColorKey(DDCKEY_SRCBLT,&col_key);


	/* Scrolling text for the way ticket */
	ZERO_OUT(goInfo);

	goInfo.pos[0].x = 15;
	goInfo.pos[0].y = 435;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dwFlags |= GOF_SCROLLINGTEXT;

	CreateScrollingTextSurface(pgg,"CHOOSE YOUR NUMBERS IN THE FIRST GROUP, AND THEN PRESS GROUP IT.",&goInfo.lpdds[0],&goInfo.dm[0].width,&goInfo.dm[0].height);

	goInfo.dmresize[0].width = 442;
	goInfo.dmresize[0].height = goInfo.dm[0].height;
	goInfo.dwWorkValue2 = 5;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return 0;

	return 1;
}

int SetupTicket_PlayersChoice(GAME_GLOBAL *pgg, unsigned short nState)
/*
** SetupTicket_PlayersChoice
** This function sets up the players choice ticket objects
** Returns: 1 if successful, 0 if failure occurs
** NOTE: The placement of the buttons is HARD CODED!!
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, nBtnYSpc = 4, nBtnXSpc = 2,
		xbtnbase[2],
		ybtnbase[4];

	/* Remove all current items */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* #1: Add the ticket type buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_TICKETTYPE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 5;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* Quick pick ticket */
	goInfo.pos[0].x = 475;
	goInfo.srcpos[0].y = 0;
	goInfo.dwID = OBJID_TICKET_QPBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Way ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height;
	goInfo.dwID = OBJID_TICKET_WAYBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Straight ticket */
	goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 4;
	goInfo.dwID = OBJID_TICKET_STRAIGHTBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Special ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
	goInfo.dwID = OBJID_TICKET_SPECIALBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #2: Add the players choice buttons frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_PCTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 475;
	goInfo.pos[0].y = 73;

	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_PCTICKET_BUTTONFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #3: Add the players choice buttons(relative to frame) */
	sid = SURFACEID_BUTTON_PLAYERSCHOICE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.dm[1].width = goInfo.dm[0].width /= 8;
	goInfo.pos[1].x = goInfo.pos[0].x += 13;
	goInfo.pos[1].y = goInfo.pos[0].y += 20;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* Calculate positions of buttons */

	xbtnbase[0] = goInfo.pos[0].x;
	xbtnbase[1] = xbtnbase[0] + goInfo.dm[0].width + 3;
	ybtnbase[0] = goInfo.pos[0].y;
	ybtnbase[1] = ybtnbase[0] + goInfo.dm[0].height + 5;
	ybtnbase[2] = ybtnbase[1] + goInfo.dm[0].height + 5;
	ybtnbase[3] = ybtnbase[2] + goInfo.dm[0].height + 5;

	/* 190 Way 8(Vertical) */
	goInfo.dwID = OBJID_PCTICKET_190WAY8_V;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 207;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 190 Way 8(Boxes) */
	goInfo.dwID = OBJID_PCTICKET_190WAY8_B;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 138;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[1];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 120 Way 10 */
	goInfo.dwID = OBJID_PCTICKET_120WAY10;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 276;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[0];
	goInfo.pos[1].y = goInfo.pos[0].y = ybtnbase[1];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 10 8's */
	goInfo.dwID = OBJID_PCTICKET_108S;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 345;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[1];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* 8 10's */
	goInfo.dwID = OBJID_PCTICKET_810S;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 414;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[0];
	goInfo.pos[1].y = goInfo.pos[0].y = ybtnbase[2];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Horizontal rows */
	goInfo.dwID = OBJID_PCTICKET_HORIZONTALROWS;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 1;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[1];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Dealer special */
	goInfo.dwID = OBJID_PCTICKET_DEALERSPECIAL;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 70;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[0];
	goInfo.pos[1].y = goInfo.pos[0].y = ybtnbase[3];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Vertical rows */
	goInfo.dwID = OBJID_PCTICKET_VERTICALROWS;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = 482;
	goInfo.pos[1].x = goInfo.pos[0].x = xbtnbase[1];

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the yellow background */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_PLAYERSTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 93;
	goInfo.pos[0].y = 84;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_PCTICKET_PCTICKETBG;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the ticket info frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_TICKETINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 89;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_INFOFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the Players Choice ticket label */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_PLAYERSCHOICE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 104;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_PCTICKET_LABEL;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red bet amount background */
	sid = SURFACEID_BACKGROUND_BET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 360;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_BETBACKGROUND;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* The ticket */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_TICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 130;
	goInfo.dwID = OBJID_TICKET;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), 0,&goInfo))
		return 0;

	/* Change ticket transparency key of ticket to something not likley to occur */
	DDCOLORKEY col_key;

	col_key.dwColorSpaceLowValue = 99999;
	col_key.dwColorSpaceHighValue = 99999;
	
	goInfo.lpdds[0]->SetColorKey(DDCKEY_SRCBLT,&col_key);


	/* Scrolling text for the players choice ticket */
	ZERO_OUT(goInfo);

	goInfo.pos[0].x = 15;
	goInfo.pos[0].y = 435;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dwFlags |= GOF_SCROLLINGTEXT;

	CreateScrollingTextSurface(pgg,"PLEASE CHOOSE ONE OF OUR EIGHT DIFFERENT PLAYERS CHOICE TICKETS.",&goInfo.lpdds[0],&goInfo.dm[0].width,&goInfo.dm[0].height);

	goInfo.dmresize[0].width = 442;
	goInfo.dmresize[0].height = goInfo.dm[0].height;
	goInfo.dwWorkValue2 = 5;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return 0;

	return 1;
}

int	SetupTicket_SpecialTicket(GAME_GLOBAL *pgg, unsigned short nState)
/*
** SetupTicket_SpecialTicket
** This function sets up the special ticket objects
** Returns: 1 if successful, 0 if failure occurs
** NOTE: Like the players choice ticket, these values are also hard coded(a lil bit)!!!!
*/
{
	GAME_OBJECT goInfo;
	unsigned short count, sid, nBtnYSpc = 4, nBtnXSpc = 2, nFrameX, nFrameY;

	/* Remove all current items */
	while (pgg->gs[nState].ObjDefault.next)
		KP_RemoveObject(pgg,&(pgg->gs[nState].ObjDefault),pgg->gs[nState].ObjDefault.next->dwID);

	/* #1: Add the ticket type buttons */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BUTTON_TICKETTYPE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dm[0].height /= 5;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* Quick pick ticket */
	goInfo.pos[0].x = 475;
	goInfo.srcpos[0].y = 0;
	goInfo.dwID = OBJID_TICKET_QPBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Way ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height;
	goInfo.dwID = OBJID_TICKET_WAYBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Straight ticket */
	goInfo.pos[0].x -= goInfo.dm[0].width + 1;
	goInfo.pos[0].y += goInfo.dm[0].height + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 4;
	goInfo.dwID = OBJID_TICKET_STRAIGHTBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Players choice ticket */
	goInfo.pos[0].x += goInfo.dm[0].width + 1;
	goInfo.srcpos[0].y = goInfo.dm[0].height * 3;
	goInfo.dwID = OBJID_TICKET_PLAYERSBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #2: Add the special ticket buttons frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_SPECIALTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	nFrameX = goInfo.pos[0].x = 475;
	nFrameY = goInfo.pos[0].y = 73;

	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_BUTTONFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #3: Add the special ticket buttons(relative to frame) */
	sid = SURFACEID_BUTTON_SPECIALTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.dm[1].height = goInfo.dm[0].height /= 2;
	goInfo.dm[1].width = goInfo.dm[0].width /= 4;
	goInfo.pos[1].x = goInfo.pos[0].x += 13;
	goInfo.pos[1].y = goInfo.pos[0].y += 17;
	goInfo.srcpos[1].y = goInfo.dm[0].height;
	goInfo.lpdds[1] = goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	/* #4: Top and bottom button */
	goInfo.dwID = OBJID_SPECIALTICKET_TOPANDBOTTOMBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #5: Left and right button */
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 8;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width;
	goInfo.dwID = OBJID_SPECIALTICKET_LEFTANDRIGHTBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #6: Edge button */
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 8;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 2;
	goInfo.dwID = OBJID_SPECIALTICKET_EDGEBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #7: Odd or even button */
	goInfo.pos[1].y = goInfo.pos[0].y += goInfo.dm[0].height + 8;
	goInfo.srcpos[1].x = goInfo.srcpos[0].x = goInfo.dm[0].width * 3;
	goInfo.dwID = OBJID_SPECIALTICKET_ODDOREVENBTN;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #8: Top and bottom icon */
	ZERO_OUT(goInfo);
	sid = SURFACEID_ICON_SPECIAL_TB;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.pos[0].x = nFrameX + 93;
	goInfo.pos[0].y = nFrameY + 15;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_TOPANDBOTTOMICON;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #9: Left and right icon */
	sid = SURFACEID_ICON_SPECIAL_LR;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.pos[0].y += 44;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_LEFTANDRIGHTICON;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #10: Edge icon */
	sid = SURFACEID_ICON_SPECIAL_EDGE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.pos[0].y += 44;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_EDGEICON;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* #11: Odd or even icon */
	sid = SURFACEID_ICON_SPECIAL_OE;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);
	goInfo.pos[0].y += 44;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_ODDOREVENICON;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the blue background */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_SPECIAL;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 93;
	goInfo.pos[0].y = 84;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_SPECIALTICKETBG;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the ticket info frame */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FRAME_TICKETINFO;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 89;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_INFOFRAME;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the Special ticket label */
	ZERO_OUT(goInfo);
	sid = SURFACEID_LABEL_SPECIALTICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 104;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_SPECIALTICKET_LABEL;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* Add the red bet amount background */
	sid = SURFACEID_BACKGROUND_BET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width, goInfo.dm[0].height);

	goInfo.pos[0].x = 360;
	goInfo.pos[0].y = 92;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwID = OBJID_TICKET_BETBACKGROUND;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault),nState,&goInfo))
		return 0;

	/* The ticket */
	ZERO_OUT(goInfo);
	sid = SURFACEID_BACKGROUND_TICKET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;
	goInfo.dwFlags |= GOF_CLICKABLE;

	goInfo.pos[0].x = 101;
	goInfo.pos[0].y = 130;
	goInfo.dwID = OBJID_TICKET;

	if (!KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), 0,&goInfo))
		return 0;

	/* Change ticket transparency key of ticket to something not likley to occur */
	DDCOLORKEY col_key;

	col_key.dwColorSpaceLowValue = 99999;
	col_key.dwColorSpaceHighValue = 99999;
	
	goInfo.lpdds[0]->SetColorKey(DDCKEY_SRCBLT,&col_key);

	/* Scrolling text for the special ticket */
	ZERO_OUT(goInfo);

	goInfo.pos[0].x = 15;
	goInfo.pos[0].y = 435;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dwFlags |= GOF_SCROLLINGTEXT;

	CreateScrollingTextSurface(pgg,"PLEASE CHOOSE FROM ONE OF OUR FOUR SPECIAL TICKETS.",&goInfo.lpdds[0],&goInfo.dm[0].width,&goInfo.dm[0].height);

	goInfo.dmresize[0].width = 442;
	goInfo.dmresize[0].height = goInfo.dm[0].height;
	goInfo.dwWorkValue2 = 5;

	if (KP_AddObject(pgg,&(pgg->gs[nState].ObjDefault), nState,&goInfo) == NULL)
		return 0;

	return 1;

}

void UpdateObjects(GAME_GLOBAL *pgg)
/*
** UpdateObjects()
** This function is called after the loop to update the bet meters and various text items
*/
{
	GAME_OBJECT *curr;

	curr = KP_FindObject(pgg,&pgg->kenodata.ObjHead,OBJID_TICKET_CREDITAMOUNT);

	if (!curr)
	/* Hope we never get here! */
		return;

	if ( (*(pgg->kenodata.lpnCredits)) != curr->dwWorkValue)
	/* Time to update the credit amount */
	{
		curr->dwWorkValue = (*(pgg->kenodata.lpnCredits));
		DrawMeter(curr,(*(pgg->kenodata.lpnCredits)));

		/* HACK: Update the bet & won amounts here too */
		DrawMeter(KP_FindObject(pgg,&pgg->kenodata.ObjHead,OBJID_TICKET_BETAMOUNT),0);
		DrawMeter(KP_FindObject(pgg,&pgg->kenodata.ObjHead,OBJID_TICKET_WONAMOUNT),0);
	}
}

int	DrawMeter(GAME_OBJECT *pgo, unsigned int nAmount)
/*
** DrawMeter()
** This function draws the amount specified on the object specified in the form: $1,234.56
** Returns: 0 if sucessful
*/
{
	char amtbuf[32], ch;
	int count, pos, amtlen = 0,
		srcpos, srcwidth,
		srcposmap[] = { 94, 11, 18, 27, 39, 48, 56, 69, 77, 86 },
		srcwidthmap[] = { 8, 3, 7, 7, 8, 7, 8, 7, 8, 7 };
    DDSURFACEDESC ddsd;
	RECT rs, rd;
	LPDIRECTDRAWSURFACE lpddsfont = pgo->pgg->gst[SURFACEID_FONT_METERNBRS].lpdds;

    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_HEIGHT | DDSD_WIDTH;
	
	/* First, clear destination surface */
	KP_FillSurface(pgo->lpdds[0],0);

	/* Output amount to string for easier parsing */
	amtlen = sprintf(amtbuf,"%2.2f",(float)nAmount / 100);

	/* Get the dimensions of the surface to be drawn to */
	pgo->lpdds[0]->GetSurfaceDesc(&ddsd);
	/* KP_ODS("amtbuf=%s,width=%d,height=%d",amtbuf,ddsd.dwWidth,ddsd.dwHeight); */

	pos = ddsd.dwWidth - 1;

	/* Create the border */

	/* On the top */
	rs.left = 1;
	rs.right = 3;
	rs.top = 0;
	rs.bottom = 1;

	rd.left = 0;
	rd.right = pos;
	rd.top = 0;
	rd.bottom = 1;

	pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);

	/* On the bottom */
	rd.top = ddsd.dwHeight - 2;
	rd.bottom = ddsd.dwHeight - 1;

	pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);

	/* On the right */
	rs.left = 0;
	rs.right = 1;
	rs.top = 0;
	rs.bottom = ddsd.dwHeight - 1;

	rd.left = pos - 1;
	rd.right = pos;
	rd.top = 0;
	rd.bottom = ddsd.dwHeight - 1;

	pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);

	pos--;

	for (count = amtlen; count >= 0; count--)
	/* Parse the amount and draw it to the surface */
	{
		ch = amtbuf[count];

		if (ch == '$')
		{
			srcpos = 1;
			srcwidth = 6;
		}
		else if (ch == ',')
		{
			srcpos = 35;
			srcwidth = 3;
		}
		else if (ch == '.')
		{
			srcpos = 65;
			srcwidth = 3;
		}
		else if (ch >= '0' && ch <= '9')
		{
			/* 0 for 0, 1 for 1, etc... */
			ch -= '0';
			
			srcpos = srcposmap[ch];
			srcwidth = srcwidthmap[ch];
		}
		else
			continue;

		/* Blit the number/punctuation mark to the object's surface */
		pos -= srcwidth;

		if (pos < 0)
			return -1;

		rs.left = srcpos;
		rs.right = rs.left + srcwidth;
		rs.top = 0;
		rs.bottom = ddsd.dwHeight - 1;

		rd.left = pos;
		rd.right = rd.left + srcwidth;
		rd.top = 0;
		rd.bottom = ddsd.dwHeight - 1;

		pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);
	}

	/* Last, blit the dollar sign */
	rs.left = 0;
	rs.right = 7;
	rs.top = 0;
	rs.bottom = ddsd.dwHeight - 1;

	rd.left = 0;
	rd.right = 7;
	rd.top = 0;
	rd.bottom = ddsd.dwHeight - 1;

	pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);

	return 0;
}

int	DrawBetAmount(GAME_OBJECT *pgo, unsigned int nAmount)
/*
** DrawBetAmount()
** This function draws the amount specified on the object specified in the form: $1,234.56
** Returns: 0 if sucessful
*/
{
	char amtbuf[32], ch;
	int count, pos, amtlen = 0,
		srcpos, srcwidth,
		srcposmap[] = { 14, 28, 37, 50, 67, 80, 91, 103, 115, 127 },
		srcwidthmap[] = { 9, 4, 9, 8, 10, 8, 9, 9, 10, 9 };
    DDSURFACEDESC ddsd;
	RECT rs, rd;
	LPDIRECTDRAWSURFACE lpddsfont = pgo->pgg->gst[SURFACEID_FONT_TICKETBET].lpdds;

    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_HEIGHT | DDSD_WIDTH;
	
	/* First, clear destination surface */
	KP_FillSurface(pgo->lpdds[0],0);

	/* Output amount to string for easier parsing */
	amtlen = sprintf(amtbuf,"%2.2f",(float)nAmount / 100);

	/* Get the dimensions of the surface to be drawn to */
	pgo->lpdds[0]->GetSurfaceDesc(&ddsd);
	KP_ODS("amtbuf=%s,width=%d,height=%d",amtbuf,ddsd.dwWidth,ddsd.dwHeight);

	pos = ddsd.dwWidth - 1;

	for (count = amtlen; count >= 0; count--)
	/* Parse the amount and draw it to the surface */
	{
		ch = amtbuf[count];

		if (ch == '$')
		{
			srcpos = 2;
			srcwidth = 8;
		}
		else if (ch == '.')
		{
			srcpos = 61;
			srcwidth = 4;
		}
		else if (ch >= '0' && ch <= '9')
		{
			/* 0 for 0, 1 for 1, etc... */
			ch -= '0';
			
			srcpos = srcposmap[ch];
			srcwidth = srcwidthmap[ch];
		}
		else
			continue;

		/* Blit the number/punctuation mark to the object's surface */
		pos -= srcwidth;

		if (pos < 0)
			return -1;

		rs.left = srcpos;
		rs.right = rs.left + srcwidth;
		rs.top = 0;
		rs.bottom = ddsd.dwHeight - 1;

		rd.left = pos;
		rd.right = rd.left + srcwidth;
		rd.top = 0;
		rd.bottom = ddsd.dwHeight - 1;

		pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);
	}

	/* Last, blit the dollar sign */
	rs.left = 2;
	rs.right = 10;
	rs.top = 0;
	rs.bottom = ddsd.dwHeight - 1;

	rd.left = 2;
	rd.right = 10;
	rd.top = 0;
	rd.bottom = ddsd.dwHeight - 1;

	pgo->lpdds[0]->Blt(&rd, lpddsfont, &rs, DDBLT_WAIT, NULL);

	return 0;
}

void ChangeCredits(GAME_GLOBAL *pgg, unsigned int credits)
/*
** ChangeCredits()
** Call this function to change the credit amount(so the screen can be updated on the next frame)
*/
{
	*pgg->kenodata.lpnCredits = credits;
	UpdateObjects(pgg);
}

int CreateTicketSpecificObjects(GAME_GLOBAL *pgg, KENO_TICKET *pTkt)
/*
** CreateTicketSpecificObjects()
** This function will create all objects for a specific ticket, such as the bet amount, the X's, etc...
** Returns 0 if successful
*/
{
	GAME_OBJECT *curr, goInfo, *pgoTicket = KP_FindObject(pgg,&(pgg->gs[GAME_STATE_QUICKPICK_TICKET].ObjDefault),OBJID_TICKET);
	int sid, count, count2, x, y;

	/* #1: Clear the current list */
	while (pTkt->ObjHead.next)
	{
		KP_ODS("CTSO: Removing objects, pTkt->ObjHead.next == %X",pTkt->ObjHead.next);
		KP_RemoveObjectPtr(pgg,&(pTkt->ObjHead),pTkt->ObjHead.next);
	}
	
	/* #2: Create the bet amount */
	ZERO_OUT(goInfo);
	sid = SURFACEID_FONT_TICKETBET;
	KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
	goInfo.dwID = OBJID_TICKET_TICKETBETAMOUNT;
	goInfo.pos[0].x = 365;
	goInfo.pos[0].y = 95;
	goInfo.dm[0].width = 90;

	/* Try to obtain our bet amount work surface from the pool, if we can't find it, then add it to the pool */
	goInfo.lpdds[0] = pgg->lpddsTemporary[goInfo.dwID];

	if (!goInfo.lpdds[0])
	/* Initialize this surface */
	{
		if (KP_CreateBlankSurface(pgg,&goInfo.lpdds[0],goInfo.dm[0].width,goInfo.dm[0].height,0)
			!= DD_OK)
			return 1;

		/* Keep this surface for later use */
		pgg->lpddsTemporary[goInfo.dwID] = goInfo.lpdds[0];
	}

	curr = KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);

	if (!curr)
	/* Could not create bet amount object */
		return 1;
	else
	/* Got the bet amount! Now add the bet amount to the surface */
	{
		DrawBetAmount(curr,pTkt->nBet);
		curr->dwWorkValue = pTkt->nBet;
	}

	ZERO_OUT(goInfo);
	sid = SURFACEID_ICON_TICKET;
	goInfo.dwID = OBJID_STATIC;
	goInfo.dm[0].width = 30;
	goInfo.dm[0].height = 30;
	goInfo.lpdds[0] = pgg->gst[sid].lpdds;

	/* #2: Add any X's over the numbers(For Quick Pick and Straight tickets) */
	if (!pgoTicket)
	{
		KP_ODS("CreateTicketSpecificObjects(): pgoTicket is NULL!");
		return 1;
	}

	if (pTkt->nType == TICKET_TYPE_QUICKPICK || pTkt->nType == TICKET_TYPE_STRAIGHT)
	{
		int number, numberx;

		for (count = 0; count < 21 && pTkt->nNumbers[1][count]; count++)
		/* Get those numbers! And coordinates! */
		{
			number = numberx = pTkt->nNumbers[1][count];

			/* Get the physical coordinates of number */
			GetCoordsForNumber(number,(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
			goInfo.pos[0].x += pgoTicket->pos[0].x;
			goInfo.pos[0].y += pgoTicket->pos[0].y;

			if (number <= 20)
			/* First row of X icons */
				goInfo.srcpos[0].y = 57;
			else if (number > 20 && number <= 40)
			/* Second row */
			{
				goInfo.srcpos[0].y = 143;
				numberx -= 20;
			}
			else if (number > 40 && number <= 60)
			/* Third row */
			{
				goInfo.srcpos[0].y = 229;
				numberx -= 40;
			}
			else if (number > 60 && number <= 80)
			/* Last row */
			{
				goInfo.srcpos[0].y = 315;
				numberx -= 60;
			}
			else
			/* How did we get here!? */
			{
				KP_ODS("Invalid number found while creating X's!");
				return 1;
			}

			/* TODO: Use a X-coordinate map */
			goInfo.srcpos[0].x = (numberx - 1) * 31;

			KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);

			if (pTkt->nType == TICKET_TYPE_STRAIGHT)
				KP_ODS("Adding an X for #%d",number);
		}

		/* count = number of numbers selected */
		if (count > 1 && (count <= 10 || count == 20))
		{
			ZERO_OUT(goInfo);
			sid = SURFACEID_LABEL_220SPOT;
			KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
			goInfo.dwID = OBJID_STATIC;
			goInfo.pos[0].x = 247;
			goInfo.pos[0].y = 102;
			goInfo.dm[0].height /= 10;
			goInfo.lpdds[0] = pgg->gst[sid].lpdds;

			if (count == 20)
			{
				goInfo.srcpos[0].y = goInfo.dm[0].height * 9;
			}
			else
				goInfo.srcpos[0].y = (count - 2) * goInfo.dm[0].height;

			KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
		}
	}
	else if (pTkt->nType == TICKET_TYPE_WAYTICKET || pTkt->nType == TICKET_TYPE_PLAYERS)
	/* Way ticket or variation */
	{
		int number, numberx;

		ZERO_OUT(goInfo);
		sid = SURFACEID_ICON_WAYLETTERS;
		KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
		goInfo.dwID = OBJID_STATIC;
		goInfo.dm[0].width /= 20;
		goInfo.lpdds[0] = pgg->gst[sid].lpdds;

		for (count = 1; count <= pTkt->nGroupCount; count++)
		/* Get those numbers! And coordinates! */
		{
			/* Get the appropriate way letter for the group */
			goInfo.srcpos[0].x = (count - 1) * goInfo.dm[0].width;

			for (count2 = 0; pTkt->nNumbers[count][count2] && count2 < 21; count2++)
			/* Go through each group */
			{
				number = numberx = pTkt->nNumbers[count][count2];

				/* Get the physical coordinates of number */
				GetCoordsForNumber(number,(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
				goInfo.pos[0].x += pgoTicket->pos[0].x;
				goInfo.pos[0].y += pgoTicket->pos[0].y;
				
				KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
			}
		}

		if (pTkt->nType == TICKET_TYPE_PLAYERS)
		/* Add the players choice label */
		{
			int nPCType = 0;

			ZERO_OUT(goInfo);
			sid = SURFACEID_LABEL_PLAYERSTYPE;
			KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
			goInfo.dwID = OBJID_STATIC;
			goInfo.pos[0].x = 264;
			goInfo.pos[0].y = 98;
			goInfo.dm[0].height /= 8;
			goInfo.lpdds[0] = pgg->gst[sid].lpdds;

			if (pTkt->nSubType == TICKET_SUBTYPE_190WAY8_B)
				nPCType = 1;
			else if (pTkt->nSubType == TICKET_SUBTYPE_120WAY10)
				nPCType = 2;
			else if (pTkt->nSubType == TICKET_SUBTYPE_108S)
				nPCType = 3;
			else if (pTkt->nSubType == TICKET_SUBTYPE_810S)
				nPCType = 4;
			else if (pTkt->nSubType == TICKET_SUBTYPE_HORIZONTALROWS)
				nPCType = 5;
			else if (pTkt->nSubType == TICKET_SUBTYPE_DEALERSPECIAL)
				nPCType = 6;
			else if (pTkt->nSubType == TICKET_SUBTYPE_VERTICALROWS)
				nPCType = 7;

			goInfo.srcpos[0].y = nPCType * goInfo.dm[0].height;

			KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
		}
	}
	else if (pTkt->nType == TICKET_TYPE_SPECIAL)
	/* Special ticket */
	{
		int number, count, count2;

		ZERO_OUT(goInfo);
		sid = SURFACEID_ICON_SPECIAL_LETTERS;
		KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
		goInfo.dwID = OBJID_STATIC;
		goInfo.dm[0].width /= 4;
		goInfo.lpdds[0] = pgg->gst[sid].lpdds;

		if (pTkt->nSubType == TICKET_SUBTYPE_TOPANDBOTTOM)
		/* Top and bottom ticket */
		{
			for (count = 1; count <= 40; count++)
			{
				GetCoordsForNumber(count,(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
				goInfo.pos[0].x += pgoTicket->pos[0].x + 1;
				goInfo.pos[0].y += pgoTicket->pos[0].y;
				
				KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
			}
		}
		else if (pTkt->nSubType == TICKET_SUBTYPE_LEFTANDRIGHT)
		/* Left and right ticket */
		{
			goInfo.srcpos[0].x = goInfo.dm[0].width;

			count = 0;

			while (count <= 70)
			{
				for (count2 = 1; count2 <= 5; count2++)
				/* Get all numbers on the left */
				{
					number = count + count2;

					GetCoordsForNumber(number,(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
					goInfo.pos[0].x += pgoTicket->pos[0].x + 1;
					goInfo.pos[0].y += pgoTicket->pos[0].y;
					
					KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
				}

				count += 10;
			}
		}
		else if (pTkt->nSubType == TICKET_SUBTYPE_EDGE)
		/* Edge ticket */
		{
			goInfo.srcpos[0].x = goInfo.dm[0].width * 2;

			int nbrs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 20, 21, 30, 31, 40, 41, 50, 51,
				60, 61, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 0 };

			for (count = 0; nbrs[count]; count++)
			/* Add the edge numbers */
			{
				GetCoordsForNumber(nbrs[count],(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
				goInfo.pos[0].x += pgoTicket->pos[0].x + 1;
				goInfo.pos[0].y += pgoTicket->pos[0].y;
				
				KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
			}
		}
		else if (pTkt->nSubType == TICKET_SUBTYPE_ODDOREVEN)
		/* Odd or even ticket */
		{
			goInfo.srcpos[0].x = goInfo.dm[0].width * 3;

			for (count = 2; count <= 80; count += 2)
			{
				GetCoordsForNumber(count,(unsigned int*)&(goInfo.pos[0].x),(unsigned int*)&(goInfo.pos[0].y));
				goInfo.pos[0].x += pgoTicket->pos[0].x + 1;
				goInfo.pos[0].y += pgoTicket->pos[0].y;
				
				KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
			}
		}

		/* Add the special type label */
		ZERO_OUT(goInfo);
		sid = SURFACEID_LABEL_SPECIALTYPE;
		KP_GETBMPSIZE(pgg,sid,goInfo.dm[0].width,goInfo.dm[0].height);
		goInfo.dwID = OBJID_STATIC;
		goInfo.pos[0].x = 247;
		goInfo.pos[0].y = 102;
		goInfo.dm[0].height /= 7;
		goInfo.lpdds[0] = pgg->gst[sid].lpdds;

		if (pTkt->nSubType == TICKET_SUBTYPE_TOPANDBOTTOM)
			goInfo.srcpos[0].y = 0;
		else if (pTkt->nSubType == TICKET_SUBTYPE_LEFTANDRIGHT)
			goInfo.srcpos[0].y = goInfo.dm[0].height * 2;
		else if (pTkt->nSubType == TICKET_SUBTYPE_EDGE)
			goInfo.srcpos[0].y = goInfo.dm[0].height * 6;
		else if (pTkt->nSubType == TICKET_SUBTYPE_ODDOREVEN)
			goInfo.srcpos[0].y = goInfo.dm[0].height * 5;

		KP_AddObject(pgg,&(pTkt->ObjHead), 0,&goInfo);
	}

	if (pTkt == &(pgg->kenodata.tickets[pgg->kenodata.nWorkTicket]) &&
		pgg->nState != GAME_STATE_STARTUP)
	{
		pgg->gs[pgg->nState].ObjHead.next = pTkt->ObjHead.next;
	}

	return 0;
}

void GetCoordsForNumber(unsigned int nNumber, unsigned int *xPos, unsigned int *yPos)
/*
** GetCoordsForNumber
** This function takes the number specified and fills xPos and yPos with the 
** relative X/Y coordinates for that number on the ticket.
*/
{
	if (nNumber < 1 || nNumber > 80)
	{
		*xPos = 0;
		*yPos = 0;
	}
	else
	{
		char nbrbuf[32];

		/* Print the number to the buffer for easy parsing */
		sprintf(nbrbuf,"%2.2d",nNumber);
		
		nbrbuf[0] -= '0';
		nbrbuf[1] -= '0';
		
		if (nbrbuf[1] == 0)
		/* Got 10, 20, etc... */
		{
			nbrbuf[0]--;
			nbrbuf[1] = 10;
		}

		*xPos = TktXCoords[nbrbuf[1]];
		*yPos = TktYCoords[nbrbuf[0]];
	}
}

int GetNumberFromCoords(unsigned int xPos, unsigned int yPos)
/*
** GetNumberFromCoords()
** This function will return the number clicked on by the mouse. The X/Y coordinates must be 
** relative to the ticket((0,0) == Upper left corner of ticket)
*/
{
	/* HACK: Hard-code the width & height of the ticket & numbers */
	int nNbrWidth = 32, nNbrHeight = 32, nTktWidth = 357, nTktHeight = 278;

	int count, nDigit1 = 0, nDigit2 = 0;
	char nbrbuf[32];

	if (xPos > nTktWidth || yPos > nTktHeight)
		return 0;

	for (count = 1; count <= 10; count++)
	/* Get closest X-coordinate */
	{
		if (xPos > TktXCoords[count] && xPos < (TktXCoords[count] + nNbrWidth))
		{
			nDigit2 = count;

			if (count == 10)
			/* Shift over to next 10 */
			{
				nDigit1++;
				nDigit2 = 0;
			}

			break;
		}
	}

	for (count = 0; count <= 9; count++)
	/* Get closest Y-coordinate */
	{
		if (yPos > TktYCoords[count] && yPos < (TktYCoords[count] + nNbrHeight))
		{
			nDigit1 += count;
			break;
		}
	}

	sprintf(nbrbuf,"%d%d",nDigit1,nDigit2);

	return atoi(nbrbuf);
}

void CreateQuickPick(KENO_TICKET *pTkt, int nSpots)
/*
** CreateQuickPick()
** Creates a Quick Pick ticket by assigning random numbers to the ticket
*/
{
	int count, count2, nNew;
	BOOL bDuplicate = FALSE;

	/* We don't need those old numbers */
	ZERO_OUT(pTkt->nNumbers);

	for (count = 0; count < nSpots; count++)
	{
		nNew = RandInt(1,80);

		bDuplicate = FALSE;

		for (count2 = 0; pTkt->nNumbers[1][count2]; count2++)
		/* See if number has been picked already */
		{
			if (nNew == pTkt->nNumbers[1][count2])
			/* Decrement outer loop count and try again */
			{
				count--;
				bDuplicate = TRUE;
				break;
			}
		}

		if (!bDuplicate)
			pTkt->nNumbers[1][count] = nNew;

	}

	pTkt->nGroupCount = 1;
}

void CreatePlayersChoiceTicket(KENO_TICKET *pTkt, int nSubType)
/*
** CreatePlayersChoiceTicket()
** Creates a player's choice ticket with the specified type
*/
{
	int count;

	/* We don't need those old numbers */
	ZERO_OUT(pTkt->nNumbers);

	switch (nSubType)
	{
		case TICKET_SUBTYPE_190WAY8_V:
		/* 190 Way 8(Vertical) */
		{
			int nbrs[22][4] =
			{
				{ 0, 0, 0, 0 },
				{ 1, 11, 21, 31 },
				{ 2, 12, 22, 32 },
				{ 3, 13, 23, 33 },
				{ 4, 14, 24, 34 },
				{ 5, 15, 25, 35 },
				{ 6, 16, 26, 36 },
				{ 7, 17, 27, 37 },
				{ 8, 18, 28, 38 },
				{ 9, 19, 29, 39 },
				{ 10, 20, 30, 40 },
				{ 41, 51, 61, 71 },
				{ 42, 52, 62, 72 },
				{ 43, 53, 63, 73 },
				{ 44, 54, 64, 74 },
				{ 45, 55, 65, 75 },
				{ 46, 56, 66, 76 },
				{ 47, 57, 67, 77 },
				{ 48, 58, 68, 78 },
				{ 49, 59, 69, 79 },
				{ 50, 60, 70, 80 },
				{ 0, 0, 0, 0 }
			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
				pTkt->nNumbers[count][3] = nbrs[count][3];
			}

			pTkt->nGroupCount = count;
		}
		break;
		case TICKET_SUBTYPE_190WAY8_B:
		/* 190 Way 8(Boxes) */
		{
			int nbrs[22][4] =
			{
				{ 0, 0, 0, 0 },
				{ 1, 2, 11, 12 },
				{ 3, 4, 13, 14 },
				{ 5, 6, 15, 16 },
				{ 7, 8, 17, 18 },
				{ 9, 10, 19, 20 },
				{ 21, 22, 31, 32 },
				{ 23, 24, 33, 34 },
				{ 25, 26, 35, 36 },
				{ 27, 28, 37, 38 },
				{ 29, 30, 39, 40 },
				{ 41, 42, 51, 52 },
				{ 43, 44, 53, 54 },
				{ 45, 46, 55, 56 },
				{ 47, 48, 57, 58 },
				{ 49, 50, 59, 60 },
				{ 61, 62, 71, 72 },
				{ 63, 64, 73, 74 },
				{ 65, 66, 75, 76 },
				{ 67, 68, 77, 78 },
				{ 69, 70, 79, 80 },
				{ 0, 0, 0, 0 }
			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
				pTkt->nNumbers[count][3] = nbrs[count][3];
			}

			pTkt->nGroupCount = count;
		}
		break;
		case TICKET_SUBTYPE_120WAY10:
		/* 120 Way 10 */
		{
			int nbrs[21][5] =
			{
				{ 0, 0, 0, 0, 0 },
				{ 1, 2, 3, 4, 5 },
				{ 6, 7, 8, 9, 10 },
				{ 11, 12, 13, 14, 15 },
				{ 16, 17, 18, 19, 20 },
				{ 21, 22, 23, 24, 25 },
				{ 26, 27, 28, 29, 30 },
				{ 31, 32, 33, 34, 35 },
				{ 36, 37, 38, 39, 40 },
				{ 41, 42, 43, 44, 45 },
				{ 46, 47, 48, 49, 50 },
				{ 51, 52, 53, 54, 55 },
				{ 56, 57, 58, 59, 60 },
				{ 61, 62, 63, 64, 65 },
				{ 66, 67, 68, 69, 70 },
				{ 71, 72, 73, 74, 75 },
				{ 76, 77, 78, 79, 80 }
			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
				pTkt->nNumbers[count][3] = nbrs[count][3];
				pTkt->nNumbers[count][4] = nbrs[count][4];
			}

			pTkt->nGroupCount = count;
		}
		break;
		case TICKET_SUBTYPE_108S:
		{
			int nbrs[21][9] =
			{
				{ 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 11, 21, 31, 41, 51, 61, 71 },
				{ 2, 12, 22, 32, 42, 52, 62, 72 },
				{ 3, 13, 23, 33, 43, 53, 63, 73 },
				{ 4, 14, 24, 34, 44, 54, 64, 74 },
				{ 5, 15, 25, 35, 45, 55, 65, 75 },
				{ 6, 16, 26, 36, 46, 56, 66, 76 },
				{ 7, 17, 27, 37, 47, 57, 67, 77 },
				{ 8, 18, 28, 38, 48, 58, 68, 78 },
				{ 9, 19, 29, 39, 49, 59, 69, 79 },
				{ 10, 20, 30, 40, 50, 60, 70, 80 }
			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
				pTkt->nNumbers[count][3] = nbrs[count][3];
				pTkt->nNumbers[count][4] = nbrs[count][4];
				pTkt->nNumbers[count][5] = nbrs[count][5];
				pTkt->nNumbers[count][6] = nbrs[count][6];
				pTkt->nNumbers[count][7] = nbrs[count][7];
			}

			pTkt->nGroupCount = count;
		}
		break;
		case TICKET_SUBTYPE_810S:
		{
			int nbrs[21][11] =
			{
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
				{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
				{ 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
				{ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 },
				{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 },
				{ 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 },
				{ 61, 62, 63, 64, 65, 66, 67, 68, 69, 70 },
				{ 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 }

			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
				pTkt->nNumbers[count][3] = nbrs[count][3];
				pTkt->nNumbers[count][4] = nbrs[count][4];
				pTkt->nNumbers[count][5] = nbrs[count][5];
				pTkt->nNumbers[count][6] = nbrs[count][6];
				pTkt->nNumbers[count][7] = nbrs[count][7];
				pTkt->nNumbers[count][8] = nbrs[count][8];
				pTkt->nNumbers[count][9] = nbrs[count][9];
			}

			pTkt->nGroupCount = count;
		}
		break;
		case TICKET_SUBTYPE_DEALERSPECIAL:
		{
			int nbrs[21][3] =
			{
				{ 0, 0, 0 },
				{ 31, 32, 33 },
				{ 38, 39, 40 },
				{ 41, 42, 43 },
				{ 48, 49, 50 }
			};

			for (count = 1; nbrs[count][0]; count++)
			/* Fill in the ticket */
			{
				pTkt->nNumbers[count][0] = nbrs[count][0];
				pTkt->nNumbers[count][1] = nbrs[count][1];
				pTkt->nNumbers[count][2] = nbrs[count][2];
			}

			pTkt->nGroupCount = count;
		}
		break;

	}

	pTkt->nSubType = nSubType;
}

int GetTicketGroup(KENO_TICKET *pTkt, int nNumber)
/*
** GetTicketGroup()
** This function finds the group for the specified number, and returns it.
** Returns -1 if the number is not on the ticket
*/
{
	int count, count2;

	/* Each ticket must have at least one group */
	if (pTkt->nGroupCount == 0)
		pTkt->nGroupCount = 1;

	for (count = 1; count <= pTkt->nGroupCount; count++)
	/* Go through each group */
	{
		for (count2 = 0; pTkt->nNumbers[count][count2] && count2 < 21; count2++)
		/* Match up the numbers */
		{
			if (pTkt->nNumbers[count][count2] == nNumber)
				return count;
		}
	}

	return -1;
}

int AddNumber(KENO_TICKET *pTkt, int nGroup, int nNumber)
/*
** AddNumber()
** This function adds the specified number to the specified group
** Returns: 1 if successful, -1 if too many numbers in group, 0 if failed for other reasons
*/
{
	int retval;

	/* Check to see if the number is already on the ticket */
	retval = GetTicketGroup(pTkt,nNumber);

	if (retval == -1)
	/* Number not on ticket */
	{
		int count;

		for (count = 0; count < 20; count++)
		{
			if (!pTkt->nNumbers[nGroup][count])
			/* Found the empty one */
			{
				pTkt->nNumbers[nGroup][count] = nNumber;
				return 1;
			}
		}

		/* Too many numbers */
			return -1;
	}
	else
		KP_ODS("AddNumber() attempted to add a number which already exists!");

	return 0;
}

int RemoveNumber(KENO_TICKET *pTkt, int nNumber)
/*
** RemoveNumber()
** This function removes the specified number from the specified ticket
** Returns 1 if number was there and removed, otherwise 0
*/
{
	int count, count2;
	BOOL bFound = FALSE;

	for (count = 1; count < 20; count++)
	/* Go through each group */
	{
		for (count2 = 0; count2 < 20; count2++)
		/* Find the number */
		{
			if (bFound)
			/* Shift the remaining numbers to the left */
			{
				pTkt->nNumbers[count][count2 - 1] = pTkt->nNumbers[count][count2];
				pTkt->nNumbers[count][count2] = 0;
			}
			else
			{
				if (pTkt->nNumbers[count][count2] == nNumber)
				/* Found it */
				{
					pTkt->nNumbers[count][count2] = 0;
					bFound = TRUE;
				}
			}
		}

		if (bFound)
			return 1;
	}

	return 0;
}

HRESULT	CreateScrollingTextSurface(GAME_GLOBAL *pgg, char *pszText, LPDIRECTDRAWSURFACE *lplpdds, unsigned short *pnWidth, unsigned short *pnHeight)
/*
** CreateScrollingTextSurface()
** Creates a surface with the scrolling text font using the text specified.
**
** Returns 0 if sucessful, and fills in:
** pnWidth = The width of the new surface
** pnHeight = The height of the new surface
*/
{
	char ch;
	int count, nWidth = 0, nHeight = 0;
    DDSURFACEDESC ddsd;
	LPDIRECTDRAWSURFACE lpdds = NULL;
	DDCOLORKEY col_key;
	HRESULT hr = NULL;
	RECT SrcRect, DestRect;

	for (count = 0; pszText[count]; count++)
	/* Step #1: Determine the width and height of the new surface */
	{
		ch = pszText[count];
		
		if (ch == '!' || ch == ',' || ch == '.')
		/* Special width for punctuation */
			nWidth += 20;
		else
		/* Default width is 24 pixels */
			nWidth += 24;
	}

	nHeight = 28;

	/* Step #2: Create the surface */
	if (hr = KP_CreateBlankSurface(pgg,&lpdds,nWidth,nHeight,0) != DD_OK)
	{
		MessageBox(pgg->hWnd,"Unable to create scrolling text surface!","Error",MB_OK);
		return hr;
	}

	SrcRect.top = DestRect.top = 0;
	SrcRect.bottom = DestRect.bottom = nHeight;
	DestRect.left = 0;

	for (count = 0; pszText[count]; count++)
	/* Step #3: Fill in the surface with the text */
	{
		ch = pszText[count];

		if (ch == ' ')
		{
			DestRect.left += 24;
			continue;
		}
		if (ch == '!')
		{
			SrcRect.left = 36 * 24;
			SrcRect.right = SrcRect.left + 20;
		}
		else if (ch == ',')
		{
			SrcRect.left = (36 * 24) + (1 * 20);
			SrcRect.right = SrcRect.left + 20;
		}
		else if (ch == '.')
		{
			SrcRect.left = (36 * 24) + (2 * 20);
			SrcRect.right = SrcRect.left + 18;
		}
		else if (ch >= '0' && ch <= '9')
		{
			SrcRect.left = (24 * (ch - '0'));
			SrcRect.right = SrcRect.left + 24;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			SrcRect.left = (24 * (ch - 'A' + 10));
			SrcRect.right = SrcRect.left + 24;
		}
		else
		{
			KP_ODS("CreateScrollingTextSurface() failed! Invalid character in string: %d",(int)ch);
			return FALSE;
		}

		DestRect.right = DestRect.left + (SrcRect.right - SrcRect.left);

		hr = lpdds->Blt(&DestRect,pgg->gst[SURFACEID_FONT_SCROLLINGTEXT].lpdds,&SrcRect,DDBLT_WAIT,NULL);

		if (FAILED(hr))
		/* Unable to blit the letter */
		{
			int count;

			KP_ODS("Unable to Blt letter '%d', error #%x",ch,(unsigned int)hr);
			KP_ODS("d(t=%d,l=%d,b=%d,r=%d),s(t=%d,l=%d,b=%d,r=%d)",
				DestRect.top,
				DestRect.left,
				DestRect.bottom,
				DestRect.right,
				SrcRect.top,
				SrcRect.left,
				SrcRect.bottom,
				SrcRect.right);
		}

		DestRect.left = DestRect.right;
	}

	/* Copy the correct information to the output parameters */
	*lplpdds = lpdds;
	*pnWidth = nWidth;
	*pnHeight = nHeight;

	return DD_OK;

}

int ShowTicket(GAME_GLOBAL *pgg, int nTicket)
/*
** ShowTicket()
** Will show the specified ticket on the screen
** Returns 0 if sucessful
*/
{
	KENO_TICKET *pTkt = &(pgg->kenodata.tickets[nTicket]),
				*pWorkTkt = &(pgg->kenodata.tickets[pgg->kenodata.nWorkTicket]);
	GAME_OBJECT *curr = NULL;

	int nState = 0;

	/* Switch context of work ticket to the specified ticket */
	memcpy(pWorkTkt,pTkt,sizeof(*pTkt));


	if (pTkt->nType == TICKET_TYPE_QUICKPICK)
		nState = GAME_STATE_QUICKPICK_TICKET;
	else if (pTkt->nType == TICKET_TYPE_SPECIAL)
		nState = GAME_STATE_SPECIAL_TICKET;
	else if (pTkt->nType == TICKET_TYPE_WAYTICKET)
		nState = GAME_STATE_WAY_TICKET;
	else if (pTkt->nType == TICKET_TYPE_PLAYERS)
		nState = GAME_STATE_PLAYERS_TICKET;
	else
	/* Default ticket is a straight ticket */
		nState = GAME_STATE_STRAIGHT_TICKET;
		
	pgg->nState = nState;
	pgg->gs[nState].ObjHead.next = pTkt->ObjHead.next;

	/* Update the bet amount */
	curr = KP_FindObject(pgg,&(pTkt->ObjHead),OBJID_TICKET_TICKETBETAMOUNT);

	if (curr)
		DrawBetAmount(curr,pTkt->nBet);

	//CreateTicketSpecificObjects(pgg,pWorkTkt);

	return 0;
}

int SaveTicket(GAME_GLOBAL *pgg, int nTicket)
/*
** SaveTicket()
** Will save the work ticket to the ticket specified
** Returns 0 if sucessful
*/
{

	KENO_TICKET *pTkt = &(pgg->kenodata.tickets[nTicket]),
				*pWorkTkt = &(pgg->kenodata.tickets[pgg->kenodata.nWorkTicket]);


	/* Save the context of the work ticket to the ticket specified */
	memcpy(pTkt,pWorkTkt,sizeof(*pTkt));

	SetTicketTab(pgg,nTicket,TICKET_TAB_SAVED,FALSE);

	return 0;
}

int SetTicketTab(GAME_GLOBAL *pgg, int nTicket, int nType, BOOL bBright)
/*
** SetTicketTab()
** This function will set the ticket view objects at the top to the type specified
** Returns 0 if sucessful
*/
{
	GAME_OBJECT *pgoTktTab = NULL;
	int dwID = nTicket;

	/* NOTE: An assumption is made here that OBJID_TICKET_ONE...etc are in sequence! */
	dwID += OBJID_TICKET_ONE;
	dwID -= 1;

	pgoTktTab = KP_FindObject(pgg,&(pgg->kenodata.ObjHead),dwID);

	if (!pgoTktTab)
		KP_ODS("FATAL ERROR: Unable to find ticket tab object for ticket #%d",nTicket);
	else
	{
		if (nType == TICKET_TAB_OPEN)
			pgoTktTab->srcpos[0].x = pgoTktTab->dm[0].width;
		else if (nType == TICKET_TAB_SAVED)
			pgoTktTab->srcpos[0].x = 0;
		else if (nType == TICKET_TAB_WON)
			pgoTktTab->srcpos[0].x = pgoTktTab->dm[0].width * 2;
		else if (nType != TICKET_TAB_DONTCHANGE)
			KP_ODS("Invalid ticket tab type passed for ticket %d(%d)",nTicket,nType);

		if (bBright)
			pgoTktTab->srcpos[0].y = pgoTktTab->dm[0].height;
		else
			pgoTktTab->srcpos[0].y = 0;
	}



	return 0;
}