#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <map>


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
    c_map[rev_e] = 1; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void solve(){
  int n,m,s;
  std::cin >> n >> m >> s;
  
  graph G(n+1);
  edge_adder adder(G);
  std::vector<int> stores(n);
  std::vector<int> num_s(n, 0);
  for(int i = 0; i < s; i++){
    int l;
    std::cin >> l;
    stores[i] = l;
    num_s[i]++;
  }
  for(int i = 0; i < s; i++){
    adder.add_edge(stores[i], n, num_s[i]);
  }
  for(int i = 0; i < m; i++){
    int a,b;
    std::cin >> a >> b;
    adder.add_edge(a, b, 1);
  }
  long flow = boost::push_relabel_max_flow(G, 0, n);
  if(flow == s){
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