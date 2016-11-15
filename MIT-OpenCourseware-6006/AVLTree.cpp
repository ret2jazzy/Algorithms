#include <iostream>

using namespace std;
//This is an example of a self balancing binary search tree, aka AVL Tree
//There might be some bad coding practices, and some of them are because of some unknown errors
//I had to initialize new nodes in computeUp() function, because returning the values of new nodes from left and right rotate and assigning them 
//directly on the node and node->left/right was not working(which took me quite a bunch of hours to debug
struct Node {//Making the binary tree node
	int val;
	Node *right;
	Node *left;
	Node *parent;
	int height;
	Node(int value, Node *par){//The default constructor of the Node
		val = value;
		right = NULL;
		left = NULL;
		parent = par;
		height = 0;//The height of node is 0 when its made
	}
};

int heightOfNode(Node *node)//A function which calculates the height of the node, provided the left and right heights are legit
{
	if(node->left != NULL && node->right != NULL){
		return max(node->left->height, node->right->height);
	}else if(node->left != NULL){
		return node->left->height;
	}else if(node->right != NULL){ return node->right->height;}
	else return -1;//-1 so as we do 1+heightOfNode()
}

Node* leftRotate(Node *&node)//For Rotating the Node on the left
{
	Node *temp = node->right;//A pointer to the Node which will be moved upwards in place of this Node
	Node *temp2 = node;//A Pointer to this Node itself as we lose it in nect line when we change the parent of it's right
	temp->parent = node->parent;//Changing parent of the temp node to the parent of this node
	if(temp->parent != NULL){//Check if the parent is not null
		if(temp->parent->left == node){//Check if this node was the left node of it's parent, 
			temp->parent->left = temp;//and then changing parent's appropriate pointer to the temp
		}else temp->parent->right = temp;
	}
	temp2->right = temp->left;//Changing some other pointers and parent so as complete the rotation
	if(temp2->right != NULL){
		temp2->right->parent = temp2;
	}
	temp->left = temp2;//This Node itself becomes the left pointer of the node which was down
	temp2->parent = temp;
	temp2->height = 1+heightOfNode(temp2);//Recalculating both the heights
	temp->height = 1+heightOfNode(temp);
	return temp;//Returning pointer to the new node which moved up
}

Node* rightRotate(Node *&node)//The same as left rotation but with right pointers instead of left pointers
{
	Node *temp = node->left;
	Node *temp2 = node;
	temp->parent = node->parent;
	if(temp->parent != NULL){
		if(temp->parent->right == node){
			temp->parent->right = temp;
		}else temp->parent->left = temp;
	}
	temp2->left = temp->right;
	if(temp2->left != NULL){
		temp2->left->parent = temp2;
	}
	temp->right = temp2;
	temp2->parent = temp;
	temp2->height = 1+heightOfNode(temp2);
	temp->height = 1+heightOfNode(temp);
	return temp;
}

int heightDiff(Node *node)//A function which calculates the difference of heights of the nodes of a node
{
	if(node->left != NULL && node->right != NULL){
		return node->left->height - node->right->height;
	}else if(node->left != NULL){
		return node->left->height+1;
	}else if(node->right != NULL){ return 0-node->right->height-1;}
	else return 0;
}

Node* computeUp(Node *&node)//The function which was the hardest to debug, it goes up using parent pointers 
							//from the new node and recalculates their heights and balances the tree if it's unbalanced
{
	node->height = 1+heightOfNode(node);//Calculates the height of this node
	int hd = heightDiff(node);//Calculates the differnce in heights of both it's nodes
	if(hd > 1){//If the height is more on left side by factor of more than 1
		Node *node2 = NULL;//I had to initialize two more Nodes to handle the vales of new nodes after rotation
		Node *node3 = NULL;//Just because if i did like "node = rightRotate(node)", it won't work, and the location of node wouldn't change
		if(heightDiff(node->left) < 0){//Check if the height of node below it had more weight on right or left, and rotating appropriately
			node3 = leftRotate(node->left);//If it was more, then we would left rotate the left node, and then right rotate this node
			node2 = rightRotate(node3->parent);//Due to some unknown reason, the value of "node" wouldn't change, even if during the left rotate of it's left node, i changed the parent pointer
			//so i had to make these extra nodes
		}else node2 = rightRotate(node);
		if(node2->parent != NULL){//Check if a parent is available for the node, and then calling this function on parent
			return computeUp(node2->parent);
		}else return node2;//if no parent, then we are on root and we return this node
	}else if(hd < -1){//Same case as above, only if we have height more on the right side
		Node *node2 = NULL;
		Node *node3 = NULL;
		if(heightDiff(node->right) > 0){
			node3 = rightRotate(node->right);
			node2 = leftRotate(node3->parent);
		}else node2 = leftRotate(node);
		if(node2->parent != NULL){
			return computeUp(node2->parent);
		}else return node2;
	}else{//If their heights do not differ by more than 1 or -1, then it's balanced
		if(node->parent != NULL){//Then it checks if a parent is available, and then call's the function on parent
			return computeUp(node->parent);
		}else return node;//Or it returns this node if no parent is available(meaning it's the root node)
	}
}


Node* addNode(Node *&root, int val, Node *par)//Adding a new Node(new plane time), I am passing the node as a reference to pointer, as otherwise, it gets passed by value
{
	if(root == NULL){
		root = new Node(val, par);
		return computeUp(root);//Updating all the heights upto top and rebalancing the tree
	}
	if(val < root->val){//Just a recursive simple Node adder
		return addNode(root->left, val, root);
	}else {
		return addNode(root->right, val, root);
	}
}

bool treeCheckContains(Node *root, int val)//Check if the tree contains a specific val(val) within 'k' unit distance from each Node
{
	if(root == NULL){//If it reaches a empty Node, means it doesn't contain a value withing k units of val
		return true;
	}
	if(val == root->val){
		return false;
	}else if(val > root->val){
		return treeCheckContains(root->right, val);
	}else return treeCheckContains(root->left, val);
}

int main()
{
	cout << "Enter the first val ";//The first Node, ot the first plane
	int p; cin >> p;
	Node *root = new Node(p, NULL);
	int howManyVals;
	cout << "Enter the amount of values you wish to add ";//The amount of planes which are scheduled to land, i.e the time for their arrival and k min check
	cin >> howManyVals;
	while(howManyVals--){
		cout << "Enter next value to add ";//The time for next plane and k min
		int m;
		cin >> m;
		if(treeCheckContains(root, m)){//Checking if no other plane is scheduled in k mins
			cout << "Min check has succeded" << endl;
			root = addNode(root, m, NULL);//Adding the Node and the root is returned to this node
			cout << "root " << root->val << endl;//Outputing the value of the root node
			cout << "Item has been added" << endl;
		}else {cout << "MIN CHECK FAILED, TRY ADDING ANOTHER ITEM" << endl;
		++howManyVals;
		}
	}
}
