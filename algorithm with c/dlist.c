#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data), int (*match)(const *void key1, const *void key2))
{
	list->size = 0;
	list->match = match;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void dlist_destroy(DList *list)
{
    void *data;
	
	/* Remove each element */
	while (dlist_size(list) > 0)
	{
		if (dlist_remove(list, dlist_tail(list), &data) == 0)
		    && list->destory != NULL)
		{
			/* Call a user-defined function to free dynamically allocated data. */
			list->destory(data);
		}
	}
	
	memset(list, 0, sizeof(DList));
	return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{

    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{

	return 0;
}
int dlist_remove(DList *list, DListElmt *element, void **data)
{
	if (element == NULL || dlist_size(list) == 0)
		return -1;
	
	*data = element->data;
	
	if (element == list->head)
	{
		list->head = element->next;
		
		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	}
	else
	{
		element->prev->next = element->next;
		if (element->next == NULL)
			list->tail = element->prev;
		else
		    element->next->prev = element->prev;
	}
	
	free(element);
	list->size--;
	return 0;
}