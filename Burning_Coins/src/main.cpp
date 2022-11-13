#include<iostream>
#include<vector>
#include<map>

using namespace std;

typedef vector<int> IV;

void solve(){
  int n, tmp;
  cin >> n;
  IV v;
  for(int i = 0; i < n; i++){
    cin >> tmp;
    v.push_back(tmp);
  }
  vector<IV> matrix;

  //BC
  bool turn = ((n % 2) == 0);
  if(!turn){
    matrix.push_back(v);
  } else {
    IV zeros(n, 0);
    matrix.push_back(zeros);
  }
  
  for(int length = 1; length < n; length++){
    IV row;
    for(int i = 0; i < n - length; i++){
      if(turn){
        int left = matrix[length-1][i] +v[i + length];
        int right = matrix[length-1][i+1] + v[i];
        //cout << " 1 | l:"  << length << " i:" << i << " " << left << " " << right << endl;
        row.push_back(left > right ? left:right);
      }else {
        int left = matrix[length-1][i];
        int right = matrix[length-1][i+1];
        //cout << " 2 | l:"  << length << " i:" << i << " " << left << " " << right << endl;
        row.push_back(left < right ? left:right);

      }
    }
    matrix.push_back(row);
    turn = !turn; 
  }
  cout << matrix.back().back() << endl;
}

int main(){
  int t; 
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  return 0;
}