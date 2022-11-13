///
#include <iostream>
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

void solve(){
  int w,h;
  std::cin >> w >> h;
  graph G(w*h+2);
  edge_adder adder(G);
  const int S = w*h, T=w*h+1;
  int num_a = 0, num_b=0;
  for(int i = 0; i < h; i++){
    bool layer = i%2;
    std::string s;
    std::cin >> s;
    for(int j = 0; j < w; j++){
      if(s[j] == '.'){
        if(!layer){
          num_a++;
          adder.add_edge(S, i*w + j, 1);
          if(i > 0)adder.add_edge(i*w + j, (i-1)*w + j, 1);
          if(i < h-1)adder.add_edge(i*w + j, (i+1)*w + j, 1);
          if(j > 0)adder.add_edge(i*w + j, i*w + j-1, 1);
          if(j < w-1)adder.add_edge(i*w + j, i*w + j+1, 1);
        } else{
          num_b++;
          adder.add_edge(i*w + j, T, 1);
        }
      }
      layer = !layer;
    }
  }
  if(num_a != num_b){
    std::cout << "no\n";
    return;
  }
  long flow = boost::push_relabel_max_flow(G, S, T);
  if(flow == num_a){
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
  while(t--)solve();
  return 0;
}