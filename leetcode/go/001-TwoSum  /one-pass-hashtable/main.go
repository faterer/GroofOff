package main
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.

// Example:

// Given nums = [2, 7, 11, 15], target = 9,

// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].
import "fmt"

//遍历目标数组，target - 当前数组值，查看其值是否在map中，没有则将该值插入map，遍历到target-当前数组值=map中已有的值，则返回答案
func twoSum(nums []int, target int) []int {
    n := len(nums)
    m := make(map[int]int, n)
    for i := 0; i < n; i++ {
        j, ok := m[target - nums[i]]
        if ok {
            return []int{j, i}
        }
        m[nums[i]] = i
    }
    return []int{}
}

func main() {
    nums := []int{2,7,11,15}
    fmt.Println(twoSum(nums, 9))
}