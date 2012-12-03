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