package main

import "fmt"

func max(i, j int) int {
    if (i < j) {
        return j
    }
    return i
}

func lengthOfLongestSubstring(s string) int {
    n := len(s)
    res := 0
    m := make(map[int]int, n)
    for i, j := 0, 0; j < n; j++ {
        idx, ok := m[int(s[j])]
        if ok {
            i = max(idx, i)
        }
        res = max(res, j - i + 1)
        m[int(s[j])] = j + 1
    }
    return res
}

func main() {
	fmt.Print(lengthOfLongestSubstring("abcabcbb"))
	fmt.Print(lengthOfLongestSubstring("bbbbbb"))
	fmt.Print(lengthOfLongestSubstring("pwwkew"))
	fmt.Print(lengthOfLongestSubstring("c"))
	fmt.Print(lengthOfLongestSubstring("au"))
	fmt.Print("\n")
	//31312
}
