#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>


typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int>
                              > weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;

std::vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n); //exterior property
  boost::dijkstra_shortest_paths(G, s, 
    boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
    boost::get(boost::vertex_index, G))));
    
  return dist_map;
}

void solve(){
  int n, m;
  std::cin >> n >> m;
  weighted_graph G(n);
  for(int i = 0; i < m; i++){
    int u, v, w;
    std::cin >> u >> v >> w;
    boost::add_edge(u,v,w,G);
  }
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  weight_map d = get(boost::edge_weight, G);

  int w_mst = 0;
  for(edge_desc e: mst){
    w_mst += d[e]; 
  }
  std::cout << w_mst << ' ';
  std::vector<int> dist_map = dijkstra_dist(G, 0);
  std::cout << *std::max_element(dist_map.cbegin(), dist_map.cend()) << '\n';
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  return 0;
}