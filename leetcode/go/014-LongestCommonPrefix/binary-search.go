package main

import "fmt"
import "math"
import "strings"

func main() {
	fmt.Println(longestCommonPrefix([]string{"flower", "flow", "flight"}))
}

func longestCommonPrefix(strs []string) string {
	if len(strs) == 0 {
		return ""
	}
	minLen := math.MaxInt32
	for _, str := range strs {
		minLen = Min(minLen, len(str))
	}
	low, high := 1, minLen
	for low <= high {
		mid := (low + high) / 2
		if isCommonPrefix(strs, mid) {
			low = mid + 1
		} else {
			high = mid - 1
		}
	}

	return strs[0][0 : (low+high)/2]
}

func isCommonPrefix(strs []string, length int) bool {
	str := strs[0][0:length]
	for i := 1; i < len(strs); i++ {
		if !strings.HasPrefix(strs[i], str) {
			return false
		}
	}
	return true
}

func Min(x int, y int) int {
	if x < y {
		return x
	}
	return y
}
