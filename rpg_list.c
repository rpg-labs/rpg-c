#include "rpg_list.h"

int rpg_list_init( struct _rpg_list **out_new ) {
	struct _rpg_list *new = ( struct _rpg_list * ) malloc ( sizeof(struct _rpg_list) );FAIL_IF_NULL(new);
	new->first = NULL;
	new->last = NULL;
	new->length=0;

	*out_new = new;

	return SUCCESS;
}

int rpg_new_list_item( void *data, struct _rpg_list_item **out_new ) {
	char *new_string=NULL;
	struct _rpg_list_item *new = ( struct _rpg_list_item * ) malloc ( sizeof(struct _rpg_list_item) );FAIL_IF_NULL(new)
	new->data = data;
	new->next = NULL;

	*out_new = new;
	return SUCCESS;
}

int rpg_list_add(struct _rpg_list *list, void *data) {
	struct _rpg_list_item *new=NULL;
	int ret = rpg_new_list_item( data, &new );ENSURE_SUCCEEDED

	if ( list->last == NULL ) {
		list->first = new;
		list->last = new;
	} else {
		list->last->next = new;
		list->last = new;
	}
	list->length=list->length+1;
	
	return SUCCESS;
}
