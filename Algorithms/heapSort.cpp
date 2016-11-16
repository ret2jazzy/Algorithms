#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//This wil sort the heap in ascending order, because we are making a max-heap, from which the top element will be the largest and then will move to last

void Maxheapify(vector<int>&heap, int index, int size)//Heapify takes a pre-condition that the subTrees of the index-node are already max-heapified
{
	int biggest = index;
	int left = 2*index +1;//Left element
	int right = 2*index +2;//Right element
	if(left < size && heap[left] > heap[biggest]){//Checking which child node is bigger
		biggest = left;
	}
	if(right < size && heap[right] > heap[biggest]){//Checking which child node is bigger
		biggest = right;
	}
	if(biggest > index){//checking if it has been changed, then swapping them and heapifying the rest
		swap(heap[biggest], heap[index]);
		Maxheapify(heap, biggest, size);
	}

}

void heapSort(vector<int>&array)
{
	for(int i = (array.size()/2)-1;i >= 0; --i){//As indexes start from 0, all elements after (size/2)-1 will be nodes 
		Maxheapify(array, i, array.size());
	}
	for(int i = array.size()-1; i >= 0;--i){//Swapping the largest element with the end element, then running heapify on the array again leaving the last element
		swap(array[0], array[i]);
		Maxheapify(array, 0, i);//running heapify on the rest of array leaving the swapped element, turning all array in ascending order
	}

}

int main()
{
	int p;cin >> p;
	vector<int>ans;
	while(p--){
		int m;cin >> m;
		ans.push_back(m);
	}
	heapSort(ans);
	cout << "sorted" << endl;
	for(auto m : ans){
		cout << m << endl;
	}
}