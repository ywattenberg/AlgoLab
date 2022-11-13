#include<iostream>
#include<vector>

using namespace std;

int main(){
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i){
    int n;
    cin >> n;
    int sum = 0;
    int num_even = 0;
    int even_tmp = 0;
    int tmp;
    for(int j = 0; j < n; ++j){
      cin >> tmp;
      sum = (tmp + sum)%2;
      if(sum % 2 == 0)
        num_even++;
      if(tmp % 2 == 0)
        even_tmp++;
      }
      int even_pairs = ((num_even -1 )*num_even)/2;
      int num_odd = n - num_even;
      int odd_pairs = ((num_odd -1 )*num_odd)/2;
      cout << (even_pairs + odd_pairs + num_even) << endl;
  }
}
  