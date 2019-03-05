package main

import "fmt"

func main() {
	fmt.Println(longestCommonPrefix([]string{"flower", "flow", "flight"}))
}

func longestCommonPrefix(strs []string) string {
	n := len(strs)
	if n == 0 {
		return ""
	}

	for i := 0; i < len(strs[0]); i++ {
		c := strs[0][i]
		for j := 1; j < n; j++ {
			if i == len(strs[j]) || strs[j][i] != c {
				return strs[0][0:i]
			}
		}
	}

	return strs[0]
}
