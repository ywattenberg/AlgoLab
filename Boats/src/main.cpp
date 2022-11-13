#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
int calc_new_end(int curr_end, int pos, int length){
  int diff = pos - curr_end;
  return (diff > length) ? pos : (length - diff)+pos;
}

void solve(){
  int n;
  cin >> n;
  vector<pair<int, int>> vec(n);
  int l,p;
  for(int i = 0; i < n; i++){
    cin >> l >> p;
    vec[i] = make_pair(p , l);
  }
  sort(vec.begin(), vec.end());
  
  // for(auto i : vec){
  //   cout << i.first << ' ' << i.second << endl;
  // }
  int max = 1, pos=vec[0].first, pos_prev=-99999;
  for(int i = 1; i < n; i++){
    // cout << pos <<" " << pos_prev << ' ' << max << endl;
    if (vec[i].first >= pos){
      max++;
      pos_prev = pos;
      pos = calc_new_end(pos, vec[i].first, vec[i].second);
    } else if(vec[i].first > pos_prev){
      int new_end = calc_new_end(pos_prev, vec[i].first, vec[i].second);
      pos = min(new_end, pos);
    }
  }
  
  cout << max << '\n';
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
}