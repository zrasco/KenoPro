/*
** ll.h
**
** Contains header information for all linked list information & functions
*/

#ifndef __LL_H__
#define __LL_H__

#include "Struct.h"

/* Function prototypes */
LINKED_LIST_STRUCT	*LL_Add(LINKED_LIST_STRUCT*, void*);
LINKED_LIST_STRUCT	*LL_Find(LINKED_LIST_STRUCT*, void*);
void	*LL_Remove(LINKED_LIST_STRUCT*, LINKED_LIST_STRUCT*);

#endif		/* __LL_H__ */