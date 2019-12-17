#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <constants.h>
#include <date_handle.h>


int date_create(date_t **date)
{
	if(!date) return INVALID_ADDRESS;

	*date = (date_t *)calloc(1, sizeof(date_t));
	if(!(*date)) return INVALID_MEMORY_ALLOCATION; 
	
	return SUCCESS;
}


int date_free(date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;
	
	free(date);

	return SUCCESS;
}


void __set_struct(date_t * date, struct tm * ps_time)
{
	date->s_time.tm_sec   = ps_time->tm_sec;
	date->s_time.tm_min   = ps_time->tm_min;
	date->s_time.tm_hour  = ps_time->tm_hour;
	date->s_time.tm_mday  = ps_time->tm_mday;
	date->s_time.tm_mon   = ps_time->tm_mon;
	date->s_time.tm_year  = ps_time->tm_year;
	date->s_time.tm_wday  = ps_time->tm_wday;
	date->s_time.tm_yday  = ps_time->tm_yday;
	date->s_time.tm_isdst = ps_time->tm_isdst;	
}


int date_set_current(date_t * date)
{
	if(!date) return INVALID_DATA_STRUCTURE;

	time_t timer;
	struct tm *ps_time;

	timer = time(NULL);
	ps_time = localtime(&timer);
	__set_struct(date, ps_time);

	return SUCCESS;
}


int date_set_calendar(date_t *date, int year, int month, int day)
{
	if(!date) return INVALID_MEMORY_ALLOCATION;
	if(year < 0) return INVALID_RANGE_VALUE;
	if(month <= 0 || month > 12) return INVALID_RANGE_VALUE;
	if(day <= 0 || month > 31) return INVALID_RANGE_VALUE;

	time_t timer;
	struct tm *ps_time;

	date->s_time.tm_year = year - 1900;
	date->s_time.tm_mon  = month - 1;
	date->s_time.tm_mday = day;
	ps_time = &(date->s_time);
	timer = mktime(ps_time);	
	ps_time = localtime(&timer);
	__set_struct(date, ps_time);

	return SUCCESS;
}

int date_set_clock(date_t *date, int hour, int minute, int second)
{
	if(!date) return INVALID_MEMORY_ALLOCATION;
	if(hour < 0 || hour > 23) return INVALID_RANGE_VALUE;
	if(minute < 0 || minute > 59) return INVALID_RANGE_VALUE;
	if(second < 0 || second > 59) return INVALID_RANGE_VALUE;

	time_t timer;
	struct tm *ps_time;

	date->s_time.tm_hour = hour;
	date->s_time.tm_min  = minute;
	date->s_time.tm_sec = second;
	ps_time = &(date->s_time);
	timer = mktime(ps_time);	
	ps_time = localtime(&timer);
	__set_struct(date, ps_time);
	
	return SUCCESS;
}


int date_get_calendar_to_int(int *year, int *month, int *day, date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;
	if(!year || !month || !day) return INVALID_ADDRESS;

	*year  = date->s_time.tm_year + 1900;
	*month = date->s_time.tm_mon + 1;
	*day   = date->s_time.tm_mday;

	return SUCCESS;
}


int date_get_clock_to_int(int *hour, int *minute, int *second, date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;
	if(!hour || !minute || !second) return INVALID_ADDRESS;

	*hour     = date->s_time.tm_hour;
	*minute   = date->s_time.tm_min;
	*second   = date->s_time.tm_sec;

	return SUCCESS;
}


int date_get_system_format(char *date_string, date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;
	if(!date_string) return INVALID_ADDRESS;

	struct tm *ps_time;

	ps_time = &(date->s_time);
	date_string = asctime(ps_time);

	return SUCCESS;
}


int date_get_normal_format(char *date_string, date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;
	if(!date_string) return INVALID_ADDRESS;

	sprintf(date_string, "%d/%d/%d - %d:%d:%d",
			date->s_time.tm_mday, date->s_time.tm_mon + 1, date->s_time.tm_year + 1900,
			date->s_time.tm_hour, date->s_time.tm_min, date->s_time.tm_sec );

	return SUCCESS;
}


int date_print_system_format(date_t * date)
{
	if(!date) return INVALID_DATA_STRUCTURE;

	struct tm *ps_time;

	ps_time = &(date->s_time);
	printf("%s", asctime(ps_time));

	return SUCCESS;
}


int date_print_normal_format(date_t *date)
{
	if(!date) return INVALID_DATA_STRUCTURE;

	printf("%d/%d/%d - %d:%d:%d",
			date->s_time.tm_mday, date->s_time.tm_mon + 1, date->s_time.tm_year + 1900,
			date->s_time.tm_hour, date->s_time.tm_min, date->s_time.tm_sec );
	return SUCCESS;
}


int date_diff_days(int *diff, date_t *date_1, date_t *date_2)
{
	if(!date_1 || !date_2) return INVALID_DATA_STRUCTURE;
	if(!diff) return INVALID_ADDRESS;

	(*diff) = date_1->s_time.tm_yday - date_2->s_time.tm_yday;

	return SUCCESS;
}