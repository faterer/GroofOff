#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a)>(b)?(a):(b)

static int rod_price[] = {0,1,5,8,9,10,17,17,20,24,30};

int rod_cutting(int price, int length)
{
	int q = -1;

	if(length == 0)
		return 0;

	for(int i = 1; i <= length; i++) {
		q = max(q, rod_price[i] + rod_cutting(price, length - i));
	}

	return q;
}


int main()
{
	int price = 0;
	
	printf("length i |\t");
	for(int i = 1; i < sizeof(rod_price)/sizeof(int); i++) {
		printf("%d\t", i);
	}
	printf("\n");
	printf("price Pi |\t");
	for(int i = 1; i < sizeof(rod_price)/sizeof(int); i++) {
		printf("%d\t", rod_price[i]);
	}
	printf("\n");
	for(int i = 1; i <= 10; i++) {
		int price = 0; 
		price = rod_cutting(price, i);

		printf("length: %d\tprice: %d\n", i, price);
	}

	return 0;
}