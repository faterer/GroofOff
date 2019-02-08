package main

import "fmt"
import "sort"
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
type ListNode struct {
    Val int
    Next *ListNode
}

func mergeKLists(lists []*ListNode) *ListNode {
    var ints []int
    for _, list := range lists {
        curr := list
        for curr != nil {
            ints = append(ints, curr.Val)
            curr = curr.Next
        }
    }
    sort.Ints(ints)

    head := new(ListNode)
    prev := head
    for _, val := range ints {
        curr := new(ListNode)
        curr.Val = val
        prev.Next = curr
        prev = curr
    }
    return head.Next
}

func main() {
    fmt.Println("MergeKLists")
    fmt.Println("MergeKLists")
}
