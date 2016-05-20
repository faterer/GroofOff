#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASIZE 256

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define OUTPUT(index) printf("%d\n", index)

//Boyer-Moore algorithm
int BM(char *x, int m, char *y, int n);

int strStr(char* haystack, char* needle) {
	int h_len = (int)strlen(haystack);
	int n_len = (int)strlen(needle);   

	return BM(needle, n_len, haystack, h_len);
}

//Bad character
void preBmBc(char *x, int m, int bmBc[]) {
   int i;
 
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[x[i]] = m - i - 1;
}
 
 
void suffixes(char *x, int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && x[g] == x[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}

//Good suffix 
void preBmGs(char *x, int m, int bmGs[]) {
   int i, j;
   int *suff = (int *)malloc(m * sizeof(int));
 
   suffixes(x, m, suff);
   printf("suff:");
   for(i = 0; i < m; i++)
      printf("%d,", suff[i]);
   printf("\n");
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= 0; --i)
      if (suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}
 
 
int BM(char *x, int m, char *y, int n) {
   int i, j, k,bmBc[ASIZE];
   int *bmGs = (int *)malloc(m * sizeof(int));

   /* Preprocessing */
   /* Good suffix */
   preBmGs(x, m, bmGs);
   /* Bad character */
   preBmBc(x, m, bmBc);

   for(i = 0; i < m; i++)
      printf("%d,", bmGs[i]);
   printf("\n");
   for(i = (int)'A'; i <= (int)'Z'; i++)
      printf("%c:%d,", (char)i, bmBc[i]);
   printf("\n"); 
   /* Searching */
   j = 0;
   while (j <= n - m) {
      for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);
      if (i < 0) {
         return j;
      }
      else
         printf("bmGs=%d\n", bmGs[i]);
         printf("bmBc=%d\n", bmBc[y[i + j]] - m + 1 + i);
         k = MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
         printf("%d,\n", k);
         j += k;
   }
   return 0;
}


int main(int argc, char const *argv[])
{
	char *s1 = "ASIMPLEEXAMPLE  BABCDAB";
   //HERE IS A SIMPLE EXAMPLE  BABCDAB
   //BABCDABBABCDABBABCDABBABCDAB
	char *s2 = "BABCDAB";
   char *s3 = "EXAMPLE";
	int idx1 = strStr(s1, s2);
   int idx2 = strStr(s1, s3);
   //printf("%s\n", s1+idx);
	return 0;
}
