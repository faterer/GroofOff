/*
* itoa.c
*
*  Created on: Sep 16, 2014
*      Author: c programming language
*/
#include <stdio.h>
#include <string.h>

static const char digits[] = "9876543210123456789";
static const char* zero = digits + 9;

void reverse(char s[])
{
   int i, j;
   char c;

   for(i = 0, j = strlen(s) - 1; i < j; i++,j--)
   {
       c = s[i];
       s[i] = s[j];
       s[j] = c;
   }
}

void itoa_1(int value, char buf[])
{
	int i = value;
	int lsd;
	char *p = buf;

	do {
		lsd = i % 10;
		i /= 10;
		*p++ = zero[lsd];
	}while(i != 0);

	if (value < 0)
	{
		*p++ = '-';
	}
	*p = '\0';
	reverse(buf);
}

void itoa_2(int n, char s[])
{
	int sign;
	int i = 0;

	if ((sign = n) < 0)
		n = -n;

	do
	{
		s[i++] = n % 10 + '0';
	} while ((n = n / 10) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main()
{
   int a1 = -123;
   int a2 = 123;
   char s1[10];
   char s2[10];

   itoa_1(a1, s1);
   printf("%s\n", s1);
   itoa_1(a2, s2);
   printf("%s\n", s2);
   itoa_2(a1, s1);
   printf("%s\n", s1);
   itoa_2(a2, s2);
   printf("%s\n", s2);
   return 0;
}
