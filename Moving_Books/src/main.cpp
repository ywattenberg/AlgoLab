#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool comp_f(const int x, const int y){
  return x > y;
}

void solve() {
  int n,m;
  cin >> n >> m;
  
  vector<int> strength;
  
  for(int i = 0; i < n; i++) {
    int s; 
    cin >> s;
    strength.push_back(s);  
  }
  
  vector<int> weight;
  for(int i = 0; i < m; i++) {
    int w;
    cin >> w;
    weight.push_back(w);  
  }
  
  sort(strength.begin(), strength.end(), comp_f);
  sort(weight.begin(), weight.end(), comp_f);
  
  if(weight[0] > strength[0]) {
    cout << "impossible \n" ;
    return;
  }
  
  vector<int> w_cap;
  int idx = 0;
  
  for(int i = 0; i < m; i++) {
    while (idx < n && weight[i] <= strength[idx]) {
      idx++;
    }
    w_cap.push_back(idx-1);
  }
  
  int max_round = 0;
  vector<int> h_round;
  h_round.push_back(0);
  
  for(int i = 1; i < m; i++) {
    int h_friend = w_cap[i];
    auto curr_round = upper_bound(h_round.begin(), h_round.end(), h_friend, comp_f);
    if (curr_round == h_round.end()) {
        max_round++;
        h_round.push_back(0);
    } else {
      (*curr_round)++;
    }
  }
  
  int t = (max_round + 1) * 3 - 1;
  cout << t << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(NULL);
  int t;
  cin >> t;
  for(int i = 0; i < t; i++) {
    solve();
  }
  
  return 0;
}