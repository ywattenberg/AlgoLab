///1
#include<iostream>
#include<vector>
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
  int m,n,k,c;
  std::cin >> m >> n >> k >> c;
  graph G(m*n*2+2);
  edge_adder adder(G);
  const int S = m*n*2;
  const int T = m*n*2+1;
  const int offset = m*n;
  auto vert = [m,n] (int x, int y){return y*m + x;};
  
  for(int y = 0; y < n; y++){
    for(int x = 0; x < m; x++){
      if(y == 0 || y == n-1){
        adder.add_edge(vert(x,y), T, 1);
      }
      if(x == 0 || x == m-1){
        adder.add_edge(vert(x,y), T, 1);
      }
      if(x < m-1){
        adder.add_edge(vert(x,y), vert(x+1,y)+ offset, 1);
        adder.add_edge(vert(x+1,y), vert(x,y)+ offset, 1);
      }
      if(y < n-1){
        adder.add_edge(vert(x,y), vert(x,y+1)+ offset, 1);
        adder.add_edge(vert(x,y), vert(x,y+1)+ offset, 1);
      }
      adder.add_edge(vert(x,y)+offset, vert(x,y), c);
    }
  }

  for(int i = 0; i < k; i++){
    int x,y;
    std::cin >> x >> y;
    adder.add_edge(S, vert(x,y)+offset,1);
  }
  long flow = boost::push_relabel_max_flow(G, S, T);
  std::cout << flow << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
  
}