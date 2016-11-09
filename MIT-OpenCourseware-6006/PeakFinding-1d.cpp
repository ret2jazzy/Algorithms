#include <iostream>
#include <vector>

using namespace std;

int peak(vector<int>lol,int start, int end)
{
	int mid = (start+end)/2;
	if(mid+1 <= end && lol[mid+1] > lol[mid]){
		return peak(lol, mid+1, end);
	}else if(mid-1 >= start && lol[mid-1] > lol[mid]){
		return peak(lol, start, mid-1);
	}else return mid;
}

int main()
{
	int p;cin >> p;
	vector<int>ond;
	for(int i = 0;i < p; ++i){
		int c;cin >> c;
		ond.push_back(c);
	}
	cout << peak(ond, 0, ond.size()-1) << endl;
}
