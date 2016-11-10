#include <iostream>
#include <vector>

using namespace std;
//This will sort array in descending order
void merge(vector<int>&array, int start, int mid, int end)//The sort subroutine
{
	vector<int>temp1;//the temp vectors to store already sorted stuff
	vector<int>temp2;
	for(int i = start; i <= mid; ++i){//copying the stuff into already sorted stuff
		temp1.push_back(array[i]);
	}
	for(int i = mid+1;i <= end;++i){
		temp2.push_back(array[i]);
	}
	int ar1 = 0;//defining the indexes of vectors on which we are going to do the finger-merge-sort
	int ar2 = 0;
	for(int i = start; i <= end; ++i){
		if(ar1 == temp1.size()){//checking if all the elements of a single vector has been used
			for(int m = i; m <=end; ++m){
				array[m] = temp2[ar2];
				++ar2;
			}
			break;
		}
		if(ar2 == temp2.size()){//checking if all the elements of a single vector has been used
			for(int m = i; m <=end; ++m){
				array[m] = temp1[ar1];
				++ar1;
			}
			break;
		}
		if(temp1[ar1] >= temp2[ar2]){//checking which element is bigger and then increasing their indexes
			array[i] = temp1[ar1];
			++ar1;
		}else{
			array[i] = temp2[ar2];
			++ar2;
		}
	}

}

void mergeSort(vector<int>&array, int start, int end)
{
	if(start < end){//The if is to check if we have atleast two elements which we can sort, or it will be a base case of only one element and its already sorted
		int mid = (start+end)/2;
		mergeSort(array, start, mid);//sorting midway
		mergeSort(array, mid+1, end);
		merge(array, start, mid, end);//merging it
	}
}

int main()
{
	int n; cin >> n;
	vector<int>tosort;
	while(n--){
		int p;cin >> p;
		tosort.push_back(p);
	}
	mergeSort(tosort, 0, tosort.size()-1);
	cout << "sorted" << endl;
	for(auto m : tosort){
		cout << m << endl;
	}
}
