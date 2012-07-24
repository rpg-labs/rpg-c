#include <stdio.h>
#include "rpg_string_list.h"

#ifndef RPG_STDIN
#define RPG_STDIN 1

#define RPG_READ_STDIN(l) ret = read_stdin(l, &stdin_list);ENSURE_SUCCEEDED
#define LINE_SIZE 1024

int read_line_from_stdin( int max_line_size, char **out_eof, char **out_line );

int read_stdin(int max_line_size, struct _rpg_string_list **out_list);

#endif
