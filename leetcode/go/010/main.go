package main

import "fmt"

func isMatch(s string, p string) bool {
    if len(p) == 0 {
        return len(s) == 0
    }
    
    if len(p) > 1 && p[1] == '*' {
        return isMatch(s, p[2:]) || len(s) > 0 && (s[0] == p[0] || '.' == p[0]) && isMatch(s[1:], p)
    } else {
        return len(s) > 0 && (s[0] == p[0] || '.' == p[0]) && isMatch(s[1:], p[1:])
    }
}

func main() {
	fmt.Println(isMatch("aa", "a*"))
	fmt.Println(isMatch("ab", ".*"))
	fmt.Println(isMatch("aab", "c*a*b"))
	fmt.Println(isMatch("mississippi", "mis*is*p*."))
}