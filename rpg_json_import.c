#include "rpg_json_import.h"

#define INC_ON_SU if ( *out_i > -1 ) { *out_i=*out_i+1;}

#define FIND_START_OF(b,l,c,i) ret = find_start_of(b,l,c,&i);ENSURE_SUCCEEDED
#define ATTRIBUTE_LIST(b,l,i) FIND_START_OF(b,l,'{',i);
#define START_OF_ATTR(b,l,i) FIND_START_OF(b,l,'"',i);
#define ATTR_DIV(b,l,i) FIND_START_OF(b,l,':',i);
#define NEXT_VAL(b,l,i) FIND_START_OF(b,l,'"',i);

#define END_OF_NAME(b,l,i) ret = end_of_name(b,l,&i);ENSURE_SUCCEEDED
#define END_OF_VALUE(b,l,i) ret = end_of_value(b,l,&i);ENSURE_SUCCEEDED

#define NEXT_ATTR(b,l,i) ret = next_attr(b,l,&i);ENSURE_SUCCEEDED

#define READ_ATTR_TO_HASH(b,l,i,r) ret = read_attr_to_hash(p,b,l,&i,r);ENSURE_SUCCEEDED

#define ENSURE_INDEX_VALID if ( i == -1 ) { *out_i = -1; return SUCCESS; }

int chrpos( char *buffer, int len, char c, int *out_i ) {
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

int end_of_name( char *buffer, int len, int *out_i ) {
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

int end_of_value( char *buffer, int len, int *out_i ) {
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

int find_start_of( char *buffer, int len, char c, int *out_i ) {
	int ret = chrpos( buffer, len, c, out_i );ENSURE_SUCCEEDED
	INC_ON_SU;
	return SUCCESS;
}

int next_attr( char *buffer, int len, int *out_i ) {
	int ret;
	int i;

	for( i=*out_i;i<len;i++ ) {
		if ( buffer[i] == '}' ) { //end of object
			*out_i = -2;
			return SUCCESS;
		} else if (  buffer[i] == ',' ) {
			int j=i+1;
			START_OF_ATTR(buffer, len, j );
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
int copy_string_from_buffer( char *buffer, char *string, int start, int end ) {
	int i=0;
	int j=0;

	for( i=start;i<=end;i++ ) {
		string[j++] = buffer[i];
	}
	string[j] = '\0';

	return SUCCESS;
}

int read_value_from_buffer( apr_pool_t *p, char *buffer, int len, int *out_i, char **out_value ) {
	int i = *out_i;

	while( i < len && buffer[i] == ' ' ) { i++; }; //spin through the whitespace
	
	if ( i == len ) {
		*out_i = -1;
		return SUCCESS;
	}

	if ( buffer[i] == '"' ) {
		int ret;
		char *value = (char *)apr_palloc(p, DEFAULT_BUFFER_SIZE);

		i++;
		int start=i;
		END_OF_VALUE(buffer,len,i);ENSURE_INDEX_VALID;
		ret = copy_string_from_buffer( buffer, value, start, i );ENSURE_SUCCEEDED;ENSURE_INDEX_VALID;
		i=i+2;
		
		*out_value = value;
		*out_i = i;
		return SUCCESS;
	}

	if ( buffer[i] == 'n' ) {
		if ( ( i + 4 ) < len && !strncmp( &buffer[i], "null", 4 ) ) {
			i = i + 4;

			*out_value = NULL;
			*out_i = i;
			return SUCCESS;
		}
	}

	*out_i = -1;
	return SUCCESS;

}

int read_attr_to_hash( apr_pool_t *p, char *buffer, int len, int *out_i, struct _rpg_hash *r ) {
	int ret;
	int i=*out_i;
	char name[DEFAULT_BUFFER_SIZE];
	char *value;

	{
		int start = i;
		END_OF_NAME(buffer,len,i);
		ret = copy_string_from_buffer( buffer, name, start, i );ENSURE_SUCCEEDED;ENSURE_INDEX_VALID;
		i=i+2;
	}
	ATTR_DIV(buffer,len,i);ENSURE_INDEX_VALID;
	{
		ret = read_value_from_buffer( p, buffer, len, &i, &value );ENSURE_SUCCEEDED;ENSURE_INDEX_VALID

	}

	RPG_HASH_SET_STRING( r, name, value );
	*out_i = i;

	return SUCCESS;
}

//{"hid":"198","name":"Mangatewai","psm":"16 Oct 2012","psc":"25 Jul 2012","mapref":""}"
int rpg_json_import( apr_pool_t *p, char *b, struct _rpg_hash **out_r ) {
	int ret;
	struct _rpg_hash *r;
	int l = strlen( b );
	int i;

	#define ENSURE_INDEX_VALID_R if ( i == -1 ) { *out_r = NULL; return SUCCESS; }

	RPG_HASH_INIT(r);

	i=0;
	ATTRIBUTE_LIST(b,l,i);ENSURE_INDEX_VALID_R;
	START_OF_ATTR(b,l,i);ENSURE_INDEX_VALID_R;

	while( i != -2 ) {
		READ_ATTR_TO_HASH(b,l,i,r);ENSURE_INDEX_VALID_R;
		NEXT_ATTR(b,l,i);ENSURE_INDEX_VALID_R;
	}

	*out_r = r;
	return SUCCESS;	
}
