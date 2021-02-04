#include <unordered_map>
#include "list.h"

using namespace std;

ListNode* createList(vector<int> a) {
	ListNode* dummy = new ListNode;
	ListNode* p = dummy;

	for (auto num : a) {
		p->next = new ListNode(num);
		p = p->next;
	}
	return dummy->next;
}

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
	
	/* 递归写法 return ReverseListRecursion(head) */
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


/// <summary>
/// 83. Remove Duplicates from Sorted List
/// </summary>
ListNode* deleteDuplicates(ListNode* head) {
	unordered_map<int, int> hash;
	ListNode* p = head;
	ListNode dummy;
	dummy.next = head;
	ListNode* prev = &dummy;

	while (p) {
		if (hash[p->val] > 0) {
			prev->next = p->next;
			delete p;
			p = prev->next;
		}
		else {
			hash[p->val]++;
			prev = prev->next;
			p = p->next;
		}
		
	}
	return dummy.next;
}

/// <summary>
/// 328. Odd Even Linked List
/// </summary>
ListNode* oddEvenList(ListNode* head) {
	ListNode* odd = head;
	if (!odd) {
		return head;
	}

	ListNode* even = odd->next;
	ListNode* temp = even;
	while (even && even->next) {
		odd->next = odd->next->next;
		even->next = even->next->next;

		odd = odd->next;
		even = even->next;
		
	}
	odd->next = temp;
	return head;

}


/// <summary>
/// 19. Remove Nth Node From End of List
/// </summary>
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* p = head;
	ListNode* q = head;
	ListNode* prev = head;
	while (n--) {
		q = q->next;
	}

	while (q) {
		prev = p;
		q = q->next;
		p = p->next;
	}

	if (p == head) {
		return p->next;
	}
	
	prev->next = p->next;
	delete p;
	return head;
}


/// <summary>
/// 148. Sort List
/// </summary>

ListNode* FindMid(ListNode* left, ListNode* right) {
	/* 快慢指针找中点 */
	ListNode* slow, * fast;
	slow = fast = left;
	while (fast != right && fast->next !=right) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

ListNode* MergeList(ListNode* l1, ListNode* l2) {
	ListNode dummy;
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

ListNode* MergeSortList(ListNode* left, ListNode* right) {
	/* 归并排序 */
	if (left->next == right) {
		left->next = nullptr;
		return left;
	}
	ListNode* mid = FindMid(left, right);
	return MergeList(MergeSortList(left, mid), MergeSortList(mid, right));
}

ListNode* sortList(ListNode* head) {
	if (!head) {
		return head;
	}
	return MergeSortList(head, nullptr);
}