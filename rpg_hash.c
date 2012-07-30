#include "rpg_hash.h"

int rpg_hash_init( apr_pool_t *p, struct _rpg_hash **out_new ) {
	struct _rpg_hash *new = ( struct _rpg_hash * ) apr_palloc ( p, sizeof(struct _rpg_hash) );FAIL_IF_NULL(new);
	new->first = NULL;
	new->last = NULL;
	new->length = 0;

	*out_new = new;

	return SUCCESS;
}

int rpg_new_hash_item( apr_pool_t *p, char *key, void *value, struct _rpg_hash_item **out_new ) {
	char *new_string = NULL;
	struct _rpg_hash_item *new = ( struct _rpg_hash_item * ) apr_palloc ( p, sizeof(struct _rpg_hash_item) );FAIL_IF_NULL(new)
	DUP_STRING(key);
	new->key = new_string;
	new->value = value;
	new->next = NULL;

	*out_new = new;
	return SUCCESS;
}

int rpg_add_hash_item( apr_pool_t *p, struct _rpg_hash *hash, char *key, void *value ) {
	struct _rpg_hash_item *new=NULL;
	int ret = rpg_new_hash_item( p, key, value, &new );ENSURE_SUCCEEDED

	if ( hash->last == NULL ) {
		hash->first = new;
		hash->last = new;
	} else {
		hash->last->next = new;
		hash->last = new;
	}
	hash->length = hash->length + 1;

	return SUCCESS;
}

int rpg_hash_find(struct _rpg_hash *hash, char *key, struct _rpg_hash_item **out_hash_item) {

	if ( hash == NULL || key == NULL ) {
		*out_hash_item = NULL;
		return SUCCESS;
	}

	struct _rpg_hash_item *current=hash->first;
	size_t len = sizeof( key );
	while( current != NULL ) {
		if ( !strncmp( key, current->key, len ) ) {
			*out_hash_item = current;
			return SUCCESS;
		}
		current = current->next;
	}
	*out_hash_item = NULL;
	return SUCCESS;
}

int rpg_hash_get(struct _rpg_hash *hash, char *key, void **out_value) {
	struct _rpg_hash_item *hash_item = NULL;

	int ret = rpg_hash_find(hash, key, &hash_item);ENSURE_SUCCEEDED

	if ( hash_item == NULL ) {
		*out_value = NULL;
	} else {
		*out_value = hash_item->value;
	}
	
	return SUCCESS;
}

int rpg_hash_get_string(struct _rpg_hash *hash, char *key, char **out_value) {
	int ret;

	void *data;
	ret = rpg_hash_get(hash, key, &data);ENSURE_SUCCEEDED

	*out_value = (char *)data;

	return SUCCESS;
}

int rpg_hash_get_tm(struct _rpg_hash *hash, char *key, struct tm **out_value) {
	int ret;
    
	void *data;
	ret = rpg_hash_get(hash, key, &data);ENSURE_SUCCEEDED
    
	*out_value = (struct tm *)data;
    
	return SUCCESS;
}

int rpg_hash_set( apr_pool_t *p, struct _rpg_hash *hash, char *key, void *value ) {
	struct _rpg_hash_item *hash_item=NULL;

	int ret = rpg_hash_find( hash, key, &hash_item );ENSURE_SUCCEEDED
	if ( hash_item != NULL ) {
		hash_item->value = value;
	} else {
		ret = rpg_add_hash_item( p, hash, key, value );ENSURE_SUCCEEDED
	}

	return SUCCESS;
}

int rpg_hash_set_string( apr_pool_t *p, struct _rpg_hash *hash, char *key, char *value ) {
	int ret;
	if ( value == NULL ) {
		RPG_HASH_SET(hash, key, NULL);
		return SUCCESS;
	}
		
	char *buffer = (char *)apr_palloc(p, strlen(value)+1);
	strcpy( buffer, value );

	RPG_HASH_SET(hash, key, buffer);

	return SUCCESS;
}

int rpg_hash_del(struct _rpg_hash *hash, char *key) {

	//Anything in the first drill is NULL, so fine.
	if ( hash == NULL || key == NULL || hash->first == NULL ) {
		return SUCCESS;
	}

	//The first entry is the one to be removed	
	size_t len = sizeof( key );
	if ( !strncmp( key, hash->first->key, len ) ) {
		if ( hash->first == hash->last ) {
			hash->last = hash->first->next;
		}
		hash->first = hash->first->next;
		return SUCCESS;
	}

	struct _rpg_hash_item *current=hash->first;
	while( current->next != NULL ) {
		if ( !strncmp( key, current->next->key, len ) ) {
			if ( hash->first == hash->last ) {
				hash->last = current->next->next;
			}
			current->next = current->next->next;

			return SUCCESS;
		}
		current = current->next;
	}
	
	//Couldn't find it, no worries.
	return SUCCESS;
}

int rpg_hash_of_strings_to_json( apr_pool_t *p, struct _rpg_hash *hash, struct _rpg_string_list *l ) {
	int ret;

	if ( hash == NULL ) {
		return SUCCESS;
	}

	struct _rpg_hash_item *current=hash->first;
	RPG_STRING_LIST_ADD( l, "{" );
	while( current != NULL ) {
		if ( current != hash->first ) {
			RPG_STRING_LIST_ADD( l, "," );
		}
		RPG_STRING_LIST_ADD( l, "'" );
		RPG_STRING_LIST_ADD( l, current->key );
		RPG_STRING_LIST_ADD( l, "'" );

			RPG_STRING_LIST_ADD( l, ":" );

		RPG_STRING_LIST_ADD( l, "'" );
		RPG_STRING_LIST_ADD( l, (char *)current->value );
		RPG_STRING_LIST_ADD( l, "'" );

		current = current->next;
	}
	RPG_STRING_LIST_ADD( l, "}" );

	return SUCCESS;
}
