package main

// Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating characters.

// Example 1:

// Input: "abcabcbb"
// Output: 3 
// Explanation: The answer is "abc", with the length of 3. 
// Example 2:

// Input: "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// Example 3:

// Input: "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3. 
//              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

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
