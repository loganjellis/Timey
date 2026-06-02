#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "timey.h"

#define TIMEY_TIME_STR_LEN 11
#define TIMEY_DATE_STR_LEN 13

// obtain and format time
static void timey_fmt_time(char *buffer, size_t size, const char *fmt)
{
	time_t raw = 0;
	struct tm *time_info;

	time(&raw);

	time_info = localtime(&raw);

	strftime(buffer, size, fmt, time_info);
}
// obtain full string after formatting
static void timey_get_str(char *buffer, size_t size, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, size, fmt, args);
	va_end(args);
}
void timey_query_time(char *buffer, size_t buffer_size)
{
	if(!buffer)
		return;

	timey_fmt_time(buffer, buffer_size, "[%H:%M:%S]");
}
void timey_query_date(char *buffer, size_t buffer_size)
{
	if(!buffer)
		return;

	timey_fmt_time(buffer, buffer_size, "[%m-%d-%Y]");
}

timey_timestamp timey_curr_timestamp()
{
	timey_timestamp ts = {0};

	// obtain time
	char time[TIMEY_TIME_STR_LEN];
	timey_query_time(time, sizeof time);

	// obtain specific time components from string
	char hour[3], min[3], sec[3];

	memcpy(hour, time + 1, 2);
	hour[2] = '\0';

	memcpy(min, time + 4, 2);
	min[2] = '\0';

	memcpy(sec, time + 7, 2);
	sec[2] = '\0';

	ts.hour = strtoul(hour, NULL, 10);
	ts.min = strtoul(min, NULL, 10);
	ts.sec = strtoul(sec, NULL, 10);

	return ts;
}
static void timey_next_hour(timey_timestamp *ts)
{
	ts -> min -= 60;
	ts -> hour += 1;
	if(ts -> hour > 24)
		ts -> hour -= 24;
}
timey_timestamp timey_future_timestamp(timey_timestamp *now, unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	timey_timestamp future = {0};

	if(!now)
		return future;

	future = *now;

	// add hours
	future.hour += hours;
	// continue to loop back 24 hours if necessary
	while(future.hour > 24)
		future.hour -= 24;

	// add minutes
	future.min += minutes;
	// continue to loop back an hour (60 minutes) if necessary
	while(future.min > 60)
		timey_next_hour(&future);

	// add seconds
	future.sec += seconds;
	// continue to loop back a minute and hour if necessary
	while(future.sec > 60)
	{
		future.sec -= 60;
		future.min += 1;
		if(future.min > 60)
			timey_next_hour(&future);
	}

	return future;
}

timey_datetime timey_curr_datetime()
{
	timey_datetime dt = {0};

	// obtain date
	char date[TIMEY_DATE_STR_LEN];
	timey_query_date(date, sizeof date);

	// obtain specific date-time components from string
	char month[3], day[3], year[5];

	memcpy(month, date + 1, 2);
	month[2] = '\0';

	memcpy(day, date + 4, 2);
	day[2] = '\0';

	memcpy(year, date + 7, 4);
	year[4] = '\0';

	dt.year = strtoul(year, NULL, 10);
	dt.month = strtoul(month, NULL, 10);
	dt.day = strtoul(day, NULL, 10);
	dt.is_leap_year = timey_is_leap_year(dt.year);
	dt.time = timey_curr_timestamp();

	return dt;
}
static void timey_next_year(timey_datetime *dt)
{
	dt -> month -= 12;
	dt -> year += 1;
	dt -> is_leap_year = timey_is_leap_year(dt -> year);
}
static void timey_add_days(timey_datetime *dt, unsigned int days)
{
	dt -> day += days;
	unsigned int max_month_days = timey_num_days_in_dt_month(dt);
	while(dt -> day > max_month_days)
	{
		dt -> day -= max_month_days;
		dt -> month += 1;
		if(dt -> month > 12)
			timey_next_year(dt);
		max_month_days = timey_num_days_in_dt_month(dt);
	}
}
timey_datetime timey_future_datetime(timey_datetime *now, unsigned int years, unsigned int months, unsigned int days, unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	timey_datetime future = {0};

	if(!now)
		return future;

	future = *now;

	// add years
	future.year += years;

	// add months
	future.month += months;
	// continue to increment year if necessary
	while(future.month > 12)
		timey_next_year(&future);

	// add days
	timey_add_days(&future, days);

	// add to timestamp (while tracking date-time components this time)
	timey_timestamp *ts = &future.time;

	ts -> hour += hours;
	while(ts -> hour > 24)
	{
		ts -> hour -= 24;
		timey_add_days(&future, 1);
	}

	ts -> min += minutes;
	while(ts -> min > 60)
	{
		ts -> min -= 60;
		ts -> hour += 1;
		if(ts -> hour > 24)
		{
			ts -> hour -= 24;
			timey_add_days(&future, 1);
		}
	}

	ts -> sec += seconds;
	while(ts -> sec > 60)
	{
		ts -> sec -= 60;
		ts -> min += 1;
		if(ts -> min > 60)
		{
			ts -> min -= 60;
			ts -> hour += 1;
			if(ts -> hour > 24)
			{
				ts -> hour -= 24;
				timey_add_days(&future, 1);
			}
		}
	}

	return future;
}

bool timey_is_leap_year(unsigned int year)
{
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

static const unsigned int TIMEY_DAYS[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
unsigned int timey_num_days_in_month(unsigned int month)
{
	return TIMEY_DAYS[month - 1];
}

unsigned int timey_num_days_in_dt_month(timey_datetime *dt)
{
	if(!dt)
		return 0;

	if(dt -> month == 1 || dt -> month == 3 || dt -> month == 5
			|| dt -> month == 7 || dt -> month == 8 || dt -> month == 10
			|| dt -> month == 12)
		return 31;
	else if(dt -> month == 2)
		return dt -> is_leap_year ? 29 : 28;
	else
		return 30;
}
