/*
* StringTest.cpp
*
*  Created on: Oct 17, 2014
*      Author: mawang
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string cs;

char foo2(char c1, char c2)
{
  char r;

  switch (c1)
  {
     case '0': r = '\x00'; break;
     case '1': r = '\x10'; break;
     case '2': r = '\x20'; break;
     case '3': r = '\x30'; break;
     case '4': r = '\x40'; break;
     case '5': r = '\x50'; break;
     case '6': r = '\x60'; break;
     case '7': r = '\x70'; break;
     case '8': r = '\x80'; break;
     case '9': r = '\x00'; break;
     case 'a': r = '\xa0'; break;
     case 'A': r = '\xa0'; break;
     case 'b': r = '\xb0'; break;
     case 'B': r = '\xb0'; break;
     case 'c': r = '\xc0'; break;
     case 'C': r = '\xc0'; break;
     case 'd': r = '\xd0'; break;
     case 'D': r = '\xd0'; break;
     case 'e': r = '\xe0'; break;
     case 'E': r = '\xe0'; break;
     case 'f': r = '\xf0'; break;
     case 'F': r = '\xf0'; break;
  }

  switch (c2)
  {
     case '0': r |= '\x00'; break;
     case '1': r |= '\x01'; break;
     case '2': r |= '\x02'; break;
     case '3': r |= '\x03'; break;
     case '4': r |= '\x04'; break;
     case '5': r |= '\x05'; break;
     case '6': r |= '\x06'; break;
     case '7': r |= '\x07'; break;
     case '8': r |= '\x08'; break;
     case '9': r |= '\x09'; break;
     case 'a': r |= '\x0a'; break;
     case 'A': r |= '\x0a'; break;
     case 'b': r |= '\x0b'; break;
     case 'B': r |= '\x0b'; break;
     case 'c': r |= '\x0c'; break;
     case 'C': r |= '\x0c'; break;
     case 'd': r |= '\x0d'; break;
     case 'D': r |= '\x0d'; break;
     case 'e': r |= '\x0e'; break;
     case 'E': r |= '\x0e'; break;
     case 'f': r |= '\x0f'; break;
     case 'F': r |= '\x0f'; break;
  }

  return r;
}

bool foo1(string& str)
{
  unsigned int i = 0;
  unsigned int j = 0;

  while (j < str.length()-1)
  {
     char c1 = str[j++];
     char c2 = str[j++];

     str[i++] = foo2(c1,c2);
  }

  if(j != str.length())
  {
     return false;
  }

  str.resize(str.length()/2);

  return true;
}

/*****************************************/

/*****************************************/


/*****************************************/
struct s_tag { int a[100]; };
struct s_tag orange, lime, lemon;
struct s_tag twofold(struct s_tag s) {
	int j;
	for (j = 0; j < 100; j++) {
		s.a[j] *= 2;
	}
	return s;
}

int main() {
	int i;
	for (i = 0; i < 100; i++) {
		lime.a[i] = 1;
	}
	lemon = twofold(lime);
	orange = lemon;
}
/*****************************************/
