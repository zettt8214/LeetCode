#pragma once
#include<vector>
using namespace std;

void insertionSort(vector<int>& nums);
void quickSort(vector<int>& nums, int left, int right);
void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp);
void bubbleSort(vector<int>& nums);
void selectSort(vector<int>& nums);
void shellSort(vector<int>& nums);
void swap(vector<int>& nums, int i, int j);
void bucketSort(vector<int>& nums);

