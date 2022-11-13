#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<pair<long, long>> LPV;
typedef vector<long> LV;

typedef vector<pair<long, pair<long, int>>> RESV;

bool is_possible(const long gulp_dist, const RESV& s1, long rtime){
  pair<long, pair<long, int>> tmp = {rtime, {0, 0}};
  auto lower = lower_bound(s1.begin(), s1.end(), tmp);
  auto upper = upper_bound(s1.begin(), s1.end(), tmp);
  return false;
}

void calc_dists(const LPV& v, RESV& res){
  for(int i = 0; i < 1 << v.size(); i++){
    pair<long, pair<long, int>> tmp_pair = {0, {0,0}};
    for(int j = 0; j < v.size(); ++j){
      if (i & 1 << j){
        tmp_pair.first += v[j].second;
        tmp_pair.second.first += v[j].first;
        tmp_pair.second.second++;
      }
    }
    res.push_back(tmp_pair);
  }
  return;
}

void solve(){
  int n, m;
  long d, t;
  cin >> n >> m >> d >> t;
  LPV s0, s1;
  long g,h;
  for(int i = 0; i < n; i++){
    cin >> g >> h;
    if(i % 2){
      s0.push_back({g, h});
    }else{
      s1.push_back({g,h});
    }
  }
  
  LV gulp_dists(m);
  for(int i = 0; i < m; i++){
    cin >> g;
    gulp_dists[i] = g;
  }
  
  RESV r0, r1;
  calc_dists(s0, r0);
  calc_dists(s1, r1);
  
  sort(r1.begin(), r1.end());
  for(int i = 0; i < r0.size(); i++){
    long rtime = t - r0[i].first;
    
    auto curr_comp = [&s1, rtime](long a, long b) {return is_possible(b, s1, rtime);};
    auto best_gulp = lower_bound(gulp_dists.begin(), gulp_dists.end(), rtime, curr_comp);
  }
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