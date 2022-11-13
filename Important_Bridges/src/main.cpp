///1
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;

void solve(){
  int n, m;
  std::cin >> n >> m;
  graph G(n);
  for(int i = 0; i < m; ++i){
    int a, b;
    std::cin >> a >> b;
    boost::add_edge(a, b, G);
  }
  
  std::vector<int> dt(n);
  std::vector<int> lp(n);
  std::vector<std::pair<int, int>> res;
  
  auto id = get(boost::vertex_index, G);
  auto dm = boost::make_iterator_property_map(dt.begin(), id);
  auto pm = boost::make_iterator_property_map(lp.begin(), id);
  
  boost::biconnected_components(G, boost::dummy_property_map(), 
                        boost::discover_time_map(dm).lowpoint_map(pm));
  
  for(auto it = boost::edges(G); it.first != it.second; it.first++){
    int s = boost::source(*(it.first), G);
    int t = boost::target(*(it.first), G);

    
    if(lp[t] > dt[s] || lp[s] > dt[t]){
      res.push_back(((s < t)?std::make_pair(s,t) : std::make_pair(t,s)));
    }
  }
  std::sort(res.begin(), res.end());
  std::cout << res.size() << '\n';
  for(auto p : res){
    std::cout  << p.first << ' ' << p.second << '\n';
  }
}


int main(){
  int t;
  std::cin >> t;
  for(int i = 0; i < t; ++i){
    solve();
  }
}

