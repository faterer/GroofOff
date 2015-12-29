/*
 * AtoiTest.c
 *
 *  Created on: Sep 16, 2014
 *      Author: C Traps and Pitfalls
 */


int atoi(char* s)
{
	int r = 0;
	int n = 0;
	int neg = 0;
    
	switch(*s) {
        case '-':
            neg = 1;
        case '+':
            s++;
            break;
	}    
    
	while (*s >= '0' && *s <= '9') {
		n = *s++ - '0';
		r = r * 10 + n;
	}
    
	if (neg)
		r = -r;
    
	return r;
}

void AtoiTest()
{
	const char *s1 = "1234";
	const char *s2 = "-1234";
	const char *s3 = "+1234";
    
	printf("%d\n", atoi(s1));
	printf("%d\n", atoi(s2));
	printf("%d\n", atoi(s3));
}
