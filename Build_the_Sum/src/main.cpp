#include<iostream>

using namespace std;

int main(){
  int t;
  cin >> t;
  
  for(int i=0; i < t; ++i){
    int n;
    cin >> n;
    int sum = 0;
    int tmp;
    for(int j=0; j < n; ++j){
      cin >> tmp;
      sum += tmp;
    }
    cout << sum << endl;
  }
  
}