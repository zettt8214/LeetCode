#include "list.h"


/// <summary>
/// 206. Reverse Linked List
/// </summary>
ListNode* ReverseListRecursion(ListNode* head, ListNode* prev = nullptr) {
	if (!head) {
		return prev;
	}
	ListNode* next = head->next;
	head->next = prev;
	ReverseListRecursion(next, head);
}
ListNode* reverseList(ListNode* head) {
	ListNode* p = head,*prev = nullptr,*next;
	while (p) {
		next = p->next;
		p->next = prev;
		prev = p;
		p = next;
	}
	return prev;
	
	/* µ›πÈ–¥∑® return ReverseListRecursion(head) */
}


/// <summary>
/// 21. Merge Two Sorted Lists
/// </summary>
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode dummy(0);
	ListNode* d = &dummy;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			d->next = l1;
			l1 = l1->next;
		}
		else {
			d->next = l2;
			l2 = l2->next;
		}
		d = d->next;
	}

	d->next = l1 ? l1 : l2;

	return dummy.next;
}
ListNode* mergeTwoListsRecursion(ListNode* l1, ListNode* l2) {
	if (!l1) {
		return l2;
	}
	if (!l2) {
		return l1;
	}
	if (l1->val < l2->val) {
		l1->next = mergeTwoListsRecursion(l1->next, l2);
		return l1;
	}
	l2->next = mergeTwoListsRecursion(l1,l2->next);
	return l2;
}

/// <summary>
/// 24. Swap Nodes in Pairs
/// </summary>
ListNode* swapPairs(ListNode* head) {
	ListNode* p, *q,*prev;
	ListNode dummy;
	p = head;
	prev = &dummy;
	prev->next = p;

	while (p) {
		q = p->next;
		if (!q) {
			break;
		}
		p->next = q->next;
		q->next = p;
		prev->next = q;

		prev = p;
		p = p->next;
	}

	return dummy.next;
}

/// <summary>
/// 160. Intersection of Two Linked Lists
/// </summary>
ListNode* getIntersectionNode(ListNode*  headA, ListNode* headB) {
	ListNode* pa = headA, * pb = headB;
	if (!pa || !pb) {
		return nullptr;
	}

	while (pa != pb) {
		pa = pa == nullptr ? headB : pa->next;
		pb = pb == nullptr ? headB : pb->next;
	}
	return pa;
}


/// <summary>
/// 234. Palindrome Linked List
/// </summary>
ListNode* reverseListHelper(ListNode* head) {
	ListNode* p = head, * prev = nullptr, * next;
	while (p) {
		next = p->next;
		p->next = prev;
		prev = p;
		p = next;
	}
	return prev;
}

bool isPalindrome(ListNode* head) {
	ListNode* slow = head, * fast = head;
	if (!head || !head->next) {
		return true;
	}
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	slow->next = reverseListHelper(slow->next);
	slow = slow->next;
	while (slow) {
		if (head->val != slow->val) {
			return false;
		}
		slow = slow->next;
		head = head->next;
	}
	return true;
}