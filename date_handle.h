/********************************************************************************
 * 	Moon Project																*
 *																				*
 *																				*
 *  Time Management Package - Date Handle Library								*
 *	Author: João Matheus Siqueira Souza (jmssouza)								*
 *																				*
 *  December 17th, 2019															*
 ********************************************************************************/
#ifndef JM_DATE_HANDLE_H_
#define JM_DATE_HANDLE_H_

#include <time.h>

struct DATE
{
	struct tm s_time;
};	
typedef struct DATE date_t;

int date_create(date_t **);
int date_free(date_t *);

int date_set_current(date_t *);
int date_set_calendar(date_t *, int, int, int);
int date_set_clock(date_t *, int, int, int);

int date_get_calendar_to_int(int *, int *, int *, date_t *);
int date_get_clock_to_int(int *, int *, int *, date_t *);
int date_get_system_format(char *, date_t *);
int date_get_normal_format(char *, date_t *);

int date_print_system_format(date_t *);
int date_print_normal_format(date_t *);

int date_diff_days(int *, date_t *, date_t *);


#endif