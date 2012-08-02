#include "rpg_time.h"

/*
 * The number of days in the month.
 */
int rpg_month_days(unsigned int month, unsigned int year)
{
	return rpg_days_in_month[month] + (LEAP_YEAR(year) && month == 1);
}

/* 
 * The number of days since January 1. (0 to 365)
 */
int rpg_year_days(unsigned int day, unsigned int month, unsigned int year)
{
	return rpg_ydays[LEAP_YEAR(year)][month] + day;
}

int rpg_parse_tm( apr_pool_t *p, char *buffer, char *format, struct tm **out_tm ) {
	struct tm *tm = (struct tm *)apr_palloc(p, sizeof(struct tm));
	void *data = memset(tm, 0, sizeof(struct tm));
	
	char *s = strptime(buffer, format, tm);FAIL_IF_NULL(s)
	
	*out_tm = tm;
	return SUCCESS;
}

int rpg_clone_tm( apr_pool_t *p, struct tm *in_tm, struct tm **out_tm ) {
	struct tm *tm = (struct tm *)apr_palloc(p, sizeof(struct tm));
//	void *data = memset(tm, 0, sizeof(struct tm));

    tm->tm_sec = in_tm->tm_sec;
    tm->tm_min = in_tm->tm_min;
    tm->tm_hour = in_tm->tm_hour;
    tm->tm_mday = in_tm->tm_mday;
    tm->tm_mon = in_tm->tm_mon;
    tm->tm_year = in_tm->tm_year;
    tm->tm_wday = in_tm->tm_wday;
    tm->tm_yday = in_tm->tm_yday;
    tm->tm_isdst = in_tm->tm_isdst;

	*out_tm = tm;
	return SUCCESS;
}

int rpg_cmp_tm(struct tm *t1, struct tm *t2) {
#define CHK_LESS(l,r) if ( l < r ) { return -1; }
#define CHK_MORE(l,r) if ( l > r ) { return 1; }
#define CHK(l,r) CHK_LESS(l,r);CHK_MORE(l,r)

    CHK( t1->tm_year, t2->tm_year );
    CHK( t1->tm_mon, t2->tm_mon );
    CHK( t1->tm_mday, t2->tm_mday );
    CHK( t1->tm_hour, t2->tm_hour );
    CHK( t1->tm_min, t2->tm_min );
    CHK( t1->tm_sec, t2->tm_sec );

    return 0;
}

void rpg_print_date( char *s, struct tm *tm ) {
    char buffer[DEFAULT_BUFFER_SIZE];
    
    strftime (buffer,DEFAULT_BUFFER_SIZE,RPG_STD_DATE_FMT,tm);
    printf( "%s: %s\n", s, buffer );
}
