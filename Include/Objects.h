/*
** Objects.h
**
** Contains all header information for game object functions.
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "Engine.h"
#include "Struct.h"
#include "Effects.h"

/* Macro functions */
#define RandInt(_min,_max) ( (_min) + (int)(rand()%((_max)-(_min)+1)))

extern	HRESULT SetupObjects(GAME_GLOBAL*);
extern	void DestroyObjects(GAME_GLOBAL*);
extern	int	 NotifyObject(GAME_OBJECT*, unsigned short, unsigned int);
extern	void UpdateObjects(GAME_GLOBAL*);
extern	HRESULT RestoreSurfaces(GAME_GLOBAL*, BOOL);
extern	int AddCommonTicketObjects(GAME_GLOBAL*, unsigned short);
extern	int	Setup_Startup(GAME_GLOBAL*, unsigned short);
extern	int	SetupTicket_QuickPick(GAME_GLOBAL*, unsigned short);
extern	int	SetupTicket_Straight(GAME_GLOBAL*, unsigned short);
extern	int	SetupTicket_Way(GAME_GLOBAL*, unsigned short);
extern	int	SetupTicket_PlayersChoice(GAME_GLOBAL*, unsigned short);
extern	int	SetupTicket_SpecialTicket(GAME_GLOBAL*, unsigned short);
extern	int	DrawMeter(GAME_OBJECT*, unsigned int);
extern	int DrawBetAmount(GAME_OBJECT*, unsigned int);
extern	void ChangeCredits(GAME_GLOBAL*, unsigned int);
extern	int CreateTicketSpecificObjects(GAME_GLOBAL*, KENO_TICKET*);
extern	void GetCoordsForNumber(unsigned int, unsigned int*, unsigned int*);
extern	int GetNumberFromCoords(unsigned int, unsigned int);
extern	void CreateQuickPick(KENO_TICKET*, int);
extern	void CreatePlayersChoiceTicket(KENO_TICKET*, int);
extern	int GetTicketGroup(KENO_TICKET*, int);
extern	int	AddNumber(KENO_TICKET*, int, int);
extern	int RemoveNumber(KENO_TICKET*, int);
extern	HRESULT	CreateScrollingTextSurface(GAME_GLOBAL*, char*, LPDIRECTDRAWSURFACE*, unsigned short*, unsigned short*);
extern	int	ShowTicket(GAME_GLOBAL*, int);
extern	int SaveTicket(GAME_GLOBAL*, int);

#define TICKET_TAB_OPEN	1
#define TICKET_TAB_SAVED 2
#define TICKET_TAB_WON 3
#define TICKET_TAB_DONTCHANGE 4
extern	int SetTicketTab(GAME_GLOBAL*, int, int, BOOL);

/*
** #define's for surface ID's go here
**
** NOTE: No surface ID can exceed MAX_SURFACES(defined in Struct.h), as they are mapped by the ID's to
** the global array(GAME_GLOBAL->gst) for quick lookups. If surface ID's must be insanely high numbers,
** then MAX_SURFACES *MUST* be equal or greater then the highest surface ID #.
*/

#define SURFACEID_BACKGROUND_STARTUP	1							/* "Keno Pro" background logo */
#define SURFACEID_BUTTON_STARTUP		2							/* Ticket buttons in beginning of game */
#define SURFACEID_FRAME_METERS			3							/* Bet, Won, and Credit meters */
#define SURFACEID_FRAME_SAVED			4							/* Saved tickets frame */
#define SURFACEID_FRAME_SCROLLTEXT		5							/* Scrolling text frame */
#define SURFACEID_FRAME_QUICKPICK		6							/* Quick Pick numbers frame */
#define SURFACEID_FRAME_STRAIGHT		7							/* Straight ticket text frame */
#define SURFACEID_BUTTON_TICKETTAB		8							/* Saved, Open, and Won tickets */
#define SURFACEID_BUTTON_CLEARSAVED		9							/* Clear saved tickets */
#define SURFACEID_BUTTON_TICKETTYPE		10							/* Ticket type buttons */
#define SURFACEID_BUTTON_GAMEINFO		11							/* Cashout, POW, Paytable, and Help buttons */
#define SURFACEID_BUTTON_GAMEPLAY		12							/* Save ticket, cancel, start game, autoplay buttons */
#define SURFACEID_BUTTON_MONEY			13							/* Bet denomination buttons */
#define SURFACEID_BACKGROUND_TICKET		14							/* Main ticket background */
#define SURFACEID_ICON_TICKET			15							/* Ticket markings icons */
#define SURFACEID_BACKGROUND_BET		16							/* Red bet amount background */
#define SURFACEID_FONT_TICKETBET		17							/* White ticket bet amount */
#define SURFACEID_FONT_METERNBRS		18							/* Meter numbers */
#define SURFACEID_LABEL_220SPOT			19							/* 2-20 spot label */
#define SURFACEID_LABEL_STRAIGHTTICKET	20							/* Purple "Straight ticket" label */
#define SURFACEID_LABEL_QUICKPICK		21							/* Green "Quick pick" label */
#define SURFACEID_BUTTON_QUICKPICK		22							/* Quick pick buttons */
#define SURFACEID_LABEL_WAYTICKET		23							/* Red "Way ticket" label */
#define SURFACEID_BUTTON_WAYTICKET		24							/* Way ticket buttons */
#define SURFACEID_BUTTON_GROUPIT		25							/* "Group it" buttons */
#define SURFACEID_ICON_WAYLETTERS		26							/* Way group letters */
#define SURFACEID_LABEL_PLAYERSCHOICE	27							/* Yellow "Player's choice" label */
#define SURFACEID_BUTTON_PLAYERSCHOICE	28							/* Player's choice buttons */
#define SURFACEID_LABEL_SPECIALTICKET	29							/* Blue "Special ticket" label */
#define SURFACEID_BUTTON_SPECIALTICKET	30							/* Special ticket buttons */
#define SURFACEID_ICON_SPECIAL_TB		31							/* "Top and Bottom" icon */
#define SURFACEID_ICON_SPECIAL_LR		32							/* "Left and Right" icon */
#define SURFACEID_ICON_SPECIAL_EDGE		33							/* "Edge" icon */
#define SURFACEID_ICON_SPECIAL_OE		34							/* "Odd or Even" icon */
#define SURFACEID_LABEL_CHANGEBET		35							/* "Change bet" label */
#define SURFACEID_FRAME_WAYTICKET		36							/* Way ticket buttons frame */
#define SURFACEID_FRAME_PCTICKET		37							/* Players choice buttons frame */
#define SURFACEID_FRAME_SPECIALTICKET	38							/* Special ticket buttons frame */
#define SURFACEID_BACKGROUND_QUICKPICK	39							/* The green quick pick background */
#define SURFACEID_BACKGROUND_STRAIGHT	40							/* The purple straight ticket background */
#define SURFACEID_BACKGROUND_SPECIAL	41							/* The blue special ticket background */
#define SURFACEID_BACKGROUND_WAYTICKET	42							/* The red way ticket background */
#define SURFACEID_BACKGROUND_PLAYERSTICKET	43						/* The yellow players choice ticket background */
#define SURFACEID_FRAME_TICKETINFO		44							/* The ticket info frame */
#define SURFACEID_LABEL_PLAYERSTYPE		45							/* Labels with type of players ticket */
#define SURFACEID_FONT_WAYNUMBERS		46							/* Way number font */
#define SURFACEID_ICON_SPECIAL_LETTERS	47							/* Special ticket letters */
#define SURFACEID_LABEL_SPECIALTYPE		48							/* Special type labels */
#define SURFACEID_FONT_SCROLLINGTEXT	49							/* Scrolling text font */
#define SURFACEID_BALLS					50							/* The keno balls */

/*
** #define's for object ID's go here
*/
#define BASE1 1
#define OBJID_STARTUP_BACKGROUND		(BASE1 + 1)					/* Startup background */
#define OBJID_STARTUP_STRAIGHT			(BASE1 + 2)					/* Straight ticket button */
#define OBJID_STARTUP_QUICKPICK			(BASE1 + 3)					/* Quick pick ticket button */
#define OBJID_STARTUP_WAY				(BASE1 + 4)					/* Way ticket button */
#define OBJID_STARTUP_SPECIAL			(BASE1 + 5)					/* Special ticket button */
#define OBJID_STARTUP_PLAYERSCHOICE		(BASE1 + 6)					/* Player's choice button */

/* Objects common to all tickets */
#define BASE2 10
#define OBJID_TICKET_SAVEDFRAME			BASE2 + 1							/* Saved tickets frame */
#define OBJID_TICKET_ONE				BASE2 + 2							/* Ticket #1 */
#define OBJID_TICKET_TWO				BASE2 + 3							/* Ticket #2 */
#define OBJID_TICKET_THREE				BASE2 + 4							/* Ticket #3 */
#define OBJID_TICKET_FOUR				BASE2 + 5							/* Ticket #4 */
#define OBJID_TICKET_FIVE				BASE2 + 6							/* Ticket #5 */
#define OBJID_TICKET_SIX				BASE2 + 7							/* Ticket #6 */
#define OBJID_TICKET_SEVEN				BASE2 + 8							/* Ticket #7 */
#define OBJID_TICKET_EIGHT				BASE2 + 9							/* Ticket #8 */
#define OBJID_TICKET_CLEARSAVED			BASE2 + 10							/* Clear saved tickets */
#define OBJID_TICKET_BETMETER			BASE2 + 11							/* Bet meter */
#define OBJID_TICKET_WONMETER			BASE2 + 12							/* Won meter */
#define OBJID_TICKET_CREDITMETER		BASE2 + 13							/* Credit meter */
#define OBJID_TICKET_CASHOUT			BASE2 + 14							/* Cash out button */
#define OBJID_TICKET_POW				BASE2 + 15							/* Proof-of-win button */
#define OBJID_TICKET_PAYTABLE			BASE2 + 16							/* Paytable button */
#define OBJID_TICKET_HELP				BASE2 + 17							/* Help button */
#define OBJID_TICKET_SCROLLINGTEXT		BASE2 + 18							/* Scrolling text frame */
#define OBJID_TICKET_SAVETICKET			BASE2 + 19							/* Save ticket button */
#define OBJID_TICKET_CANCEL				BASE2 + 20							/* Cancel ticket button */
#define OBJID_TICKET_STARTGAME			BASE2 + 21							/* Start game button */
#define OBJID_TICKET_AUTOPLAY			BASE2 + 22							/* Auto play button */
#define OBJID_TICKET_CHANGEBET			BASE2 + 23							/* Change bet label */
#define OBJID_TICKET_ONECENT			BASE2 + 24							/* One cent bet button */
#define OBJID_TICKET_FIVECENTS			BASE2 + 25							/* Five cent bet button */
#define OBJID_TICKET_ONEQUARTER			BASE2 + 26							/* Twenty-five cent bet button */
#define OBJID_TICKET_ONEDOLLAR			BASE2 + 27							/* One dollar bet button */
#define OBJID_TICKET					BASE2 + 28							/* The BASE2 + 1-80 number background */
#define OBJID_TICKET_BETBACKGROUND		BASE2 + 29							/* The bet background */
#define OBJID_TICKET_STRAIGHTBTN		BASE2 + 30							/* Straight ticket button */
#define OBJID_TICKET_WAYBTN				BASE2 + 31							/* Way ticket button */
#define OBJID_TICKET_QPBTN				BASE2 + 32							/* Quick pick button */
#define OBJID_TICKET_SPECIALBTN			BASE2 + 33							/* Special ticket button */
#define OBJID_TICKET_PLAYERSBTN			BASE2 + 34							/* Player's choice button */
#define OBJID_TICKET_BETAMOUNT			BASE2 + 35							/* Bet amount(in dollars) */
#define OBJID_TICKET_WONAMOUNT			BASE2 + 36							/* Won amount(in dollars) */
#define OBJID_TICKET_CREDITAMOUNT		BASE2 + 37							/* Credits amount(in dollars) */
#define OBJID_TICKET_INFOFRAME			BASE2 + 38							/* The black bar with the bet, etc... */
#define OBJID_TICKET_TICKETBETAMOUNT	BASE2 + 39							/* The ticket bet amount(white on red letters) */


/* Quick pick ticket objects */
#define BASE3	OBJID_TICKET_TICKETBETAMOUNT + 1

#define OBJID_QPTICKET_QPTICKETBG		BASE3 + 1							/* The green background */
#define OBJID_QPTICKET_LABEL			BASE3 + 2							/* The green "Quick pick" label */
#define OBJID_QPTICKET_BUTTONFRAME		BASE3 + 3							/* The quick pick buttons frame */
#define OBJID_QPTICKET_TWOSPOT			BASE3 + 4							/* Two spot button */
#define OBJID_QPTICKET_THREESPOT		BASE3 + 5							/* Three spot button */
#define OBJID_QPTICKET_FOURSPOT			BASE3 + 6							/* Four spot button */
#define OBJID_QPTICKET_FIVESPOT			BASE3 + 7							/* Five spot button */
#define OBJID_QPTICKET_SIXSPOT			BASE3 + 8							/* Six spot button */
#define OBJID_QPTICKET_SEVENSPOT		BASE3 + 9							/* Seven spot button */
#define OBJID_QPTICKET_EIGHTSPOT		BASE3 + 10							/* Eight spot button */
#define OBJID_QPTICKET_NINESPOT			BASE3 + 11							/* Nine spot button */
#define OBJID_QPTICKET_TENSPOT			BASE3 + 12							/* Ten spot button */
#define OBJID_QPTICKET_TWENTYSPOT		BASE3 + 13							/* Twenty spot button */

/* Straight ticket objects */
#define BASE4 OBJID_QPTICKET_TWENTYSPOT + 1
#define OBJID_STRAIGHTTICKET_LABEL		BASE4 + 1							/* The purple "Straight ticket" label */
#define OBJID_STRAIGHTTICKET_STRAIGHTBG	BASE4 + 2							/* The purple background */

/* Way ticket objects */
#define BASE5 OBJID_STRAIGHTTICKET_STRAIGHTBG + 1
#define OBJID_WAYTICKET_WAYTICKETBG		BASE5 + 1							/* The way ticket background */
#define OBJID_WAYTICKET_LABEL			BASE5 + 2							/* The red "Way ticket" label */
#define OBJID_WAYTICKET_BUTTONFRAME		BASE5 + 3							/* The way buttons frame */
#define OBJID_WAYTICKET_TWOWAY			BASE5 + 4							/* Two ways button */
#define OBJID_WAYTICKET_THREEWAY		BASE5 + 5							/* Three ways button */
#define OBJID_WAYTICKET_FOURWAY			BASE5 + 6							/* Four ways button */
#define OBJID_WAYTICKET_FIVEWAY			BASE5 + 7							/* Five ways button */
#define OBJID_WAYTICKET_SIXWAY			BASE5 + 8							/* Six ways button */
#define OBJID_WAYTICKET_SEVENWAY		BASE5 + 9							/* Seven ways button */
#define OBJID_WAYTICKET_EIGHTWAY		BASE5 + 10							/* Eight ways button */
#define OBJID_WAYTICKET_NINEWAY			BASE5 + 11							/* Nine ways button */
#define OBJID_WAYTICKET_TENWAY			BASE5 + 12							/* Ten ways button */
#define OBJID_WAYTICKET_TWENTYWAY		BASE5 + 13							/* Twenty ways button */
#define OBJID_WAYTICKET_GROUPIT			BASE5 + 14							/* Group it button */

/* Players choice objects */
#define BASE6 OBJID_WAYTICKET_GROUPIT + 1
#define OBJID_PCTICKET_PCTICKETBG		BASE6 + 1							/* The players choice ticket background */
#define OBJID_PCTICKET_LABEL			BASE6 + 2							/* The yellow "Players choice" label */
#define OBJID_PCTICKET_BUTTONFRAME		BASE6 + 3							/* The players choice buttons frame */
#define OBJID_PCTICKET_190WAY8_V		BASE6 + 4							/* 190 way 8(vertical) button */
#define OBJID_PCTICKET_190WAY8_B		BASE6 + 5							/* 190 way 8(boxes) button */
#define OBJID_PCTICKET_120WAY10			BASE6 + 6							/* 120 way 10 button */
#define OBJID_PCTICKET_810S				BASE6 + 7							/* 8 10's button */
#define OBJID_PCTICKET_108S				BASE6 + 8							/* 10 8's button */
#define OBJID_PCTICKET_HORIZONTALROWS	BASE6 + 9							/* Horizontal rows button */
#define OBJID_PCTICKET_DEALERSPECIAL	BASE6 + 10							/* Dealers special button */
#define OBJID_PCTICKET_VERTICALROWS		BASE6 + 11							/* Vertical rows button */

/* Special ticket objects */
#define BASE7 OBJID_PCTICKET_VERTICALROWS + 1
#define OBJID_SPECIALTICKET_SPECIALTICKETBG	BASE7 + 1						/* The blue special ticket background */
#define OBJID_SPECIALTICKET_LABEL		BASE7 + 2							/* The blue "Special ticket" label */
#define OBJID_SPECIALTICKET_BUTTONFRAME	BASE7 + 3							/* The special ticket buttons frame */
#define OBJID_SPECIALTICKET_TOPANDBOTTOMBTN	BASE7 + 4						/* The "top and bottom" button */
#define OBJID_SPECIALTICKET_TOPANDBOTTOMICON	BASE7 + 5					/* The top and bottom icon */
#define OBJID_SPECIALTICKET_LEFTANDRIGHTBTN	BASE7 + 6						/* The "left and right" button */
#define OBJID_SPECIALTICKET_LEFTANDRIGHTICON	BASE7 + 7					/* The left and right icon */
#define OBJID_SPECIALTICKET_EDGEBTN		BASE7 + 8							/* The "Edge" button */
#define OBJID_SPECIALTICKET_EDGEICON	BASE7 + 9							/* The edge icon */
#define OBJID_SPECIALTICKET_ODDOREVENBTN	BASE7 + 10						/* The "odd or even" button */
#define OBJID_SPECIALTICKET_ODDOREVENICON	BASE7 + 11						/* The odd or even icon */

/*
** #define's for notification subcodes go here
*/
#define ONSC_INVALID					0
#define ONSC_BLINKDONE					1
#define ONSC_EFFECTDONE					2

/*
** #define's for game state notification subcodes go here
*/
#define GSNSC_INVALID					0
#define GSNSC_FADEOUT					1
#define GSNSC_FADEIN					2

#endif		/* __OBJECTS_H__ */