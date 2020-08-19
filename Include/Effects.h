/*
** Effects.h
**
** This header file defines all graphic effects used by Keno Pro
**
** Copyright 2004, Programmed by Zeb Rasco
*/

#ifndef __EFFECTS_H__
#define __EFFECTS_H__

#include "..\Include\Struct.h"
#include "..\Include\Objects.h"
#include "..\Include\KenoPro.h"
#include "..\Include\Constants.h"

int Effect_Startup_1(GAME_GLOBAL*, unsigned int, BOOL, int, GAME_OBJECT*);
int Effect_TicketChange(GAME_GLOBAL*, unsigned int, unsigned int, int, GAME_OBJECT*);

#endif		/* __EFFECTS_H__ */
