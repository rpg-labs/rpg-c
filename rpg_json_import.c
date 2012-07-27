#include "rpg_json_import.h"

#define RPG_JSON_IMPORT_INC_ON_SU if ( *out_i > -1 ) { *out_i=*out_i+1;}

#define RPG_JSON_IMPORT_FIND_START_OF(b,l,c,i) ret = rpg_json_import_find_start_of(b,l,c,&i);ENSURE_SUCCEEDED
#define RPG_JSON_IMPORT_ATTRIBUTE_LIST(b,l,i) RPG_JSON_IMPORT_FIND_START_OF(b,l,'{',i);
#define RPG_JSON_IMPORT_START_OF_ATTR(b,l,i) RPG_JSON_IMPORT_FIND_START_OF(b,l,'"',i);
#define RPG_JSON_IMPORT_ATTR_DIV(b,l,i) RPG_JSON_IMPORT_FIND_START_OF(b,l,':',i);
#define RPG_JSON_IMPORT_NEXT_VAL(b,l,i) RPG_JSON_IMPORT_FIND_START_OF(b,l,'"',i);

#define RPG_JSON_IMPORT_END_OF_NAME(b,l,i) ret = rpg_json_import_end_of_name(b,l,&i);ENSURE_SUCCEEDED
#define RPG_JSON_IMPORT_END_OF_VALUE(b,l,i) ret = rpg_json_import_end_of_value(b,l,&i);ENSURE_SUCCEEDED

#define RPG_JSON_IMPORT_NEXT_ATTR(b,l,i) ret = rpg_json_import_next_attr(b,l,&i);ENSURE_SUCCEEDED

#define RPG_JSON_IMPORT_READ_ATTR_TO_HASH(b,l,i,r) ret = rpg_json_import_read_attr_to_hash(b,l,&i,r);ENSURE_SUCCEEDED

#define RPG_JSON_IMPORT_ENSURE_INDEX_VALID if ( i == -1 ) { *out_i = -1; return SUCCESS; }

int rpg_json_import_chrpos( char *buffer, int len, char c, int *out_i ) {
	int i;
	for( i=*out_i;i<len;i++ ) {
		if ( buffer[i] == c ) { //found it
				*out_i = i;
				return SUCCESS;
		} else if ( buffer[i] == ' ' ) { //legal white space

		} else { //illegal character
				*out_i = -1;
				return SUCCESS;
		}
	}

	*out_i = -1;
	return SUCCESS;
}

int rpg_json_import_end_of_name( char *buffer, int len, int *out_i ) {
	int i;
	for( i=*out_i;i<len;i++ ) {
		if ( buffer[i] == '"' ) { //found it
			*out_i = i-1;
			return SUCCESS;
		}
	}

	*out_i = -1;
	return SUCCESS;
}

int rpg_json_import_end_of_value( char *buffer, int len, int *out_i ) {
	int i;
	for( i=*out_i;i<len;i++ ) {
		if ( buffer[i] == '"' ) { //found it
			*out_i = i-1;
			return SUCCESS;
		}
	}

	*out_i = -1;
	return SUCCESS;
}

int rpg_json_import_find_start_of( char *buffer, int len, char c, int *out_i ) {
	int ret = rpg_json_import_chrpos( buffer, len, c, out_i );ENSURE_SUCCEEDED
	RPG_JSON_IMPORT_INC_ON_SU;
	return SUCCESS;
}

int rpg_json_import_next_attr( char *buffer, int len, int *out_i ) {
	int ret;
	int i;

	for( i=*out_i;i<len;i++ ) {
		if ( buffer[i] == '}' ) { //end of object
			*out_i = -2;
			return SUCCESS;
		} else if (  buffer[i] == ',' ) {
			int j=i+1;
			RPG_JSON_IMPORT_START_OF_ATTR(buffer, len, j );
			*out_i = j;
			return SUCCESS;
		} else if ( buffer[i] == ' ' ) { //legal white space

		} else { //illegal character
				*out_i = -1;
				return SUCCESS;
		}
	}

	*out_i = -1;
	return SUCCESS;
}

//I think this could be replace with strncpy
int rpg_json_import_copy_string_from_buffer( char *buffer, char *string, int start, int end ) {
	int i=0;
	int j=0;

	for( i=start;i<=end;i++ ) {
		string[j++] = buffer[i];
	}
	string[j] = '\0';

	return SUCCESS;
}

int rpg_json_import_read_attr_to_hash( char *buffer, int len, int *out_i, struct _rpg_hash *r ) {
	int ret;
	int i=*out_i;
	char name[DEFAULT_BUFFER_SIZE];
	char value[DEFAULT_BUFFER_SIZE];

	{
		int start = i;
		RPG_JSON_IMPORT_END_OF_NAME(buffer,len,i);
		ret = rpg_json_import_copy_string_from_buffer( buffer, name, start, i );ENSURE_SUCCEEDED;RPG_JSON_IMPORT_ENSURE_INDEX_VALID;
		i=i+2;
	}
	RPG_JSON_IMPORT_ATTR_DIV(buffer,len,i);RPG_JSON_IMPORT_ENSURE_INDEX_VALID;
	RPG_JSON_IMPORT_NEXT_VAL(buffer,len,i);RPG_JSON_IMPORT_ENSURE_INDEX_VALID;

	{
		int start = i;
		RPG_JSON_IMPORT_END_OF_VALUE(buffer,len,i);RPG_JSON_IMPORT_ENSURE_INDEX_VALID;
		ret = rpg_json_import_copy_string_from_buffer( buffer, value, start, i );ENSURE_SUCCEEDED
		RPG_JSON_IMPORT_ENSURE_INDEX_VALID;
		i=i+2;
	}

//	printf( "name: %s, value: %s\n", name, value );
	RPG_HASH_SET_STRING( r, name, value );
	*out_i = i;

	return SUCCESS;
}

//{"hid":"198","name":"Mangatewai","psm":"16 Oct 2012","psc":"25 Jul 2012","mapref":""}"
int rpg_json_import( char *b, struct _rpg_hash **out_r ) {
	int ret;
	struct _rpg_hash *r;
	int l = strlen( b );
	int i;

	#define ENSURE_INDEX_VALID if ( i == -1 ) { *out_r = NULL; return SUCCESS; }

	RPG_HASH_INIT(r);

	i=0;
	RPG_JSON_IMPORT_ATTRIBUTE_LIST(b,l,i);ENSURE_INDEX_VALID;
	RPG_JSON_IMPORT_START_OF_ATTR(b,l,i);ENSURE_INDEX_VALID;

	while( i != -2 ) {
		RPG_JSON_IMPORT_READ_ATTR_TO_HASH(b,l,i,r);ENSURE_INDEX_VALID;
		RPG_JSON_IMPORT_NEXT_ATTR(b,l,i);ENSURE_INDEX_VALID;
	}

	*out_r = r;
	return SUCCESS;	
}
