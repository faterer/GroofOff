/*
* sqr.c
*
*  Created on: Mar 5, 2015
*      Author: mawang
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* from john carmack quake III source code */
float carmack_sqrt(float number) {

	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return 1/y;
}

float bisection_sqrt(float n)
{
	float low,high,mid,last;
	low = 0;
	high = n;
	mid = (low+high)/2;
	do {
		if(mid*mid>n)
			high = mid;
		else
			low = mid;
		last = mid;
		mid = (high+low)/2;
	} while(fabs(mid-last)>FLT_EPSILON);

	return mid;
}

float newton_sqrt(float n)
{
	float val = n;
	float last;
	do
	{
		last = val;
		val = (val + n/val)/2;
	} while(fabs(val-last)>FLT_EPSILON);
	return val;
}

int main()
{
	float f = 2.0;
	printf("carmack sqr(%f)=%f\n",f,carmack_sqrt(f));
	printf("bisection sqr(%f)=%f\n",f,bisection_sqrt(f));
	printf("system sqr(%f)=%f\n",f,sqrt(f));
	printf("newton sqr(%f)=%f\n",f,newton_sqrt(f));
	return 0;
}

