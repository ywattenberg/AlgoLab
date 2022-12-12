#include<iostream>
#include<vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

typedef std::vector<int> VI;
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


void solve(){
  int n,m,s;
  std::cin >> n >> m >> s;
  
  graph G(n+s+m+2);
  const int S = n+s+m;
  const int T = S+1;
  edge_adder adder(G);
  
  for(int i = 0; i < s; i++){
    int tmp;
    std::cin >> tmp;
    adder.add_edge(S, i, tmp, 0);
  }
  for(int i = 0; i < m; i++){
    int tmp;
    std::cin >> tmp;
    adder.add_edge(tmp-1, s+i, 1,0);
  }
  
  for(int i = 0; i < n; i++){
    adder.add_edge(s+m+i, T, 1,0);
    for(int j = 0; j < m; j++){
      int tmp;
      std::cin >> tmp;
      adder.add_edge(s+j, s+m+i, 1, 100-tmp);
    }
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, S, T);
  int cost2 = boost::find_flow_cost(G);
  int s_flow = 0;
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(S,G), G); e != eend; ++e) {
      s_flow += c_map[*e] - rc_map[*e];     
    }
  
  std::cout << s_flow << " " << 100*s_flow - cost2<< '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
}