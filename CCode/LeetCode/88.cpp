#include "stdafx.h"

void test88_1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	if (m == 0 || n == 0){
		if (m == 0){
			for (int i = 0; i != m + n; ++i) {
				nums1[i] = nums2[i];
			}
		}
		else{

		}
	}
	else{
		int p1 = 0, p2 = 0;
		int sorted[15];
		int cur;
		
		int max1 = nums1.back();
		int min1 = nums1.front();
		int max2 = nums2.back();
		int min2 = nums2.front();
		if (max1 <= min2)
		{
			for (int i = 0; i != n; ++i)
			{
				nums1[i + m] = nums2[i];
			}
		}
		while (p1 < m || p2 < n) {
			if (p1 == m) {
				cur = nums2[p2++];
			}
			else if (p2 == n) {
				cur = nums1[p1++];
			}
			else if (nums1[p1] < nums2[p2]) {
				cur = nums1[p1++];
			}
			else {
				cur = nums2[p2++];
			}
			sorted[p1 + p2 - 1] = cur;
		}
		for (int i = 0; i != m + n; ++i) {
			nums1[i] = sorted[i];
		}
	}
}
void test88(){
	vector<int>nums1;
	vector<int>nums2;
	sort(nums2.begin(), nums2.end());
	unordered_map<int, int>test;
	for (auto iter : test){
		nums2.emplace_back(iter.second);
	}
	nums1.push_back(1);
	nums1.push_back(2);
	nums1.push_back(3);
	nums1.push_back(0);
	nums1.push_back(0);
	nums1.push_back(0);
	nums2.push_back(2);
	nums2.push_back(5);
	nums2.push_back(6);
	test88_1(nums1,6,nums2,3);
}