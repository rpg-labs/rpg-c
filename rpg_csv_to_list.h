#include <stdio.h>
#include <string.h>

#include "rpg.h"
#include "rpg_string_list.h"

#ifndef RPG_CSV_TO_LIST
#define RPG_CSV_TO_LIST 1

#define RPG_CSV_TO_LIST_RUN(line,list) ret=rpg_csv_to_list_run(line, &list);ENSURE_SUCCEEDED

int rpg_csv_to_list_run( char *line, struct _rpg_string_list **out_list );

#endif
