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
