#include <stdio.h>
#include "timey.h"

int main()
{
	timey_datetime now = timey_curr_datetime();

	printf("now:    %u:%u:%u, %u-%u-%u\n", now.time.hour, now.time.min, now.time.sec, now.month, now.day, now.year);

	timey_datetime future = timey_future_datetime(&now, 1, 3, 5, 0, 15, 105);

	printf("future: %u:%u:%u, %u-%u-%u\n", future.time.hour, future.time.min, future.time.sec, future.month, future.day, future.year);

	return 0;
}
