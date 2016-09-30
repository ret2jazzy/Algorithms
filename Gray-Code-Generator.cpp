/*This program can be used to pgenerate gray code of varying bitlengths, you can input "4" and
it will produce all the possible gray code which is "4" bits in width*/

#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;


int convertGray(int x)
{
     return ((x>>1) ^ x);
}

void grayCout(int num, int x)
{
    string m = bitset<64>(num).to_string();
    for(int i = 64 - x; i < 64; ++i){
    	cout << m[i];
    }
    cout << endl;
}


int main()
{
    int n;
    cin >> n;
    for(int i=0; i < pow(2,n);++i)
    {
        int y = convertGray(i);
        grayCout(y, n);
    }
}
