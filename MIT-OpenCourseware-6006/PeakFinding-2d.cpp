#include <iostream>
#include <vector>

using namespace std;

int twD(vector<vector<int> >lol, int start, int end)
{
	int mid = (start+end)/2;
	int max = lol[0][mid];
	int maxindex = 0;
	for(int i = 1; i < lol.size();++i){
		if(lol[i][mid] > max){
			max = lol[i][mid];
			maxindex = i;
		}
	}
	if(mid-1 >= start && lol[maxindex][mid-1] > lol[maxindex][mid]){
		return twD(lol, start, mid-1);
	}else if(mid+1 <= end && lol[maxindex][mid+1] > lol[maxindex][mid]){
		return twD(lol, mid+1, end);
	}else return lol[maxindex][mid];
}

int main()
{
	int x,y;
	cin >> x >> y;
	vector<vector<int> >ans;
	for(int i = 0; i < x; ++i){
		vector<int>temp;
		for(int a = 0; a < y; ++a){
			int p;cin >>p;
			temp.push_back(p);
		}
		ans.push_back(temp);
	}
	cout << twD(ans, 0, y-1) << endl;
}
