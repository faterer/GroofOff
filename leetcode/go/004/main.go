package main

import "fmt"

func min(n1, n2 int) int {
    if n1 < n2 {
        return n1
    }
    return n2
}

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
    n1 := len(nums1)
    n2 := len(nums2)
    n := n1 + n2
    nums := make([]int, n)
    i, j, k := 0, 0, 0
    for i < n1 && j < n2 {
        if nums1[i] < nums2[j] {
            nums[k] = nums1[i]
            k++
            i++
        } else {
            nums[k] = nums2[j]
            k++
            j++
        }
    }
    
    for i < n1 {
        nums[k] =  nums1[i]
        k++
        i++
    }
    
    for j < n2 {
        nums[k] = nums2[j]
        k++
        j++
    }
    
    for i := 0; i < n; i++ {
        fmt.Print(nums[i])
    }
    fmt.Print("\n")
        
    if n % 2 == 0 {
        fmt.Println("even")
        fmt.Println(nums[n/2])
	fmt.Println(nums[(n-1)/2])
        return float64((float64(nums[n/2]) + float64(nums[(n-1)/2])) / 2.0)
    } else {
	fmt.Println("odd")
        return float64(nums[n/2])
    }
}

func main() {
	fmt.Println(findMedianSortedArrays([]int{1,2}, []int{3,4}))

}
