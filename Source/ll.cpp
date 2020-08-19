/*
** ll.cpp
**
** Contains all routines for the generic linked list functions
*/

#include "../include/ll.h"

LINKED_LIST_STRUCT *LL_Add(LINKED_LIST_STRUCT *head, void *data)
/*
** LL_Add()
** Adds an entry to the linked list, returns NULL if unable to do so
*/
{
	LINKED_LIST_STRUCT *curr = head;

	while (curr->next)
	{
		curr = curr->next;

		if (curr->data == data)
			return NULL;
	}

	/* Create new entry and add it */
	curr->next = (LINKED_LIST_STRUCT*)malloc(sizeof(LINKED_LIST_STRUCT));
	curr = curr->next;

	if (curr)
	{
		curr->data = data;
		curr->next = NULL;
	}
	else
	/* Unable to malloc() new entry */
		return NULL;

	return curr;
}

LINKED_LIST_STRUCT *LL_Find(LINKED_LIST_STRUCT *head, void *data)
/*
** LL_Find()
** Searches through specified linked list and returns pointer to link w/data
*/
{
	LINKED_LIST_STRUCT *curr = head;

	while (curr->next)
	{
		curr = curr->next;

		if (curr->data == data)
			return curr;
	}

	return NULL;
}

void *LL_Remove(LINKED_LIST_STRUCT *head, LINKED_LIST_STRUCT *target)
/*
** LL_Remove()
** Removes an entry from the linked list, and returns pointer to data(for further cleanup)
*/
{
	LINKED_LIST_STRUCT *temp = head, *curr = head;
	void *retval;

	if (head)
	{
		while (curr->next)
		{
			curr = curr->next;

			if (curr == target)
			/* Match found */
			{
				retval = curr->data;
				temp->next = curr->next;
				free(curr);

				return retval;
			}

			temp = curr;
		}
	}

	return NULL;
}