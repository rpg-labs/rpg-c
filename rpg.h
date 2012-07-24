#ifndef RPG
#define RPG 1

#define FAILED 0
#define SUCCESS -1
#define FAIL_IF_NULL(v) if ( v == NULL ) { return FAILED; }
#define ENSURE_SUCCEEDED if ( ret == FAILED ) { return FAILED; }

#define DUP_STRING(s) new_string = ( char * ) malloc ( strlen( s ) );FAIL_IF_NULL(new_string);strncpy(new_string, s, strlen( s ));

#define DEFAULT_BUFFER_SIZE 1024

#endif