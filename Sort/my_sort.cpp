#include <iostream>
#include <vector>
#include <map>
#include "my_sort.h"
using namespace std;

void swap(vector<int>& nums, int i, int j) {
	int temp;
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

void insertionSort(vector<int>& nums) {
	//O(n^2)
	//小规模数据或者数据基本有序时十分高效
	for (int i = 1; i < nums.size(); i++) {
		for (int j = i - 1; j >= 0 && nums[j] > nums[j + 1]; j--) {
			swap(nums, j, j+1);
		}
	}
}

void shellSort(vector<int>& nums) {
	//改进的插入排序，使得数组变得相对有序后再进行插入排序。
	for (int d = nums.size() / 2; d > 0; d = d / 2) { //d = 1时进行插入排序。
		for (int i = d; i < nums.size(); i++) {
			for (int j = i - d; j >= 0 && nums[j] > nums[j + d]; j = j - d) {
				swap(nums, j, j + d);
			}
		}
	}
}

void quickSort(vector<int>& nums, int left, int right) {
	//O(nlogn)
	//[left,right） 
	if (left + 1 >= right) {  //[left,left+1) indicates one element
		return;
	}
	int mid = left + (right - left) / 2;
	swap(nums, left, mid);
	int j = left;
	for (int i = left + 1; i < right; i++) {
		if (nums[i] < nums[left]) {
			swap(nums, ++j, i);
		}
	}
	
	swap(nums, left, j);
	
	quickSort(nums, left, j);
	quickSort(nums, j + 1, right);
}

void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
	//O(nlogn)
	//[left,right） 区间排序
	if (left + 1 >= right) {
		return;
	}
	int mid = left + (right - left) / 2;
	mergeSort(nums, left, mid,temp);
	mergeSort(nums, mid, right,temp);

	int index1 = left;
	int index2 = mid;
	int i = left;
	while (index1 < mid || index2 < right) {
		if (index2 == right || (index1 < mid && nums[index1] < nums[index2])) {
			temp[i++] = nums[index1++];
		}
		else {
			temp[i++] = nums[index2++];
		}
	}

	for (i = left; i < right; i++) {
		nums[i] = temp[i];
	}

}

void bubbleSort(vector<int>& nums) {
	//O(n^2)
	int len = nums.size();
	while (len > 1) {
		for (int i = 0; i < len - 1; i++) {
			if (nums[i] > nums[i + 1]) {
				swap(nums, i, i + 1);
			}
		}
		len--;
	}
}

void selectSort(vector<int>& nums) {
	int len = nums.size();
	int minIndex;
	for (int i = 0; i < len - 1; i++) {
		minIndex = i;
		for (int j = i + 1; j < len; j++) {
			if (nums[j] < nums[minIndex]) {
				minIndex = j;
			}
		}
		swap(nums, i, minIndex);
	}
}

void bucketSort(vector<int>& nums) { //计数排序
	map<int, int> counts;
	for (auto num : nums) {
		counts[num]++;
	}
	int index = 0;
	for (auto p : counts) {
		for (int i = 0; i < p.second; i++) {
			nums[index++] = p.first;
		}
	}
}