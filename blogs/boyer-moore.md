title: 字符串搜索之Boyer Moore
date: 2016-08-07 13:37
---
字符串搜索的操作是比较＋移步(shift)，如何高效的移步成为了这个算法的关键所在
最坏的移步就是一次移一步，即暴力解法(Brute Force)。那么优化的解法就是一次移多步。

字符串搜索算法汇总：[传送门](http://igm.univ-mlv.fr/~lecroq/string/)
里面详细介绍各种解法，真是有点多啊，囧
比较操作的时候算法中分为两类一类是从左向右比较即从开始字符到结束字符，另一类是从右向左比较即从结束字符到开始字符

<!-- more -->

本文主要学习Boyer Moore算法
维基百科上说，[Boyer Moore算法](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm)是1977年Robert S. Boyer和J Strother Moore发明的。
阮一峰有篇很好的对BoyerMoore算法的科普文：[传送门](http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html)
其中详述了一个Moore教授的例子
BoyerMoore关于移步最核心的就是两个概念
坏字符移步(bad-character shift)和好后缀移步(good-suffix shift)，弄明白这两个概念就明白了Boyer Moore.
在需要移步的时候考察这两个移步的步数，谁的值更大就选择谁来作为移步的步数
为了生成坏字符移步和好后缀移步，我们只需要对搜索的子(短)字符串进行处理，而不需要对目标(长)字符串进行处理。
glibc中关于子串搜索的函数strstr的这两个字符串的参数名字很有意境，前者叫needle，后者叫haystack，大海捞针啊，哈哈。

坏字符移步的生成比较容易理解：
先定义一个包含所有字符(考虑ASCII字符集，以及ASCII字符集扩展)，一共256个字符
```c
#define ALPHABET_LEN 256
int badCharacter[ALPHABET_LEN];
```
然后扫描needle串，生成坏字符移步。未在needle串中出现的坏字符的移步都是needle串长度即strlen(needle)
```c
    for (i = 0; i < ALPHABET_LEN; i++) {
        badcharacter[i] = needlelen;
    }
```
在needle串中出现过的坏字符的移步利用公式：needlelen - 1 - idx求得，idx代表从左到右对needle串进行扫描的索引，范围是从0到(needlelen - 1)。
```c
badcharacter[needle[i]] = needlelen - 1 - i;
```
考虑到在haystack串中移步时容易理解，移步时以最后一个字符作为移步的起点位置，所以上面公式求得的移步值，在移步时要减去字符相比最后字符位置的相对位置即减去(needlelen + 1 + idx)，idx代表从右到左对needle串进行扫描的索引，范围是从(needlelen - 1)到0。
```c
badcharacter[haystack[j+i]] - needlelen + 1 + i
```

好后缀移步生成：
参考维基百科的C语言实现
经过2次扫描needle串
第一次扫描是找是否有needle开始位置的前缀字符串能够与后缀字符串匹配的情况，并设置相应字符的好后缀移步
匹配类似下面这种场景
```c
ABCDAB
444461
```
```c
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
```
```c
for (p = needlelen - 1; p >= 0; p--) {
    if (is_prefix(needle, needlelen, p + 1)) {
        last_prefix_index = p + 1;
    }
    goodsuffix[p] = last_prefix_index + needlelen - 1 - p;
}
```
第二次扫描是找是否有needle中的字符串能够与字符串后缀最大值长度字符匹配的情况，并设置相应字符位置的好后缀移步
匹配类似下面这种场景
```c
BABCDAB
6666461
```
```c
int suffix_length(uint8_t *word, int wordlen, int pos) {
    int i;
    // increment suffix length i to the first mismatch or beginning
    // of the word
    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}
```
```c
for (p = 0; p < needlelen - 1; p++) {
    int slen = suffix_length(needle, needlelen, p);
    if (needle[p - slen] != needle[needlelen - 1 - slen]) {
        goodsuffix[needlelen - 1 - slen] = needlelen - 1 - p + slen;
    }
}
```
最后用教授的例子作为结束
```c
HERE IS A SIMPLE EXAMPLE
EXAMPLE
GsMoveStep=1
BcMoveStep=7
HERE IS A SIMPLE EXAMPLE
       EXAMPLE
GsMoveStep=1
BcMoveStep=2
HERE IS A SIMPLE EXAMPLE
         EXAMPLE
GsMoveStep=6
BcMoveStep=3
HERE IS A SIMPLE EXAMPLE
               EXAMPLE
GsMoveStep=1
BcMoveStep=2
HERE IS A SIMPLE EXAMPLE
                 EXAMPLE
```

[完整代码](https://github.com/faterer/groof_off/blob/master/c/string/boyer_moore_3.c)
