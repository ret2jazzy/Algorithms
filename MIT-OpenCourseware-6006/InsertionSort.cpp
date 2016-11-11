#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int>&ab)
{
	for(int i = 1; i < ab.size();++i){//Iterating through all elements as keys
		int key = ab[i];
		int ind = i;
		while(ind > 0 && key < ab[ind-1]){//checking if this is the right index to insert the key
			ab[ind] = ab[ind-1];//else just copying the next element in it's place(kind of movinf array)
			--ind;
		}
		ab[ind] = key;//inserting the key
	}
}

int main()
{
	int p;cin >> p;
	vector<int>ans;
	for(int i = 0; i < p; ++i){
		int f;cin >> f;
		ans.push_back(f);
	}
	insertSort(ans);
	cout << "sorted" << endl;
	for(auto m : ans){
		cout << m << endl;
	}
	return 0;
}
