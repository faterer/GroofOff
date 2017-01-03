#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a)>(b)?(a):(b)

// length i |      1       2       3       4       5       6       7       8       9       10
// price Pi |      1       5       8       9       10      17      17      20      24      30
static int rod_price[] = {0,1,5,8,9,10,17,17,20,24,30};

static int count = 0;

int rod_cutting(int price, int length)
{
	int q = -1;

	if(length == 0)
		return 0;

	for(int i = 1; i <= length; i++) {
		q = max(q, rod_price[i] + rod_cutting(price, length - i));
		count++;
	}

	return q;
}

int memoized_rod_cut_aux(int price, int length, int r[])
{
	int q = 0;
	if(r[length] >= 0)
		return r[length];
	if(length == 0) {
		q = 0;
	} else {
		q = -1;
		for(int i = 1; i <= length; i++) {
			q = max(q, rod_price[i] + memoized_rod_cut_aux(price, length - i, r));
			count++;
		}
	}
	r[length] = q;
	return q;
}

int memoized_rod_cut(int price, int length)
{
	int *r = (int*)malloc(sizeof(int) * (length+1));
	for(int i = 0; i <= length; i++)
		r[i] = -1;
	return memoized_rod_cut_aux(price, length, r);
}

int bottom_up_rod_cut(int price, int length)
{
	int *r = (int*)malloc(sizeof(int) * (length+1));
	r[0] = 0;
	for(int j = 1; j <= length; j++) {
		int q = -1;
		for(int i = 1; i <= j; i++) {
			q = max(q, rod_price[i] + r[j - i]);
			count++;
		}
		r[j] = q;
	}	
	return r[length];
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
	
	printf("\n +++ rod_cutting +++ \n");
	count = 0;
	price = rod_cutting(price, 4);
	printf("compute 4 running %d loop\n", count);

	printf("\n +++ bottom_up_rod_cut +++ \n");
	count = 0;
	price = bottom_up_rod_cut(price, 4);
	printf("compute 4 running %d loop\n", count);

	printf("\n +++ memoized_rod_cut +++ \n");
	count = 0;
	price = memoized_rod_cut(price, 4);
	printf("compute 4 running %d loop\n", count);

	printf("\n +++ rod_cutting +++ \n");
	for(int i = 1; i <= 10; i++) {
		int price = 0; 
		price = rod_cutting(price, i);
		printf("length: %d\tprice: %d\n", i, price);
	}

	printf("\n +++ bottom_up_rod_cut +++ \n");
	for(int i = 1; i <= 10; i++) {
		int price = 0; 
		price = bottom_up_rod_cut(price, i);
		printf("length: %d\tprice: %d\n", i, price);
	}

	printf("\n +++ memoized_rod_cut +++ \n");
	for(int i = 1; i <= 10; i++) {
		int price = 0; 
		price = memoized_rod_cut(price, i);
		printf("length: %d\tprice: %d\n", i, price);
	}

	return 0;
}