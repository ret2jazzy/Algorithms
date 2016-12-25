#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

//This graph is made using the concept of adjacency lists for graphs, and i made a Struct of node just to make 
//things complex for myself so as to learn more

struct Node{//I made a struct just to complexicate things for myself
	int val;
	Node(int p): val(p){}
};

class Graph{//The main graph class
	private:
		map<Node*, list<Node*> >adjList;//A hash table to map nodes to it's adjancent nodes list
		map<Node*, Node*>parentP;//a hash table of parent nodes
	public:
		void addEdge(Node *a, Node *b){//Function to add Node which just adds multidirectional nodes
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
		void BFS(Node *p){//The main BFS which traverses all nodes
			map<Node*, bool>visited;//The hash table to map the visited nodes, initially all bools are false
			list<Node*>toBeVisited;//The queue to keep track of nodes which we have to visit
			visited[p] = true;//The Node we start is visited
			toBeVisited.push_back(p);//Pushing it back to queue to get its neighbours
			while(!toBeVisited.empty()){//While there are more nodes to explore
				Node *m = toBeVisited.front();//The node at first place
				cout << m->val << endl;//Outputting the value
				toBeVisited.pop_front();//removing the first one
				for(auto i = adjList[m].begin(); i != adjList[m].end(); ++i){
					if(!visited[*i]){//Dereferencing i as list holds pointers
						toBeVisited.push_back(*i);
						visited[*i] = true;
						parentP[*i] = m;
					}
				}
			}
		}
		int coutParent(Node* b){//function to return the parent value, only run after a bfs
			if(parentP.count(b))//only if parent exists
			 return parentP[b]->val;
			else return -1;//else returns -1
		}
};

int main(){
	Graph lol;
	Node *m = new Node(5);//Making radnom Nodes
	Node *p = new Node(8);
	Node *k = new Node(2);
	lol.addEdge(m, p);//Adding random Nodes
	lol.addEdge(p, k);
	lol.addEdge(m, new Node(11));
	lol.addEdge(p, new Node(6));

	lol.BFS(p);//Running the BFS taking node p as base
	cout << "parent of m is " << lol.coutParent(m) << endl;//Outputting parent of m, which is p
}