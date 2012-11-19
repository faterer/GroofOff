/* issort.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2))
{
	char *a = data;
	void *key;
	int  i,j;
	
	if ((key = (char*)malloc(esize)) == NULL)
	return -1;
	
	for (j = 1; j < size; j++)
	{
		memcpy(key, &a[j * esize], esize);
		i = j - 1;
		
		while(i >=0 && compare(&a[i * esize], key) > 0)
		{
			memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
			i--;
		}
		
		memcpy(&a[(i + 1) * esize], key, esize);
	}
	
	free(key);
	
	return 0;
}

int compare_int(const void *key1, const void *key2)
{
	return *(int *)key1 - *(int *)key2;
}

int main(int argc, char *argv[])
{
	int a[5] = {4,3,1,2,5};
	int i;
	
	issort(a, sizeof(a)/sizeof(int), sizeof(int), compare_int);
	
	for (i = 0; i < 5; i++)
	printf("%d\n", a[i]);
	
	return 0;
}
