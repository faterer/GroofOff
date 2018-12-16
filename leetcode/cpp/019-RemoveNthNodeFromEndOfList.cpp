// No.19 easy https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// Given a linked list, remove the nth node from the end of list and return its head.
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.
// Note:
// Given n will always be valid.
// Try to do this in one pass
#include <iosteam>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x),next(NULL){}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode **t1 = &head, *t2 = head;

        for(int i = 1; i < n; ++i) {
        	t2 = t2->next;
        }

        while(t2->next) {
        	t1 = &((*t1)->next);
        	t2 = t2->next;
        }

        *t1 = (*t1)->next;
        return head;
    }

	void add(ListNode **head, int value) {
		ListNode** current = head;
		ListNode* entry = NULL;

		while(*current)
		{
			entry = *current;
			current = &entry->next;
		}

		if(entry)
			entry->next = new ListNode(value);
	}

	void print(ListNode *head) {
		ListNode* current = head;
		while(current) {
			cout << current->val << "->";
			current = current->next;
		}
		cout << "NULL" << endl;
	}    
};

int main()
{
	Solution s;
	//build link list
	ListNode* head = new ListNode(1);
	for(int i=2;i<6;i++) {
		s.add(&head, i);
	}
	s.print(head);

	//remove nth from end
	head = s.removeNthFromEnd1(head,1);
	//print link list
	s.print(head);

	return 0;
}