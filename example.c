#include <stdio.h>
#include "timey.h"

void print_time(timey_timestamp *ts)
{
	printf("\t%u:%u:%u %s\n", ts -> hour12, ts -> min, ts -> sec, ts -> period);
}
void print_date(timey_datetime *dt)
{
	printf("\t%s, %s %u, %u\n", dt -> day_name, dt -> month_name, dt -> day, dt -> year);
}

int main()
{
	timey_datetime now = timey_curr_datetime();

	printf("\n");
	print_date(&now);
	print_time(&now.time);
	printf("\n");

	timey_datetime future = timey_future_datetime(&now, 0, 0, 0, 12, 0, 0);

	print_date(&future);
	print_time(&future.time);
	printf("\n");

	return 0;
}
