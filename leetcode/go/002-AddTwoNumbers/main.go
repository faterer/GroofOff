package main
// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

// Example:

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// Explanation: 342 + 465 = 807.

type ListNode struct {
	Val int
	Next *ListNode
}

//遍历2个链表，各自相加并创建新链表保存相加后的值
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    c1, c2 := l1, l2
    sentinel := new(ListNode)
    c3 := sentinel
    sum := 0
    
    for c1 != nil || c2 != nil {
		//和值除以10，在和本次的和做相加，解决了进位的问题
        sum /= 10
        if c1 != nil {
            sum += c1.Val
            c1 = c1.Next
        }
        
        if c2 != nil {
            sum += c2.Val
            c2 = c2.Next
        }
        
        c3.Next = new(ListNode)
        c3 = c3.Next
        c3.Val = sum % 10
    }
    
    if sum/10 > 0 {
        c3.Next = new(ListNode)
        c3 = c3.Next
        c3.Val = 1  
    }
    
    return sentinel.Next
}

func main() {

}