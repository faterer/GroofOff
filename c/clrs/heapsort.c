#include <stdio.h>

#define PARENT(index) (index/2)
#define LEFT(index) (2*index+1)
#define RIGHT(index) (2*index+2)
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//runs in O(lgn) time, is the key to maintaining max-heap property
void max_heapify(int a[], int len, int i)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = 0;
    if (l <= len-1 && a[l] > a[i])
        largest = l;
    else    
        largest = i;
    
    if (r <= len-1 && a[r] > a[largest])
        largest = r;
    if (largest != i) {
        swap(a, i, largest);
        max_heapify(a, len, largest);
    }
}

//runs in linear time, produces a max-heap from an unordered input array  
void build_max_heap(int a[], int len)
{
    for(int i = len/2 - 1; i >= 0; i--)
        max_heapify(a, len, i);
}

//runs in O(nlgn) time, sorts an array in place
void heapsort(int a[], int length)
{
    int len = length;
    build_max_heap(a, length);
    for(int i = length - 1; i > 0; i--) {
        swap(a, 0, i);
        len = len - 1;
        max_heapify(a, len, 0);
    }
}

int main()
{
    int a[] = {2,1,5,8,4,6};
    heapsort(a, ARRAY_SIZE(a));
    printf("heapsort: ");
    for (size_t i=0;i<ARRAY_SIZE(a);i++)
        printf("%d,", a[i]);
    printf("\n");
    return 0;
}