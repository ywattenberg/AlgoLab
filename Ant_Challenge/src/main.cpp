///3
#include <iostream>
#include <vector>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS>
                                                                graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
typedef std::map<edge_desc, boost::edge_weight_t>               edge_weight_map;                 
typedef boost::associative_property_map<edge_weight_map>        weight_map; 

int dijkstra_path(const graph& G, weight_map w_map, int s, int t) //
{
  int              n = boost::num_vertices(G);
  std::vector<vertex_desc> pred_map(n);
  std::vector<int> dist_map(n);
  auto id = get(boost::vertex_index, G);
  auto dm = boost::make_iterator_property_map(dist_map.begin(), id);
  auto pm = boost::make_iterator_property_map(pred_map.begin(), id);

  boost::dijkstra_shortest_paths( //
      G, s,                       //
      boost::distance_map(dm)     //
          .predecessor_map(pm)    //
          .weight_map(w_map));
    
  return dist_map[t];
}

void kruskal(const graph& G, weight_map w_map,
                   std::vector<edge_desc>& edge_vec) //
{
  boost::kruskal_minimum_spanning_tree(
      G, std::back_inserter(edge_vec),                     
      boost::weight_map(w_map));
}


void solve(){
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;
  graph G(n);
  std::vector<edge_weight_map> map_vec(s);
  edge_desc e_tmp;
  edge_weight_map res_map;
  int u, v, w;
  for(int i = 0; i < e; i++){
    std::cin >> u >> v;
    e_tmp = boost::add_edge(u, v, G).first;
    res_map.insert(std::make_pair(e_tmp, boost::edge_weight_t(10000000)));
    for(int j = 0; j < s; j++){
      std::cin >> w;
      map_vec[j].insert(std::make_pair(e_tmp, boost::edge_weight_t(w)));
    }
  }
  
  std::vector<int> hive;
  int h;
  for(int i = 0; i < s; i++){
    std::cin >> h;
    hive.push_back(h);
  }

  weight_map w_map;
  std::vector<std::vector<edge_desc>> networks(s);
  
  for(int i = 0; i < s; i++){
    w_map = weight_map(map_vec[i]);
    kruskal(G, w_map, networks[i]);
    for(int j = 0; j < n-1; j++){
      edge_desc tmp_e = networks[i][j];
      auto it_new = res_map.find(tmp_e);
      auto it_old = map_vec[i].find(tmp_e);
      if((*it_new).second > (*it_old).second){
        it_new -> second = (*it_old).second;
      }
    }
  }
  std::cout << dijkstra_path(G, weight_map(res_map), a, b) << std::endl;
  
  
  
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