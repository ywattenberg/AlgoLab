///3
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
                              boost::no_property, boost::property<boost::edge_weight_t, int>> graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void solve(){
  int n, m, k, x, y;
  std::cin >> n >> m >> k >> x >> y;
  graph G((k+1) * n);
  
  for(int i = 0; i < m; i++){
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    for(int j = 0; j <= k; j++){
      boost::add_edge(a+(j*n), b+(j*n), c, G);
      if(d && j < k){
        boost::add_edge(a+(j*n), b+((j+1)*n), c, G);
        boost::add_edge(a+((j+1)*n), b+(j*n), c, G);
      }
    }
  }
  std::cout << dijkstra_dist(G, x, y+(n*k)) << '\n';
    
}



int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  
}