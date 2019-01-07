package main

import "fmt"

func main() {
    fmt.Println(longestCommonPrefix([]string{"flower","flow","flight"}))

}


func longestCommonPrefix(strs []string) string {
    if len(strs) == 0 {
        return ""
    }
    return longestCommonPrefixHelper(strs, 0, len(strs) - 1)
}

func longestCommonPrefixHelper(strs []string, l int, r int) string {
    if l == r {
        return strs[l]
    } else {
        mid := (l + r)/2
        lcpLeft := longestCommonPrefixHelper(strs, l, mid)
        lcpRight := longestCommonPrefixHelper(strs, mid+1, r)
        return CommonPrefix(lcpLeft, lcpRight)
    }
}

func CommonPrefix(left string, right string) string {
    min := Min(len(left), len(right))
    for i := 0; i < min; i++ {
        if left[i] != right[i] {
            return left[:i]
        }
    }
    return left[:min]
}

func Min(x int, y int) int {
    if x < y {
        return x
    }
    return y
}
