///1
#include <iostream>
#include <vector>
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

void solve(){
  int n,m;
  std::cin >> n >> m;
  
  graph G(n+m+2);
  edge_adder adder(G);
  std::vector<int> have(n,0);
  int non_zero = 0;
  for(int i = 0; i < m; i++){
    int a,b,c;
    std::cin >> a >> b >> c;
    if(c==0){
      non_zero++;
      adder.add_edge(n+m, i, 1);
      adder.add_edge(i, m+a, 1);
      adder.add_edge(i, m+b, 1);
    }else if(c==1){
      have[a]++;
    }else{
      have[b]++;
    }
  }
  int res = 0;
  bool ned = false;
  for(int i = 0; i < n; i++){
    int a;
    std::cin >> a;
    int diff = a - have[i];
    res += diff;
    if(diff < 0)ned = true;
    else if (diff > 0) adder.add_edge(i+m, n+m+1, diff);
  }
  if(ned || non_zero != res){
    std::cout << "no\n";
    return;
  }
  long flow = boost::push_relabel_max_flow(G, n+m, n+m+1);
  if(flow == res){
    std::cout << "yes\n";
  } else {
    std::cout << "no\n";
  }
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t){
    solve();
    t--;
  }
  
  return 0;
}