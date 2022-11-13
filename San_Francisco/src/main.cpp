#include<iostream>
#include<vector>

using namespace std;
typedef vector<long> IV;

void solve(){
  long n, m, k;
  long x;
  cin >> n >> m >> x >> k;
  vector<vector<pair<long, long>>> edge_list(n);
  long u,v,p;
  for(int i = 0; i < m; i++){
    cin >> u >> v >> p;
    edge_list[u].push_back({v, p});
  }

  vector<IV> res(k+1);
  IV tmp(n,0);
  res[0] = tmp;
  for(int i = 1; i < k+1; i++){
    for(int j = 0; j < n; j++){
      long max = 0;
      if(edge_list[j].empty()){
        max = res[i][0];
      }
      for(auto pos : edge_list[j]){
        max = std::max(pos.second+res[i-1][pos.first], max);
      }
      res[i].push_back(max);
    }
    if(res[i][0] >= x){
      cout << i << '\n';
      return;
    }
  }
  cout << "Impossible\n";
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  return 0;
}