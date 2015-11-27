//
//  qsort.c
//  cprogramming
//
//  Created by carol on 2/25/15.
//  Copyright (c) 2015 carol. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

void quick_sort(int a[], int right, int left)
{
    int i = right;
    int j = left;
    int key = a[i];
    
    if (i >= j)
        return;
    
    while (i != j) {
        while (i < j && key <= a[j]) {
            j--;
        }
        a[i] = a[j];
        while (i < j && key >= a[i]) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    quick_sort(a, right, i-1);
    quick_sort(a, i+1, left);
}

int binary_search(int a[], int key, int n)
{
    int mid;
    int low = 0;
    int high = n-1;
    
    while (low <= high) {
        mid = (low+high)/2;
        if (key > a[mid])
            low = mid + 1;
        else if(key < a[mid])
            high = mid - 1;
        else
            return mid;
    }
    
    return -1;
}

void bubble_sort(int a[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
}

/* Fisher_Yates */
void shuffle_array(int arr[], int len)
{
    int i = len, j;
    int temp;
    
    if (i == 0)
        return;
    
    while (--i) {
        j = rand() % (i+1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void insertion_sort(int a[], int n)
{
    int i,j,tmp;
    for(i=1;i<n;i++)
    {
        tmp = a[i];
        for (j=i;j>0&&a[j-1]>tmp;j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
}

void shell_sort(int a[], int n)
{
	int i,j,increment;
	int tmp;
	
	for(increment = n/2; increment > 0; increment /= 2)
		for(i = increment; i < n; i++)
		{
			tmp = a[i];
			for(j = i; i >= increment; j -= increment)
				if(tmp < a[j - increment])
					a[j] = a[j - increment];
				else
					break;
			a[j] = tmp;
		}
}

int main()
{
    int a[] = {2,1,5,8,4,6};
    quick_sort(a, 0, ARRAY_SIZE(a)-1);
    for (int i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    int key = 4;
    if (-1 == binary_search(a, key, ARRAY_SIZE(a)))
        printf("%d is not in array\n",key);
    else
        printf("%d is in array\n", key);
    
    key = 3;
    if (-1 == binary_search(a, key, ARRAY_SIZE(a)))
        printf("%d is not in array\n",key);
    else
        printf("%d is in array\n", key);
    
    shuffle_array(a, ARRAY_SIZE(a));
    for (int i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    bubble_sort(a, ARRAY_SIZE(a));
    for (int i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    shuffle_array(a, ARRAY_SIZE(a));
    for (int i=0;i<ARRAY_SIZE(a);i++)
    printf("%d,", a[i]);
    printf("\n");
    
    insertion_sort(a, ARRAY_SIZE(a));
    for (int i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    return 0;
}