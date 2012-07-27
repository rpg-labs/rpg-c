#ifndef RPG_TIME
#define RPG_TIME 1

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "rpg.h"

static const unsigned char rpg_days_in_month[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const unsigned short rpg_ydays[2][13] = {
	/* Normal years */
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	/* Leap years */
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
}; 

#define LEAPS_THRU_END_OF(y) ((y)/4 - (y)/100 + (y)/400)
#define LEAP_YEAR(year) ((!(year % 4) && (year % 100)) || !(year % 400))

#define RPG_YEAR_DAYS_TM(tm) rpg_year_days( tm->tm_mday, tm->tm_mon, tm->tm_year )
#define RPG_PARSE_TM(b,f,t) rpg_parse_tm( b,f,&t );ENSURE_SUCCEEDED

#define RPG_STD_DATE_FMT "%d %b %Y"

/*
 * The number of days in the month.
 */
int rpg_month_days(unsigned int month, unsigned int year);

/* 
 * The number of days since January 1. (0 to 365)
 */
int rpg_year_days(unsigned int day, unsigned int month, unsigned int year);

#endif
