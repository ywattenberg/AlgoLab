#include<iostream>
#include<cmath>
#include<climits>
#include<vector>

using namespace std;

void solve(){
  vector<int> deck;
  int n, k, tmp, best_i=0, best_j=0, sum=0, curr_i = 0;
  int diff = INT_MAX;
  cin >> n;
  cin >> k;
  
  for(int i = 0; i < n; i++){
    cin >> tmp;
    deck.push_back(tmp);
    sum += tmp;
    if(abs(sum - k)<diff){
      diff = abs(sum-k);
      best_i = curr_i;
      best_j = i;
    }
    
    while(sum > k){
      sum -= deck[curr_i++];
      if(abs(sum - k)<diff){
        diff = abs(sum-k);
        best_i = curr_i;
        best_j = i;
      }
    }
    
  }
  
  cout << best_i << " " << best_j << endl;
  
  
  
  
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i<t; i++){
    solve();
  }
}

