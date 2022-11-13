///3
#include<iostream>
#include<vector>
#include<cmath>
#include <bits/stdc++.h>


using namespace std;
typedef vector<int> VI;

void add_optimal(VI *optimal, float tmp_dist, int base_dist){
  if(tmp_dist != (int)tmp_dist){
    (*optimal).push_back(floor(tmp_dist) + base_dist);
    (*optimal).push_back(floor(tmp_dist)+1 + base_dist);
  } else{
    (*optimal).push_back(tmp_dist + base_dist);
  }
}

void solve(){
  int n, tmp;
  cin >> n;
  VI v;
  for(int i = 0; i < n; i++){
    cin >> tmp;
    v.push_back(tmp);
  }
  sort(v.begin(), v.end());
  VI optimal;
  int curr_max_num;
  int curr_min_dist;
  int first_el = 0;

  while(first_el+1 < n && abs(v[0] - v[first_el+1]) <= 200){
    first_el++;
  }
  curr_max_num = first_el + 1;
  float tmp_dist = abs(v[0] - v[first_el])/2.0;
  add_optimal(&optimal, tmp_dist, v[0]);
  curr_min_dist = ceil(tmp_dist);

  for(int last = 1; last < n && first_el+1 < n; last++){
    while(first_el+1 < n && abs(v[last] - v[first_el+1]) <= 200){
      first_el++;
    }
    
    float tmp_dist = abs(v[last] - v[first_el])/2.0;
    int tmp_num = first_el - last + 1;
    if(curr_max_num > tmp_num){
      continue;
    } else if(curr_max_num < tmp_num){
      curr_max_num = tmp_num;
      optimal.clear();
      add_optimal(&optimal, tmp_dist, v[last]);
      curr_min_dist = ceil(tmp_dist);
      
    } else if(curr_min_dist < ceil(tmp_dist)){
      continue;
    } else if(curr_min_dist > ceil(tmp_dist)){
      curr_min_dist = ceil(tmp_dist);
      optimal.clear();
      add_optimal(&optimal, tmp_dist, v[last]);
    } else{
      add_optimal(&optimal, tmp_dist, v[last]);
    }
  }
  cout << curr_max_num << ' ' << curr_min_dist << endl;
  for(auto it = optimal.cbegin(); it != optimal.cend(); it++){
    cout << *it << ' ';
  }
  cout << endl;
}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  return 0;  
}