#include <unordered_map>
#include <iostream>
#include <stack>
#include <map>
#include "str.h"
using namespace std;

/// <summary>
/// 242. Valid Anagram
/// </summary>
bool isAnagram(string s, string t) {
	map<char, int> hash;

	if (s.size() != t.size()) {
		return false;
	}

	for (int i = 0; i < s.size(); i++) {
		hash[s[i]]++;
		hash[t[i]]--;
	}

	for (auto h : hash) {
		if (h.second != 0) {
			return false;
		}
	}
	return true;
}


/// <summary>
/// 205. Isomorphic Strings
/// </summary>
bool isIsomorphic(string s, string t) {
	unordered_map<char, char> s_hash;
	unordered_map<char, char> t_hash;
	if (s.size() != t.size()) {
		return false;
	}

	for (int i = 0; i < s.size(); i++) {
		char x = s[i], y = t[i];
		if ((s_hash.count(x) && s_hash[x] != y) || (t_hash.count(y) && t_hash[y] != x)) {
			return false;
		}
		s_hash[x] = y;
		t_hash[y] = x;
	}
	return true;
}

/// <summary>
/// 647. Palindromic Substrings
/// </summary>
static int countSubstringsHelper(string s, int l, int r) {
	int count = 0;
	while (l >= 0 && r < s.size() && s[l] == s[r]) {
		l--;
		r++;
		count++;
	}
	return count;
}

int countSubstrings(string s) {
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		count += countSubstringsHelper(s, i, i);
		count += countSubstringsHelper(s, i, i + 1);
	}
	return count;
}

/// <summary>
/// 696. Count Binary Substrings
/// </summary>
int countBinarySubstrings(string s) {
	vector<int> helper;
	
	int char_count = 1;
	char cur_char = s[0];

	for (int i = 1; i < s.size(); i++) {
		if (s[i] == cur_char) {
			char_count++;
		}
		else {
			helper.push_back(char_count);
			char_count = 1;
			cur_char = s[i];
		}
	}
	helper.push_back(char_count);

	int count = 0;
	for (int i = 0; i < helper.size() - 1; i++) {
		count += ::min(helper[i], helper[i + 1]);
	}

	return count;
}

/// <summary>
/// 227. Basic Calculator II
/// </summary>
static inline int priority(char op1) {
	switch (op1) {
	case '+': return 0;
	case '-':return 0;
	case '*':return 1;
	case '/':return 1;
	}
}

int calculate(string s) {
	stack<char> symbols;
	
	int i = 0;
	string postfix_str = "";
	/* 中缀表达式转后缀表达式 */
	while (s[i]!='\0') {
	
		if (::isdigit(s[i])) {
			for(; isdigit(s[i]) && s[i]!='\0';i++)
				postfix_str += s[i];
			postfix_str += '#';
			i--;
		}
		
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			while (!symbols.empty() && priority(s[i]) <= priority(symbols.top())) {
				postfix_str += symbols.top();
				symbols.pop();
			}
			symbols.push(s[i]);
		}
		i++;
	}
	while (!symbols.empty()) {      //最后，如果栈不空，则弹出所有元素并输出
		postfix_str += symbols.top();
		symbols.pop();
	}

	cout << postfix_str;
	stack<int> value;
	string num = "";
	/* 逆波兰式计算 */
	for (int i = 0; i < postfix_str.size(); i++) {
		if (::isdigit(postfix_str[i])) {
			num += postfix_str[i];
		}
		else {
			if (postfix_str[i]=='#') {
				value.push(stoi(num));
				num = "";
			}
			else {
				int val2 = value.top();
				value.pop();
				int val1 = value.top();
				value.pop();

				switch (postfix_str[i]) {
				case '+': 
					value.push(val1 + val2);
					break;
				case '-':
					value.push(val1 - val2);
					break;
				case '*':
					value.push(val1 * val2);
					break;
				case '/':
					value.push(val1 / val2);
					break;
				}
			}
		}
		
		
	}
	return value.top();
}


/// <summary>
/// 28. Implement strStr()
/// </summary>
static vector<int> PrefixComputing(string s) {
	
	vector<int> prefix(s.size(), 0);
	/* s中已匹配字符数 */
	int k = 0;

	/* 本质是由s[0:] 取匹配 s[1:] 求s[0:i]后缀的关于s的最长前缀 */
	for (int i = 1; i < s.size(); i++) {  
		while (k > 0 && s[k] != s[i]) {
			k = prefix[k - 1];		//前面匹配了k个字符，第k+1个字符匹配失败，对应位置偏移prefix[k-1]
		}
		if (s[k] == s[i]) {
			k++;
		}
		prefix[i] = k;
	}
	return prefix;
}

int strStr(string haystack, string needle) {
	if (needle.size() == 0) {
		return 0;
	}

	vector<int> prefix = PrefixComputing(needle);

	int k = 0;
	for (auto x : prefix) {
		cout << x << " ";
	}
	for (int i = 0; i < haystack.size(); i++) {
		while (k > 0 && needle[k] != haystack[i]) {
			k = prefix[k - 1];
		}
		if (needle[k] == haystack[i]) {
			k++;
		}
		if (k == needle.size()) {
			return i - needle.size() + 1;
		}
	}
	return -1;
}

/// <summary>
/// 409. Longest Palindrome
/// </summary>
int longestPalindrome(string s) {
	map<char,int> hash;

	for (auto c : s) {
		hash[c]++;

	}

	int length = 0;
	bool flag = false;
	for (auto iter = hash.begin(); iter != hash.end(); iter++) {
		if (iter->second % 2 == 0) {
			length += iter->second;
		}
		else {
			length += iter->second - 1;
			flag = true;
		}
	}

	if (flag) {
		length++;
	}

	return length;
}


/// <summary>
/// 3. Longest Substring Without Repeating Characters
/// </summary>
int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> hash;
	int left = 0, right = 0;
	int length = 0;

	/** 滑动窗口 */
	while (right < s.size()) {
		hash[s[right]]++;
		if (hash[s[right]] == 2) {
			length = ::max(length, right - left);
			while (hash[s[right]] == 2) {
				hash[s[left]]--;
				left++;
			}
		}
		right++;
	}

	length = ::max(length, right - left);
	return length;
}

/// <summary>
/// 76. Minimum Window Substring
/// </summary>
string minWindow(string s, string t) {
	unordered_map<char, int> window;
	unordered_map<char, int> need;

	for (auto c : t) {
		need[c]++;
	}

	int left = 0, right = 0;
	string ans = "";
	int length = INT_MAX;
	int start = 0;
	int match = 0;
	while (right < s.size()) {
		
		if (need.count(s[right])) {
			window[s[right]]++;
			if (window[s[right]] == need[s[right]]) {
				match++;
			}
		}
		while (match == need.size()) {
			if (length > right - left + 1) {
				length = right - left + 1;
				start = left;
			}
			if (need.count(s[left])) {
				window[s[left]]--;
				if (window[s[left]] < need[s[left]]) {
					match--;
				}
			}
			left++;
			
		}
		right++;
	}

	ans = (length != INT_MAX ? s.substr(start, length) : "");
	return ans;
	
}

/// <summary>
/// 5. Longest Palindromic Substring
/// </summary>
pair<int,int> FindPalindromeSubstring(string s ,int l,int r) {
	int is_find = 0;
	int length = 0;
	int start = l;
	while (l >= 0 && r < s.size() && s[l]==s[r]) {
		is_find = 1;
		length = r - l + 1;
		start = l;
		l--;
		r++;
	}
	if (is_find) {
		return make_pair(length, start);
	}
	else {
		return make_pair(0, 0);
	}
	
}
string longestPalindrome5(string s) {
	int start = 0;

	int length = 0;
	for (int i = 0; i < s.size(); i++) {
		auto sub_info = FindPalindromeSubstring(s, i, i);
		if (sub_info.first > length) {
			length = sub_info.first;
			start = sub_info.second;
		}
		sub_info = FindPalindromeSubstring(s, i, i + 1);
		if (sub_info.first > length) {
			length = sub_info.first;
			start = sub_info.second;
		}
	}

	string ans;
	ans = length == 0 ? "" : s.substr(start, length);
	return ans;
}