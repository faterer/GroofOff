#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_LEN 256
#define NOT_FOUND patlen
#define max(a, b) ((a < b) ? b : a)

#define PRINT_TABLE(table, len) \
do {\
    for(int i = 0; i < len; i++)\
    printf("%d,", table[i]);\
    printf("\n");\
}while(0)

void make_delta1(int *delta1, uint8_t *pat, int32_t patlen) {
    int i;
    for (i = 0; i < ALPHABET_LEN; i++) {
        delta1[i] = NOT_FOUND;
    }
    for (i = 0; i < patlen - 1; i++) {
        delta1[pat[i]] = patlen - 1 - i;
    }
}

// true if the suffix of word starting from word[pos] is a prefix 
// of word
int is_prefix(uint8_t *word, int wordlen, int pos) {
    int i;
    int suffixlen = wordlen - pos;
    // could also use the strncmp() library function here
    for (i = 0; i < suffixlen; i++) {
        if (word[i] != word[pos+i]) {
            return 0;
        }
    }
    return 1;
}

// length of the longest suffix of word ending on word[pos].
// suffix_length("dddbcabc", 8, 4) = 2
int suffix_length(uint8_t *word, int wordlen, int pos) {
    int i;
    // increment suffix length i to the first mismatch or beginning
    // of the word
    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}

void make_delta2(int *delta2, uint8_t *pat, int32_t patlen) {
    int p;
    int last_prefix_index = patlen - 1;

    // first loop
    for (p = patlen - 1; p >= 0; p--) {
        if (is_prefix(pat, patlen, p + 1)) {
            last_prefix_index = p + 1;
        }
        delta2[p] = last_prefix_index + patlen - 1 - p;
    }
    PRINT_TABLE(delta2, patlen);
    // second loop
    for (p = 0; p < patlen - 1; p++) {
        int slen = suffix_length(pat, patlen, p);
        if (pat[p - slen] != pat[patlen - 1 - slen]) {
            delta2[patlen - 1 - slen] = patlen - 1 - p + slen;
        }
    }
    PRINT_TABLE(delta2, patlen);
}

uint8_t* boyer_moore (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen) {
    int i,j;
    int delta1[ALPHABET_LEN];
    int *delta2 = (int *)malloc(patlen * sizeof(int));
    make_delta1(delta1, pat, patlen);
    make_delta2(delta2, pat, patlen);

    // The empty pattern must be considered specially
    if (patlen == 0) return string;

    j = 0;
    while (j <= stringlen - patlen) {
        printf("%s\n", string);
        for(int s = 0; s < j; s++) printf(" ");
        printf("%s\n", pat);
        for (i = patlen - 1; i >= 0 && string[j+i] == pat[i]; --i);
        if (i < 0) {
            free(delta2);
            return (string + j);
        }
        else {
            printf("GsMoveStep=%d\n", delta2[i] - patlen + 1 + i);
            printf("BcMoveStep=%d\n", delta1[string[j+i]] - patlen + 1 + i);
            int k = max(delta1[string[j+i]] - patlen + 1 + i, delta2[i] - patlen + 1 + i);
            j += k;
        }
    }
    free(delta2);
    return NULL;
}
int main(int argc, char const *argv[])
{
    char *s1 = "HERE IS A SIMPLE EXAMPLE BABCDAB";
    //char *s2 = "BABCDAB";
    char *s3 = "EXAMPLE";
    //char *idx1 = (char *)boyer_moore((uint8_t*)s1, (uint32_t)strlen(s1), (uint8_t*)s2, (uint32_t)strlen(s2));
    char *idx2 = (char *)boyer_moore((uint8_t*)s1, (uint32_t)strlen(s1), (uint8_t*)s3, (uint32_t)strlen(s3));
    //printf("%s\n", idx1);
    printf("%s\n", idx2);
    return 0;
}