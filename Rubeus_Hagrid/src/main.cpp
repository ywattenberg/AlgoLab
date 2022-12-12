#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::tuple<long, long, long> RES; //gold, time, # of vertex
typedef std::vector<std::vector<std::pair<int, int>>> ADJ;

RES rec_dfs(const ADJ& addj_list, const VI& g, int vertex, int l){
  std::vector<RES> sub_res;
  
  for(std::pair<int, int> p: addj_list[vertex]){
    sub_res.push_back(rec_dfs(addj_list, g, p.first, p.second));
  }
  std::sort(sub_res.begin(), sub_res.end(), [](RES a, RES b){return std::get<1>(a) * std::get<2>(b) < std::get<1>(b) * std::get<2>(a);});
  
  int num_of_v = 1, t = 0;
  long gold = g[vertex]; 
  for (RES r: sub_res){
    gold += std::get<0>(r) - std::get<2>(r)*t;
    num_of_v += std::get<2>(r);
    t += std::get<1>(r);
  }
  return {gold - num_of_v*l, t + 2*l, num_of_v};
}

void solve(){
  int n;
  std::cin >> n;
  VI g(n+1);
  g[0] = 0;
  for(int i = 1; i < n+1; i++){
    int tmp;
    std::cin >> tmp;
    g[i] = tmp;
  }
  ADJ addj_list(n+1);
  for(int i = 0; i < n; i++){
    int u,v,l;
    std::cin >> u >> v >> l;
    addj_list[u].push_back({v,l});
  }
  
  RES  r = rec_dfs(addj_list, g, 0, 0);
  std::cout << std::get<0>(r) << '\n';
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
}
