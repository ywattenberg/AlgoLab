#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>


typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;
  public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity) {
      auto c_map = boost::get(boost::edge_capacity, G);
      auto r_map = boost::get(boost::edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = capacity;
      c_map[rev_e] = 0; // reverse edge has no capacity!
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
};


void solve(const std::vector<int>& vec){
  int h,w;
  std::cin >> h >> w;
  std::string s;
  std::cin >> s;
  std::vector<int> needed(26, 0);
  for(char c : s){
    needed[(int)c - 65]++;
  }
  std::vector<std::string> front(h);
  for(int i = 0; i < h; i++){
    std::string s;
    std::cin >> s;
    front[i] = s;
  }
  std::vector<int> num(351, 0);
  for(int i = 0; i < h; i++){
    std::string s;
    std::cin >> s;
    for(int j = 0; j < w; j++){
      int min = std::min((int)front[i][w-1-j] -65, (int)s[j] - 65);
      int max = std::max((int)front[i][w-1-j] -65, (int)s[j] - 65);
      num[vec[min]+max-min]++;
    }
  }


  graph G(351 + 26 + 2);
  const int S = 351 + 26;
  const int T = 351 + 26 + 1;
  edge_adder adder(G);
  for(int i = 0; i < 26; i++){
    adder.add_edge(351+i, T, needed[i]);
    for(int j = i; j < 26; j++){
      adder.add_edge(S, vec[i]+j-i, num[vec[i]+j-i]);
      adder.add_edge(vec[i]+j-i, i+351, num[vec[i]+j-i]);
      if(i != j){
        adder.add_edge(vec[i]+j-i, j+351, num[vec[i]+j-i]);
      }
    }
  }
  long flow = boost::push_relabel_max_flow(G, S, T);
  if(flow == s.size()){
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  std::vector<int> vec(26,0);
  for(int i = 0; i < 25; i++){
    vec[i+1] = vec[i] + 26 - i; 
  }
  // for(int i : vec){
  //   std::cout << i << ' ';
  // }
  while(t--)solve(vec);
  return 0;
}