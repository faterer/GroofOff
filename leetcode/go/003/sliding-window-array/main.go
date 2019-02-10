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

// If we know that the charset is rather small, we can replace the Map with an integer array as direct access table.
// Commonly used tables are:
// int[26] for Letters 'a' - 'z' or 'A' - 'Z'
// int[128] for ASCII
// int[256] for Extended ASCII
func lengthOfLongestSubstring(s string) int {
    n := len(s)
    res := 0
    idx := [256]int{0}
    for i, j := 0, 0; j < n; j++ {
        i = max(idx[int(s[j])], i)  //
        res = max(res, j - i + 1)   //store max length to res
        idx[int(s[j])] = j + 1      //set character index
        fmt.Print(s[j], idx[int(s[j])], i, j - i + 1)
        fmt.Println()
    }
    return res
}

func main() {
    //lengthOfLongestSubstring("abcabcbb")
    lengthOfLongestSubstring("pwwkew")
	//fmt.Print(lengthOfLongestSubstring("abcabcbb"))
	//fmt.Print(lengthOfLongestSubstring("bbbbbb"))
	//fmt.Print(lengthOfLongestSubstring("pwwkew"))
	//fmt.Print(lengthOfLongestSubstring("c"))
	//fmt.Print(lengthOfLongestSubstring("au"))
	//fmt.Print("\n")
	//31312
}
