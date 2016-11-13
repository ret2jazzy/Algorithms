#include <iostream>
#include <stdlib.h>
using namespace std;

//This is a binary tree which keeps track of it's parent, the length of it's subtree and it has functions like finding successor and deleting a Node
//To delete a Node, I have used the parent pointers, I change the parent pointer of the left or right node of the Node(which has to be deleted)
//to the parent of the Node(which has to be deleted)
//The I change the pointer of the parent of the Node(to be deleted) to the next left or right node
//If the Node has two subtrees, then i find the lowest value in the Node's right subtree and swap the value with the node and then delete the node with lowest value

struct Node {//Making the binary tree node
	int val;
	Node *parent;
	Node *right;
	Node *left;
	int subLength;
	Node(int value, Node *par){//The default constructor of the Node
		val = value;
		subLength = 1;//The subtree length of each node
		right = NULL;
		left = NULL;
		parent = par;//The pointer to it's parent
	}
};

void addNode(Node *&root, int val, Node *parent)//Adding a new Node, I am passing the node as a reference to pointer, as otherwise, it gets passed by value
{
	if(root == NULL){
		root = new Node(val, parent);
		return;
	}
	root->subLength += 1;
	if(val < root->val){
		addNode(root->left, val, root);
	}else {
		addNode(root->right, val, root);
	}
}

bool treeCheckContains(Node *root, int val)//A function to check if the tree contains a value or not
{
	if(root == NULL){
		return true;
	}
	if(val == root->val){
		return false;
	}
	if(val > root->val){
		return treeCheckContains(root->right, val);
	}else {
		return treeCheckContains(root->left, val);
	}
}

int lowestSubtree(Node *node)//Fincding the lowest in a subtree
{
	if(node->left != NULL){
		return lowestSubtree(node->left);
	}else return node->val;
}

int upParentLowest(Node *node)//Finding the Node which is a left Node of it's parent, for the purpose of finding successor if right subtree is empty
{
	if(node->parent != NULL){
		if(node->val < node->parent->val){
			return node->parent->val;
		}else return upParentLowest(node->parent);
	}else return -1;
}

int successor(Node *node)//Just a function to see if right subtree is available or not, and then call appropriate functions
{
	if(node->right != NULL){
		return lowestSubtree(node->right);
	}else return upParentLowest(node);
}

int findSuccessor(Node *root, int val)//The function which finds the Node which has the value for which we need to find the successor
{
	if(root == NULL){
		return -1;
	}
	if(val == root->val){
		return successor(root);
	}
	if(val < root->val){
		return findSuccessor(root->left, val);
	}else return findSuccessor(root->right, val);
}
void delByVal(Node *&root, int value);

void delNode(Node *&node)//, The main function which deletes a node, Passing the Node to be deleted as the parameter
{
	if(node->left == NULL && node->right == NULL){//If it is a leaf, then just remove it
		free(node);
		return;
	}
	else if(node->left != NULL && node->right != NULL){//If it has two subtrees, then get the lowest from right subtree and write that value in thsi node, and delete that node
		int j = lowestSubtree(node->right);
		delByVal(node, j);//Deleting the node with lowest value in right subtree
		node->val = j;
		return;
	}
	else if(node->left != NULL){//If it only has left subtree
		node->left->parent = node->parent;//Pointing the parent of the Left node to this node's parent
		if(node->parent->left->val == node->val){//Checking if the node itself is the right or the left node of it's parent, node->parent takes it one node above, ->left takes 
			//it one node down to left, and ->val returnts its value, if the value matches with the value of this node, 
			//then it's the left node of it's parent, otherwise it's right
			node->parent->left = node->left;//Changing the pointer of parent node to it's left node
			free(node);//Deleting the node
			return;
		}else {
			node->parent->right = node->left;//checking the pointer if it's right node
			free(node);
			return;
		}
	}else if(node->right != NULL){//Same case as with the left subtree, but now with right
		node->right->parent = node->parent;
		if(node->parent->right->val == node->val){
			node->parent->right = node->right;
			free(node);
			return;
		}else {
			node->parent->left = node->right;
			free(node);
			return;
		}
	}
}

void delByVal(Node *&root, int value)//The function which finds the Node to be deleted, Just some simple recursion to find the Node
{
	if(root == NULL){
		cout << "No value found" << endl;
	}
	else if(root->val == value){
		delNode(root);
	}
	else if(value > root->val){
		delByVal(root->right, value);
	}else delByVal(root->left, value);
}

int main()
{
	cout << "Enter the first val ";
	int p; cin >> p;
	Node *root = new Node(p, NULL);
	int howManyVals;
	cout << "Enter the amount of values you wish to add ";
	cin >> howManyVals;
	while(howManyVals--){
		cout << "Enter next value to add ";
		int m;
		cin >> m;
		if(treeCheckContains(root, m)){
			cout << "Min check has succeded" << endl;
			addNode(root, m, root);
			cout << "Item has been added" << endl;
		}else {cout << "MIN CHECK FAILED, TRY ADDING ANOTHER ITEM" << endl;
		++howManyVals;
		}
	}
	cout << "Enter the Node whose successor you want ";
	int r;cin >> r;
	cout << "successor is " << findSuccessor(root, r) << endl;
	cout << "Enter the Value you want to delete ";
	int ab; cin >> ab;
	delByVal(root, ab);
	cout << "DELETED " << endl;
	cout << "Enter the Node whose successor you want ";
	int qp;cin >> qp;
	cout << "successor is " << findSuccessor(root, r) << endl;
}
