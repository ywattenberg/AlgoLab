///1
#include<iostream>
#include<vector>

using namespace std;
typedef vector<vector<int>> VVI;

void solve(){
  int n;
    cin >> n;
    vector<vector<int>> matrix;
    int el;

    for(int j = 0; j < n; ++j){
      vector<int> row;
      for(int k = 0; k < n; ++k){
        cin >> el;
        el = el % 2;
        if(k == 0){
          row.push_back(el);
        } else {
          row.push_back((row.back()+el) % 2);
        }
      }
      matrix.push_back(row);
    }
    
    int even_quads = 0;
    for(int i = 0; i < n; i++){
      for(int j = i; j < n; j++){
        int even_pairs = 0;
        int sum = 0;
        for(int k = 0; k < n; k++){
          if (i == 0){
            sum = (sum + matrix[k][j]) % 2;
            if(sum == 0)
              even_pairs++;
          }
          else {
            sum = (sum + matrix[k][j] - matrix[k][i-1]) % 2;
            if(sum == 0){
              even_pairs++;
            }
          }
        }
        int num_even = ((even_pairs - 1)*even_pairs)/2;
        int odd_pairs = n - even_pairs;
        int num_odd = ((odd_pairs - 1)*odd_pairs)/2;
        even_quads += num_even + num_odd + even_pairs;
    }
  }
  cout << even_quads << endl; 
}

int main(){
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i){
    solve();
  }
}