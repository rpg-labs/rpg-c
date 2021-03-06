#include <stdlib.h>
#include <string.h>
#include "rpg.h"

#ifndef RPG_LIST
#define RPG_LIST 1


#define RPG_LIST_INIT(l) ret = rpg_list_init(p,&l);ENSURE_SUCCEEDED
#define RPG_LIST_ADD(l,v) ret = rpg_list_add(p,l,v);ENSURE_SUCCEEDED
#define RPG_LIST_GET(l,i,v) ret = rpg_list_get(p,l,i,&v);ENSURE_SUCCEEDED

struct _rpg_list_item {
	void *data;
	struct _rpg_list_item *next;
};
struct _rpg_list {
	int length;
	struct _rpg_list_item *first;
	struct _rpg_list_item *last;
};


int rpg_list_init( apr_pool_t *p, struct _rpg_list **out_new );

int rpg_new_list_item( apr_pool_t *p, void *data, struct _rpg_list_item **out_new );

int rpg_list_add( apr_pool_t *p, struct _rpg_list *list, void *data );

int rpg_list_get( struct _rpg_list *list, int index, void **out_data );

#endif
