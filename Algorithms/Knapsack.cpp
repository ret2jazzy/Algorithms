#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef pair<int,int> item;//First int holds the value and second holds the weight

vector<item>stuff;

map<int, map<int, int> >dp;

int knapsack(int now, int maxW)//A simple algo for memorized knapsack
{
	if(now == stuff.size())return 0;
	if(!dp.count(now) || !dp[now].count(maxW)){//Check if we already have solution in dp table
		if(stuff[now].second > maxW){
			dp[now][maxW] = knapsack(now+1, maxW);
		}else dp[now][maxW] = max( stuff[now].first+knapsack(now+1, maxW-stuff[now].second), knapsack(now+1, maxW));
	}
	return dp[now][maxW];//retuning the solutions
}

int main()
{
	ios::sync_with_stdio(false);
	cout << "Enter the number of items" << endl;
	int no, maxW;cin >> no;
	cout << "Enter each item value in format (value) (weight), for eg 2 3, The value of item is 2 and weight is 3" << endl;
	while(no--){
		int a,b;
		cin >> a >> b;
		stuff.push_back(make_pair(a,b));
	}
	cout << "Enter the max weight we can carry" << endl;
	int maxW;cin >> maxW;
	cout << knapsack(0, maxW) << endl;;
}