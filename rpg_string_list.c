#include <stdlib.h>
#include <string.h>
#include "rpg.h"
#include "rpg_string_list.h"


int rpg_string_list_init( struct _rpg_string_list **out_new ) {
	struct _rpg_string_list *new = ( struct _rpg_string_list * ) malloc ( sizeof(struct _rpg_string_list) );FAIL_IF_NULL(new);
	new->first = NULL;
	new->last = NULL;
	new->count = 0;

	*out_new = new;

	return SUCCESS;
}

int rpg_new_string_list_item( char *string, struct _rpg_string_list_item **out_new ) {
	char *new_string=NULL;
	struct _rpg_string_list_item *new = ( struct _rpg_string_list_item * ) malloc ( sizeof(struct _rpg_string_list_item) );FAIL_IF_NULL(new)
	DUP_STRING(string);
	new->data = new_string;
	new->next = NULL;

	*out_new = new;
	return SUCCESS;
}

int rpg_string_list_add(struct _rpg_string_list *string_list, char *string) {
	struct _rpg_string_list_item *new=NULL;
	int ret = rpg_new_string_list_item( string, &new );ENSURE_SUCCEEDED

	if ( string_list->last == NULL ) {
		string_list->first = new;
		string_list->last = new;
	} else {
		string_list->last->next = new;
		string_list->last = new;
	}
	string_list->count = string_list->count + 1;
	
	return SUCCESS;
}

int rpg_string_list_get(struct _rpg_string_list *string_list, int index, char **out_string) {
	*out_string = NULL;
	if ( string_list == NULL ) {
		return SUCCESS;
	}

	{
		struct _rpg_string_list_item *string_list_item = string_list->first;
		int i;
		for( i=1;i<index;i++ ) {
			if ( string_list_item == NULL ) { return SUCCESS; }

			string_list_item = string_list_item->next;
		}
		if ( string_list_item == NULL ) { return SUCCESS; }
		*out_string = string_list_item->data;
	}
	
	return SUCCESS;
}

int rpg_string_list_to_string(struct _rpg_string_list *string_list, char **out_string) {
	int length=0;
	struct _rpg_string_list_item *i=NULL;

	{
		i = string_list->first;
		while( i != NULL ) {
			length = length + strlen(i->data);
			i = i->next;
		}
	}
	
	char *s;
	s = ( char * ) malloc ( length );
	s[0] = '\0';

	{
		i = string_list->first;
		while( i != NULL ) {
			strcat( s, i->data );
			i = i->next;
		}
	}

	*out_string = s;
	return SUCCESS;
}
