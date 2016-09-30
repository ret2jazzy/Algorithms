/* This program can be used to encrypt or decrypt strings using caesar's encryption*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

bool isPerfectSquare(int p)
{
    if(p <= 0){
        return false;
    }
    int s = sqrt(p);
    return (s*s == p);
}

int main()
{
  string s;
  getline(cin, s);
  if(isPerfectSquare(s.size())){
      int q = sqrt(s.size());
      int f = 0;
      vector< vector<char> >lol;
      for(int i = 0; i < q; ++i){
        vector<char>temp;
          for(int y = 0; y < q; ++y){
              temp.push_back(s[f]);
              ++f;
          }
          lol.push_back(temp);
      }
      for(int i = 0; i < q; ++i){
          for(int t = 0; t < q; ++t){
              cout << lol[t][i];
          }
      }
      cout << endl;
      
      
  }else cout << "ERROR" << endl;
}
