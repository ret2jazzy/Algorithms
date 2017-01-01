#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <list>
using namespace std;
//This is a simple DFS for topological sort of a graph, I used Nodes instead of ints just for a little more complexity
//This is topological sort only work on directed acyclic graph, and is used for shortest path problems
struct Node{
	int val;
	Node(int _val):val(_val){}//The constructor
};

class Graph{
private:
	map<Node*,list<Node*> >adjList;//The adjacency list of the graph
public:
	void addNode(Node *a, Node *b){//The function to add a edge between nodes
		adjList[a].push_back(b);
	}
	void topDFS(Node *a, stack<Node*>&topOrd, map<Node*, bool>&visited){//The simple recursive DFS function, modified for topological sort
		visited[a] = true;//Mark the node we are on as visited
		for(auto i = adjList[a].begin(); i != adjList[a].end();++i){//Look at the adjacency list of the node
			if(!visited[*i]){//If it hasn't been visited, then run the recursice DFS on it
				topDFS(*i, topOrd, visited);
			}
		}
		topOrd.push(a);//Push the current Node on the stack after all it's next nodes are pushed by the recursive calls
	}
	stack<Node*>topologicalSort(){//The function which runs the modified DFS on all nodes
		map<Node*, bool>visited;//The hash table for visited nodes
		stack<Node*>topOrd;//The stack which stores the topological order
		for(auto i = adjList.begin(); i != adjList.end();++i){//Running the DFS on all the nodes 
			if(!visited[i->first]){
				topDFS(i->first, topOrd, visited);
			}
		}
		return topOrd;//returning the topological ordered stack
	}
};

int main()
{
	Graph lol;
	Node *p = new Node(3);//Adding random nodes
	Node *m = new Node(5);
	Node *r = new Node(0);
	Node *k = new Node(1);
	Node *l = new Node(2);
	Node *q = new Node(4);
	lol.addNode(m,l);//adding them
	lol.addNode(m,r);
	lol.addNode(q,r);
	lol.addNode(q,k);
	lol.addNode(l,p);
	lol.addNode(p,k);
	stack<Node*>topsorted = lol.topologicalSort();//Getting their topological order
	while(!topsorted.empty()){
		cout << topsorted.top()->val << endl;//outputting their value
		topsorted.pop();
	}
}