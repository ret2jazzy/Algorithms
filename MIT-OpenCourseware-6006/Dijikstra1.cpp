#include <iostream>
#include <map>
#include <list>
//This is my implementation of dijikstra, It uses the same greedy concept, but i haven't implemented a heap type structure for min extraction
//I just iterate through all known nodes for the min, So it takes O(N) time for min
//Therefore the total time for algo is O(N2)
using namespace std;

struct Node{//I used a Node just to complicate stuff for myself
	int val;
	Node(int _val):val(_val){}
};

class Graph{//The main graph class
private:
	map<Node*, list<Node*> >adjList;//The adjacency List of the graph
	map<Node*, map<Node*, int> >disList;//The hash table to keep track of distances between nodes
public:
	void addNode(Node *a, Node *b, int dis){//Then function to add nodes
		adjList[a].push_back(b);
		adjList[b].push_back(a);
		disList[a][b] = dis;
		disList[b][a] = dis;
	}
	Node* minVertex(map<Node*, bool>visited, map<Node*, int>ans){//It gives out the min-distanced vertex from source(from given list)
		Node *minv = NULL;
		int min = -1;
		for(auto i = ans.begin(); i != ans.end(); ++i){
			if(!visited[i->first]){//Check if we have already visited it(or you can say like it is already min distanced)
				if(min < 0){//Checks if min == -1, then just initilizes it with minimum value
					min = i->second;
					minv = i->first;
				}else if(i->second < min){//else it sees if its less than the minimum known value
						min = i->second;
						minv = i->first;
					}
				}

			}
			return minv;//returns the node
		}
	map<Node*, int> shortestFrom(Node *a){//The main function to calculate shortest nodes from source
		map<Node*, int>ans;//Hash table to keep track of distances of all nodes from source
		map<Node*, bool>visited;//hash table to keep track of visited nodes
		ans[a] = 0;//Distance of source node
		while(visited.size() < adjList.size()){//While we visit all nodes
			Node *min = minVertex(visited, ans);//Gets the minimum node which hasn't been visited
			visited[min] = true;//Marking it visited
			for(auto i = adjList[min].begin(); i != adjList[min].end(); ++i){//Looking at all adjacent vertices, and "Relaxing" them
				if(!ans.count(*i) || ans[*i] > ans[min]+disList[min][*i]){//If it not already in list or the distance from this node is less than the earlier distance
					ans[*i] = ans[min] + disList[min][*i];//Changing it
				}
			}
		}
		return ans;
	}

};

int main()
{
	Graph lol;
	Node *p = new Node(8);//Making random nodes
	Node *q = new Node(9);
	Node *s = new Node(5);
	Node *f = new Node(1);
	lol.addNode(p,q,1);//adding them
	lol.addNode(q,s,4);
	lol.addNode(p,s,6);
    map<Node*, int>ans = lol.shortestFrom(p);//getting shortest path from p
    cout << ans[s] << endl;//outputting shortest path from p to s

}