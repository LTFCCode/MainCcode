#include "stdafx.h"
//给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
struct Node {
	int val;
	Node *left;
	Node *right;
	Node *next;
};
//填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
//
//初始状态下，所有 next 指针都被设置为 NULL。
//
//进阶：
//你只能使用常量级额外空间。
//使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度
class Solution {
public:
	Node* connect(Node* root) {
		if (root == nullptr) {
			return root;
		}
		// 从根节点开始
		Node* leftmost = root;
		while (leftmost->left != nullptr) {
			// 遍历这一层节点组织成的链表，为下一层的节点更新 next 指针
			Node* head = leftmost;
			while (head != nullptr) {
				// CONNECTION 1
				head->left->next = head->right;
				// CONNECTION 2
				if (head->next != nullptr) {
					head->right->next = head->next->left;
				}
				// 指针向后移动
				head = head->next;
			}
			// 去下一层的最左的节点
			leftmost = leftmost->left;
		}
		return root;
	}
};
void Test116(){
	Solution Test;
}