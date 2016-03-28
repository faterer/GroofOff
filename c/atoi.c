/*
* atoi.c
*
*  Created on: Sep 16, 2014
*      Author: c programming language
*/
#include <stdio.h>

int atoi(char* s)
{
	int r = 0;
	int n = 0;
	int neg = 0;

	switch(*s) {
	case '-':
		neg = 1;
		s++;
		break;
	case '+':
		s++;
		break;
	}

	while (*s >= '0' && *s <= '9') {
		n = *s - '0';
		r = r * 10 + n;
		s++;
	}

	if (neg)
		r = -r;

	return r;
}

int main()
{
	char *s1 = "1234";
	char *s2 = "-1234";
	char *s3 = "+1234";

	printf("%d\n", atoi(s1));
	printf("%d\n", atoi(s2));
	printf("%d\n", atoi(s3));
	return 0;
}
