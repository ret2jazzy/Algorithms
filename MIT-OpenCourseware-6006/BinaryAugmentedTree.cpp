#include <iostream>

//This is type of binary tree which should be used in the Single Runway problem described in MIT lecture 4
//It checks that no number is in the 'k' time units of the new plane, which is passed to function by value
//It can also calculate the values which are less than a specific number(using the subtree length algo)
//Every plane is represented as a node
using namespace std;

struct Node {//Making the binary tree node
	int val;
	Node *right;
	Node *left;
	int subLength;
	Node(int value){//The default constructor of the Node
		val = value;
		subLength = 1;//The subtree length of each node
		right = NULL;
		left = NULL;
	}
};

void addNode(Node *&root, int val)//Adding a new Node(new plane time), I am passing the node as a reference to pointer, as otherwise, it gets passed by value
{
	if(root == NULL){
		root = new Node(val);
		return;
	}
	root->subLength += 1;//increasing the subtree length as we pass on from Node to Node
	if(val < root->val){
		addNode(root->left, val);
	}else {
		addNode(root->right, val);
	}
}

bool treeCheckContains(Node *root, int kMin, int val)//Check if the tree contains a specific val(val) within 'k' unit distance from each Node
{
	if(root == NULL){//If it reaches a empty Node, means it doesn't contain a value withing k units of val
		return true;
	}
	if(val >= root->val){
		if((val-kMin) <= root->val){
			return false;
		}
		return treeCheckContains(root->right, kMin, val);
	}else {
		if((val+kMin) >= root->val){
			return false;
		}
		return treeCheckContains(root->left, kMin, val);
	}
}

int lookUpBefore(Node *root, int val)//A function to lookup all the values before a speicific number, using the subtree algo
{
	if(root == NULL){
		return 0;
	}
	if(root->val < val){
		int leftval = 0;
		if(root->left != NULL){//Checking if left node exists, and then adding value
			leftval = root->left->subLength;
		}
		return 1+leftval+(lookUpBefore(root->right, val));
	}else return lookUpBefore(root->left, val);
}

int main()
{
	cout << "Enter the first val ";//The first Node, ot the first plane
	int p; cin >> p;
	Node *root = new Node(p);
	int howManyVals;
	cout << "Enter the amount of values you wish to add ";//The amount of planes which are scheduled to land, i.e the time for their arrival and k min check
	cin >> howManyVals;
	while(howManyVals--){
		cout << "Enter next value to add and the k min check ";//The time for next plane and k min
		int m, q;
		cin >> m >> q;
		if(treeCheckContains(root, q, m)){//Checking if no other plane is scheduled in k mins
			cout << "Min check has succeded" << endl;
			addNode(root, m);//Adding the Node
			cout << "Item has been added" << endl;
		}else {cout << "MIN CHECK FAILED, TRY ADDING ANOTHER ITEM" << endl;
		++howManyVals;
		}
	}
	int num;
	cout << "Enter what you want to lookup ";//The number of plane landings scheduled before a specific time
	cin >> num;
	cout << "The size is " << lookUpBefore(root, num) << endl;
}
