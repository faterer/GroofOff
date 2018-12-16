// No.2 medium https://leetcode.com/problems/add-two-numbers/
// You are given two linked lists representing two non-negative numbers. 
// The digits are stored in reverse order and each of their nodes contain a single digit. 
// Add the two numbers and return it as a linked list.

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* c1 = l1;
        ListNode* c2 = l2;
        ListNode* sentinel = new ListNode(0);
        ListNode* c3 = sentinel;
        int sum = 0;
        
        while(c1 != NULL || c2 != NULL) {
            sum /= 10;
            if(c1 != NULL) {
                sum += c1->val;
                c1 = c1->next;
            }
            
            if(c2 != NULL) {
                sum += c2->val;
                c2 = c2->next;
            }
            
            c3->next = new ListNode(sum % 10);
            c3 = c3->next; 
        }
        
        if ((sum / 10))
            c3->next = new ListNode(1);
        
        return sentinel->next;
    }
};