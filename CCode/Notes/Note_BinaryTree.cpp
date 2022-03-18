#include "stdafx.h"
typedef struct DataType{
	int test;
};
typedef struct TreeType{
	TreeType* Left;
	TreeType* Right;
	DataType Data;
};
class BinaryTree{
public:
	int size;
	TreeType *Root;
	BinaryTree(){
		this->size = 0;
	}
	BinaryTree(DataType data){
		this->size = 1;
		this->Root->Data = data;
	}
	BinaryTree(DataType data, TreeType left, TreeType right){
		this->size = 1;
		this->Root->Data = data;
		this->Root->Left = &left;
		this->Root->Right = &right;
	}
	BinaryTree(DataType *data, TreeType *left, TreeType *right){
		this->size = 1;
		this->Root->Data = *data;
		this->Root->Left = left;
		this->Root->Right = right;
	}
	int treesize();//��ȡԪ�ؽڵ������
	bool isEmpty();// �ж����Ƿ�Ϊ����
	void clear() ;// �����������Ԫ��
	void preorder(TreeType* demo);// ǰ�����
	void inorder(TreeType* demo);// �������
	void postorder(TreeType* demo);// �������
	void levelOrder(TreeType* demo);// �������
	int height() ;// �������ĸ߶�
	bool isComplete() ;// �ж��Ƿ�Ϊ��ȫ������
	bool isProper() ;// �ж��Ƿ�Ϊ�������
	bool toString() ;// ����toString��������״��ӡ������
private:
	void levelOrder(TreeType* left, TreeType* right);
};
int BinaryTree::treesize(){
	return this->size;
}
bool BinaryTree::isEmpty(){
	return this->size == 0;
}
void BinaryTree::clear(){
	this->size = 0;
	this->Root = new TreeType;
}
void BinaryTree::preorder(TreeType* demo){
	if (demo == NULL)						
	{
		return;
	}
	printf("%d ", demo->Data.test);
	preorder(demo->Left);			
	preorder(demo->Right);			
}
void BinaryTree::inorder(TreeType* demo){
	if (demo == NULL)
	{
		return;
	}
	preorder(demo->Left);
	printf("%d ", demo->Data.test);
	preorder(demo->Right);
}
void BinaryTree::postorder(TreeType* demo){
	if (demo == NULL)
	{
		return;
	}
	preorder(demo->Left);
	preorder(demo->Right);
	printf("%d ", demo->Data.test);
}
void BinaryTree::levelOrder(TreeType* demo){
	if (demo == NULL)
	{
		return;
	}
	printf("%d ", demo->Data.test);
	levelOrder(demo->Left, demo->Right);
}
void BinaryTree::levelOrder(TreeType* left, TreeType* right){
	if (left ==nullptr || right == nullptr){
		return;
	}
	printf("%d ", left->Data.test);
	printf("%d ", right->Data.test);
	levelOrder(left->Left, left->Right);
	levelOrder(right->Left, right->Right);

}
int BinaryTree::height(){
	int height = 0;
	return height;
}

void Tree_test(){
	DataType data;
	DataType test;
	data.test = 1;
	test = data;
	BinaryTree* tree = new BinaryTree(data);
	system("pause");
}