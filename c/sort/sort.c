//
//  qsort.c
//  cprogramming
//
//  Created by carol on 2/25/15.
//  Copyright (c) 2015 carol. All rights reserved.
//  gcc -O -Wall -W -pedantic -ansi -std=c99 -o sort sort.c

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

// From The C programming Language
void swap(int v[], size_t i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void quick_sort(int v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quick_sort(v, left, last - 1);
    quick_sort(v, last + 1, right);
}


void quick_sort_2(int a[], int left, int right)
{
    int i = left;
    int j = right;
    int x = a[i];

    if (i >= j)
        return;

    while(i != j) {
        while(i < j && a[j] >= x)
            j--;
        a[i] = a[j];
        while(i < j && a[i] <= x)
            i++;
        a[j] = a[i];
    }
    a[i] = x;
    quick_sort_2(a, left, i - 1);
    quick_sort_2(a, i + 1, right);
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
    for(i = 1; i < n; i++)
    {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; j--)
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
    quick_sort_2(a, 0, ARRAY_SIZE(a)-1);
    printf("quick_sort_2: ");
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
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
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    bubble_sort(a, ARRAY_SIZE(a));
    printf("bubble_sort: ");
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    shuffle_array(a, ARRAY_SIZE(a));
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
    printf("%d,", a[i]);
    printf("\n");
    
    insertion_sort(a, ARRAY_SIZE(a));
    printf("insertion_sort: ");
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");

    shuffle_array(a, ARRAY_SIZE(a));
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
    printf("%d,", a[i]);
    printf("\n");

    shell_sort(a, ARRAY_SIZE(a));
    printf("shell_sort: ");
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    
    return 0;
}
