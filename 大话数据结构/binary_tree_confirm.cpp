#include <iostream>
#include <queue>

using namespace std;

/*
判断一棵树是否是完全二叉树的思路
1. 如果树为空，则直接返回错
2.如果树不为空：层序遍历二叉树
	2.1>如果一个结点左右孩子都不为空，则pop该节点，将其左右孩子入队列；
　　2.2>如果遇到一个结点，左孩子为空，右孩子不为空，则该树一定不是完全二叉树；
　　2.3>如果遇到一个结点，左孩子不为空，右孩子为空；或者左右孩子都为空；则该节点之后的队列中的结点都为叶子节点；该树才是完全二叉树，否则就不是完全二叉树
 */
struct treeNode{
	int val;
	treeNode *left;
	treeNode *right;
	treeNode(int x):val(x), left(nullptr), right(nullptr){}
};

bool isCompleteTree(treeNode *root){
	if(root == nullptr)
		return false;
	queue<treeNode*> tempQueue;
	tempQueue.push(root);
	while(!tempQueue.empty()){
		treeNode *pNode = tempQueue.front(); 
		if(pNode->left && pNode->right){
			tempQueue.pop();
			tempQueue.push(pNode->left);
			tempQueue.push(pNode->right);
		}
		if(pNode->left == nullptr && pNode->right)
			return false;
		if((pNode->left == nullptr && pNode->right == nullptr) || (pNode->left && pNode->right == nullptr)) {
			if(pNode->left && pNode->right == nullptr)
				tempQueue.push(pNode->left);
			while(!tempQueue.empty()){
				pNode = tempQueue.front();
				if(pNode->left == nullptr && pNode->right == nullptr)
					tempQueue.pop();
				else
					return false;
			}
			return true;
		}
	}
	return true;
}

void test(){
	treeNode *node1 = new treeNode(1);
	treeNode *node2 = new treeNode(2);
	treeNode *node3 = new treeNode(3);
	treeNode *node4 = new treeNode(4);
	treeNode *node5 = new treeNode(5);
	treeNode *node6 = new treeNode(6);
	treeNode *node7 = new treeNode(7);

	node1->left = node2;
	node1->right = node3;
	node2->left = node4;
	node2->right = node5;
	node3->left = node6;
	node3->right = node7;

	cout << isCompleteTree(node1) << endl;
}

void test1(){
	treeNode *node1 = new treeNode(1);
	treeNode *node2 = new treeNode(2);
	treeNode *node3 = new treeNode(3);
	treeNode *node4 = new treeNode(4);
	treeNode *node5 = new treeNode(5);
	// treeNode *node6 = new treeNode(6);
	treeNode *node7 = new treeNode(7);

	node1->left = node2;
	node1->right = node3;
	node2->left = node4;
	node2->right = node5;
	// node3->left = node6;
	node3->right = node7;

	cout << isCompleteTree(node1) << endl;
}

int main(int argc, char const *argv[])
{
	
	test();
	test1();
	return 0;
}
