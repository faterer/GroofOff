#include <time.h>
#include <stdio.h>
#include <string.h>

int main()
{
	time_t tv;
	struct tm tm_v;
	struct tm *p;
	char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	memset((void *)&tm_v, 0 ,sizeof(struct tm));
	tv = time(NULL);
	p = localtime_r(&tv, &tm_v);
	printf("current second: %ld\n", tv);
	printf ("%d-%d-%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
}