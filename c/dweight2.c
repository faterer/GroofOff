//
//  dweight2.c
//  cprogramming
//
//  Created by carol on 2/11/15.
//  Copyright (c) 2015 carol. All rights reserved.
//

#include <stdio.h>

int main()
{
    int height, length, width, volume, weight;
    printf("Enter height of box: ");
    scanf("%d", &height);
    printf("Enter length of box: ");
    scanf("%d", &length);
    printf("Enter width of box: ");
    scanf("%d", &width);
    volume = height * length * width;
    weight = (volume + 165) / 166;
    printf("Volme (cube inches): %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", weight);
    return 0;
}