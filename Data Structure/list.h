#pragma once
typedef struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
}ListNode;

ListNode* reverseList(ListNode* head);				/// 206. Reverse Linked List
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);/// 21. Merge Two Sorted Lists
ListNode* swapPairs(ListNode* head);				/// 24. Swap Nodes in Pairs
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB);	/// 160. Intersection of Two Linked Lists
bool isPalindrome(ListNode* head);					/// 234. Palindrome Linked List
ListNode* deleteDuplicates(ListNode* head);			/// 83. Remove Duplicates from Sorted List
ListNode* oddEvenList(ListNode* head);				/// 328. Odd Even Linked List
ListNode* removeNthFromEnd(ListNode* head, int n);	/// 19. Remove Nth Node From End of List
ListNode* sortList(ListNode* head);					/// 148. Sort List
