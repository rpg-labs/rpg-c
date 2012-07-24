#include "rpg_csv_to_list.h"

int rpg_csv_to_list_run( char *line, struct _rpg_string_list **out_list ) {

	int ret;
	struct _rpg_string_list *l = NULL;
	
	RPG_STRING_LIST_INIT(l)
	*out_list = l;

	if ( line == NULL ) {
		return SUCCESS;
	}

	{
		char buffer[1024];
		int buffer_index=0;
		int line_index=0;
		
		while( line[line_index] != '\0' ) {
			if ( line[line_index] == ',' ) {
				buffer[buffer_index] = '\0';
				RPG_STRING_LIST_ADD(l,&buffer[0]);
				buffer_index=0;
			} else {
				buffer[buffer_index++] = line[line_index];
			}


			line_index++;
		}
		buffer[buffer_index] = '\0';
		RPG_STRING_LIST_ADD(l,&buffer[0]);
		
	}


	return SUCCESS;
}
