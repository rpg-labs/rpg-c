#include "rpg_stdin.h"

int read_line_from_stdin( apr_pool_t *p, int max_line_size, char **out_eof, char **out_line ) {
	char *line = (char *)apr_palloc(p, max_line_size);FAIL_IF_NULL(line)

	line[0] = '\0';
	line[sizeof(line)-1] = ~'\0';  /* Ensure no false-null at end of buffer */

	char *eof = fgets(line, max_line_size, stdin);
	int index = strlen( line );
	line[index-1] = '\0';//chomp the newline character

	*out_line = line;
	*out_eof = eof;

	return SUCCESS;
}

int read_stdin(apr_pool_t *p, int max_line_size, struct _rpg_string_list **out_list) {
	int ret;

	char *eof;
	char *line;
	int loop = 1;

	struct _rpg_string_list *l=NULL;

	RPG_STRING_LIST_INIT(l);

	while ( loop ) {
		ret = read_line_from_stdin( p, max_line_size, &eof, &line );ENSURE_SUCCEEDED
		RPG_STRING_LIST_ADD(l, line)

		if ( eof == NULL ) {
			if ( ferror( stdin ) ) {
				printf( "Error reading from stdin\n" );
				return FAILED;
			}
			loop = 0;
		}
	}
	
	*out_list=l;
	return SUCCESS;
}
