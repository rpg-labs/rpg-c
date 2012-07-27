#include <stdlib.h>
#include <string.h>
#include "rpg.h"
#include "rpg_string_list.h"

#ifndef RPG_HASH
#define RPG_HASH 1

#define RPG_HASH_INIT(h) ret = rpg_hash_init(&h);ENSURE_SUCCEEDED
#define RPG_HASH_SET(h, k, v) ret = rpg_hash_set(h,k,v);ENSURE_SUCCEEDED
#define RPG_HASH_SET_STRING(h, k, v) ret = rpg_hash_set_string(h,k,v);ENSURE_SUCCEEDED
#define RPG_HASH_GET(h, k, v) ret = rpg_hash_get(h,k,&v);ENSURE_SUCCEEDED
#define RPG_HASH_GET_STRING(h, k, v) ret = rpg_hash_get_string(h,k,&v);ENSURE_SUCCEEDED
#define RPG_HASH_DEL(h, k) ret = rpg_hash_del(h,k);ENSURE_SUCCEEDED

#define RPG_HASH_OF_STRINGS_TO_JSON(h,sl) ret = rpg_hash_of_strings_to_json(h,sl);ENSURE_SUCCEEDED
#define RPG_JSON_TO_HASH_OF_STRINGS(h,sl) ret = rpg_json_to_hash_of_strings(h,sl);ENSURE_SUCCEEDED

struct _rpg_hash_item {
	char *key;
	void *value;
	struct _rpg_hash_item *next;
};
struct _rpg_hash {
	struct _rpg_hash_item *first;
	struct _rpg_hash_item *last;
	int length;
};


int rpg_hash_init( struct _rpg_hash **out_new );

int rpg_new_hash_item( char *key, void *value, struct _rpg_hash_item **out_new );

int rpg_add_hash_item(struct _rpg_hash *hash, char *key, void *value);

int rpg_hash_find(struct _rpg_hash *hash, char *key, struct _rpg_hash_item **out_hash_item);

int rpg_hash_get(struct _rpg_hash *hash, char *key, void **out_value);

int rpg_hash_get_string(struct _rpg_hash *hash, char *key, char **out_value);

int rpg_hash_set(struct _rpg_hash *hash, char *key, void *value);

int rpg_hash_del(struct _rpg_hash *hash, char *key);

int rpg_hash_of_strings_to_json( struct _rpg_hash *hash, struct _rpg_string_list *l );

#endif
