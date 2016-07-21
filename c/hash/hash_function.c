#include <stdio.h>

#define PRIME_TBLSIZ (20)

unsigned int hashpjw(const void *key)
{
    const char *ptr = key;
	unsigned int val = 0;
	
	while (*ptr != '\0')
	{
	    unsigned int tmp;
		val = (val << 4) + (*ptr);
		
		if (tmp = (val & 0xf0000000)
		{
		    val = val ^ (tmp >> 24);
            val = val ^ tmp;			
		}
	    
		ptr++;
	}
	
	return val % PRIME_TBLSIZ;
}

int main(void)
{
    char *str[] = {"hello", "world", "father", "mother", "I", "love", "you"};
	int i;
	int size = sizeof str / sizeof *str;
	
	for (i = 0; i < size; i++)
    {
	    printf("hash(%s)=%d\n", str[i], hashpjw(str[i]));	
	}
	
	return 0;
}
