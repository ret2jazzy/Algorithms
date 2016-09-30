/*This just a simpe bubble-sort of array(Vector is better i know) made just for fun*/


#include <iostream>
#include <algorithm>

using namespace std;

void sortar(int arr[], int size)
{
    int swapped = 1;
    while(swapped){
        swapped = 0;
        for(int i  = 0; i < size -1; ++i){
            if(arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
                swapped = 1;
            }
        }
        
    }
}

int main()
{
    cout << "Size of array " << endl;
    int s;cin >> s;
    int arraya[s];
    for(int i = 0; i < s; ++i){
        int x;
        cin >> x;
        arraya[i] = x;
    }
    sortar(arraya, s);
    cout << endl;
    for(int i = 0; i < s; ++i){
        cout << arraya[i] << endl;
    }
}
