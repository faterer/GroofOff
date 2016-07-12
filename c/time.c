#include <time.h>
#include <stdio.h>
#include <string.h>

int main()
{
	time_t tv;
	struct tm time_tm;
	struct tm *p;
	char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	memset((void *)&time_tm, 0 ,sizeof(struct tm));
	tv = time(NULL);
	p = localtime_r(&tv, &time_tm);
	printf("localtime: %ld - %04d-%02d-%02d %02d:%02d:%02d\n", tv, (1900+time_tm.tm_year),
                   (1+time_tm.tm_mon),(time_tm.tm_mday),(time_tm.tm_hour),(time_tm.tm_min),(time_tm.tm_sec));
}