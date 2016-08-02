#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_LEN 256
#define NOT_FOUND needlelen
#define max(a, b) ((a < b) ? b : a)

#define PRINT_TABLE(table, len) \
do {\
    for(int i = 0; i < len; i++)\
    printf("%d,", table[i]);\
    printf("\n");\
}while(0)

void make_badcharacter(int *badcharacter, uint8_t *needle, int32_t needlelen) {
    int i;
    for (i = 0; i < ALPHABET_LEN; i++) {
        badcharacter[i] = NOT_FOUND;
    }
    for (i = 0; i < needlelen - 1; i++) {
        badcharacter[needle[i]] = needlelen - 1 - i;
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

void make_goodsuffix(int *goodsuffix, uint8_t *needle, int32_t needlelen) {
    int p;
    int last_prefix_index = needlelen - 1;

    // first loop
    for (p = needlelen - 1; p >= 0; p--) {
        if (is_prefix(needle, needlelen, p + 1)) {
            last_prefix_index = p + 1;
        }
        goodsuffix[p] = last_prefix_index + needlelen - 1 - p;
    }
    PRINT_TABLE(goodsuffix, needlelen);
    // second loop
    for (p = 0; p < needlelen - 1; p++) {
        int slen = suffix_length(needle, needlelen, p);
        if (needle[p - slen] != needle[needlelen - 1 - slen]) {
            goodsuffix[needlelen - 1 - slen] = needlelen - 1 - p + slen;
        }
    }
    PRINT_TABLE(goodsuffix, needlelen);
}

uint8_t* boyer_moore (uint8_t *haystack, uint32_t haystacklen, uint8_t *needle, uint32_t needlelen) {
    int i,j;
    int badcharacter[ALPHABET_LEN];
    int *goodsuffix = (int *)malloc(needlelen * sizeof(int));
    make_badcharacter(badcharacter, needle, needlelen);
    make_goodsuffix(goodsuffix, needle, needlelen);

    // The empty needletern must be considered specially
    if (needlelen == 0) return haystack;

    j = 0;
    while (j <= haystacklen - needlelen) {
        printf("%s\n", haystack);
        for(int s = 0; s < j; s++) printf(" ");
        printf("%s\n", needle);
        for (i = needlelen - 1; i >= 0 && haystack[j+i] == needle[i]; --i);
        if (i < 0) {
            free(goodsuffix);
            return (haystack + j);
        }
        else {
            printf("GsMoveStep=%d\n", goodsuffix[i] - needlelen + 1 + i);
            printf("BcMoveStep=%d\n", badcharacter[haystack[j+i]] - needlelen + 1 + i);
            int k = max(badcharacter[haystack[j+i]] - needlelen + 1 + i, goodsuffix[i] - needlelen + 1 + i);
            j += k;
        }
    }
    free(goodsuffix);
    return NULL;
}
int main(int argc, char const *argv[])
{
    char *s1 = "HERE IS A SIMPLE EXAMPLE";
    //char *s2 = "BABCDAB"
    char *s3 = "EXAMPLE";
    //char *idx1 = (char *)boyer_moore((uint8_t*)s1, (uint32_t)strlen(s1), (uint8_t*)s2, (uint32_t)strlen(s2));
    char *idx2 = (char *)boyer_moore((uint8_t*)s1, (uint32_t)strlen(s1), (uint8_t*)s3, (uint32_t)strlen(s3));
    //printf("%s\n", idx1);
    printf("%s\n", idx2);
    return 0;
}