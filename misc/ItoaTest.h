/*
 * ItoaTest.c
 *
 *  Created on: Sep 16, 2014
 *      Author: K&R Implementation
 */
#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    int i, j;
    char c;
    
    for(i = 0, j = (int)strlen(s) - 1; i < j; i++,j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int sign;
    int i = 0;
    
    if ((sign = n) < 0)
        n = -n ;
    
    do
    {
        s[i++] = n % 10 + '0';
    }while((n = n / 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void ItoaTest()
{
    int a1 = -123;
    int a2 = 123;
    char s1[10];
    char s2[10];
    
    itoa(a1, s1);
    printf("%s\n", s1);
    itoa(a2, s2);
    printf("%s\n", s2);
}