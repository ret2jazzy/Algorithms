#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <map>

using namespace std;

typedef pair<int, int>pii;//The priority que defination

class Graph{//The main graph class
private:
	map<int, vector<pii> >adjList;
public:
	void addNode(int a, int b, int w){//A function to add nodes
		adjList[a].push_back(make_pair(b,w));
		adjList[b].push_back(make_pair(a,w));
	}
	map<int,int> primS(int s){//The main prims function
		map<int,int>parent;//The hash table for parent nodes
		parent[s] = -1;//Parent of source is -1
		map<int,bool>visited;//Hash table to keep track of which nodes are added in the MST
		map<int,int>dists;//Hash table to keep track of lowest distance of nodes from their adjacent ones(or maybe more)
		dists[s] = 0;
		priority_queue<pii, vector<pii>, greater<pii> >que;//A min priority que implementation
		que.push(make_pair(0,s));//pushing the source node
		while(!que.empty()){//It'll be empty when all nodes get processed atleast once
			int nod = que.top().second;//picking the node with lowest distance
			que.pop();
			if(visited[nod])continue;//Just to make sure the node hasn't been already visited
			visited[nod] = true;
			for(auto i = adjList[nod].begin(); i != adjList[nod].end(); ++i){//looking at all neighbouring nodes
				int node = i->first;
				int weight = i->second;
				if(!visited[node] && (!dists.count(node) || weight < dists[node])){//If the distance is less, or no distance is recorded
					dists[node] = weight;
					parent[node] = nod;
					que.push(make_pair(weight,node));
				}
			}
		}
		return parent;
	}
};

int main()
{
	Graph lol;
	lol.addNode(1,2,5);
	lol.addNode(2,3,7);
	lol.addNode(1,3,6);
	map<int,int>ans = lol.primS(1);
	cout << ans[3] << endl;
}