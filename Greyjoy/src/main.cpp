
#include <iostream>
#include <vector>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> IV;
typedef tuple<int, int, int> IT;

bool compare_pair(const IT& a, const IT& b){
  return get<0>(a) < get<0>(b) 
      || (get<0>(a) == get<0>(b) && get<1>(a) < get<1>(b)) 
      || (get<0>(a) == get<0>(b) && get<1>(a) == get<1>(b) && get<2>(a) < get<2>(b));
}

void solve(){
  int n, k, w;
  cin >> n >> k >> w;
  
  IV c(n);
  for(int i = 0; i < n; i++){
    cin >> c[i];
  }
  
  vector<IV> waterways(n);
  int l, tmp;
  for(int i = 0; i < w; i++){
    cin >> l;
    for(int j = 0; j < l; j++){
      cin >> tmp;
      waterways[i].push_back(tmp);
    }
  }
  
  int max = 0;
  vector<IT> prev_sum;
  for(int i = 0; i < w; i++){
    auto begin = waterways[i].cbegin();
    auto end = waterways[i].cbegin()+1;
    int num_of_men = c[0];
    //prev_sum.push_back({num_of_men, 1, i});
    while(end != waterways[i].cend() && num_of_men < k){
      prev_sum.push_back(make_tuple(num_of_men, (int)(end - begin), i));
      num_of_men += c[*(end++)];
    }
    if(end == waterways[i].cend() && num_of_men < k){
      prev_sum.push_back(make_tuple(num_of_men, (int)(end - begin), i));
    }
    while(begin != waterways[i].cend()){
      if(num_of_men == k && (int)(end - begin) > max){
        max = (int)(end - begin);
      }
      num_of_men -= c[*(begin++)];
      while(end != waterways[i].cend() && num_of_men < k){
          num_of_men += c[*(end++)];
      }
    }
    if(num_of_men == k && (int)(end - begin) > max){
      max = (int)(end - begin);
    }
  }
  //cout << k << " k  " << endl;
  // for (auto i : prev_sum){
  //   cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
  // }
  
  sort(prev_sum.begin(), prev_sum.end(), compare_pair);
  
  auto begin = prev_sum.cbegin();
  auto rbegin = prev_sum.crbegin();
  while(begin != prev_sum.cend() && rbegin != prev_sum.crend()){
    //cout << get<0>(*begin) << " b " << get<1>(*begin) << " b " << get<2>(*begin) << endl;
    while(rbegin+1 != prev_sum.crend() 
        && get<0>(*rbegin) + get<0>(*begin) > k + c[0]){
      rbegin++;
    }
    //cout << get<0>(*rbegin) << " r " << get<1>(*rbegin) << " r " << get<2>(*rbegin)<< endl;
    if(get<0>(*rbegin) + get<0>(*begin) == k + c[0] 
        && get<1>(*rbegin) + get<1>(*begin) - 1 > max
        && get<2>(*rbegin) != get<2>(*begin)){
        max = get<1>(*rbegin) + get<1>(*begin) - 1;
    }
    if(!compare_pair(*begin, *rbegin)){
      ////cout << "break" << endl;
      break;
    }
    begin++;
  }
  
  cout << max << endl;
  
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