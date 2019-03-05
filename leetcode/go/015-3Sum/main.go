package main

import "fmt"
import "sort"


func threeSum(nums []int) [][]int {
	var res [][]int
	sort.Ints(nums)
	for i := 0; i < len(nums) - 2; i++ {
		if (i == 0 || (i > 0 && nums[i] != nums[i-1])) {
			lo := i + 1
			hi := len(nums) - 1
			sum := 0 - nums[i]
            for lo < hi {
                if (nums[lo] + nums[hi] == sum) {
					res = append(res, []int{nums[i], nums[lo], nums[hi]})
                    for lo < hi && nums[lo] == nums[lo+1] {
						lo++
					}
                    for lo < hi && nums[hi] == nums[hi-1] {
						hi--
					}
					lo++
					hi--
                } else if nums[lo] + nums[hi] < sum {
					lo++
				} else {
					hi--
				}
           }
        }
	}
	return res
}

func main() {
	fmt.Println(threeSum([]int{-1, 0, 1, 2, -1, -4}))
}