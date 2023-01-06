
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/pending/disjoint_sets.hpp>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<int, K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb,Fb>;
using Delaunay = CGAL::Delaunay_triangulation_2<K,Tds>;
using Edge_iterator = Delaunay::Edge_iterator;
using P = K::Point_2;
using VOP = std::vector<P>;

using weighted_graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, K::FT>>;
using weight_map = boost::property_map<weighted_graph, boost::edge_weight_t>::type;
using edge_desc = boost::graph_traits<weighted_graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<weighted_graph>::vertex_descriptor;

using VOFI = std::vector<std::pair<K::FT, int>> ;
using Edge = std::tuple<int, int, K::FT>;
using EdgeV = std::vector<std::tuple<int, int, K::FT>>;

int calc_k(EdgeV& t, VOFI& bone_tree_dist, int n, long d){
  int n_components = n;
  boost::disjoint_sets_with_storage<> uf(n);
  for(auto e = t.begin(); e != t.end(); e++){
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    if(c1 != c2 && std::get<2>(*e) <= d){
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  std::vector<int> bones_per_tree(n,0);
  for(auto di: bone_tree_dist){
    if(di.first <= d)  bones_per_tree[uf.find_set(di.second)]++;
  }
  
  return *std::max_element(bones_per_tree.begin(), bones_per_tree.end());
}

void solve(){
  int n, m, k;
  long s;
  std::cin >> n >> m >> s >> k;
  
  std::vector<std::pair<P, int>> trees(n);
  for(int i = 0; i < n; i++){
    int x,y;
    std::cin >> x >> y;
    trees[i] = {P(x,y), i};
  }
  
  Delaunay t;
  t.insert(trees.begin(), trees.end());
  VOFI bone_tree_dist(m);
  
  for(int i = 0; i < m; i++){
    int x,y;
    std::cin >> x >> y;
    P bone(x,y);
    auto tree = t.nearest_vertex(bone);
    bone_tree_dist[i] = {4*CGAL::squared_distance(tree->point(), bone), tree->info()};
  }
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  
  std::vector<K::FT> imp_dists;
  imp_dists.reserve(m+3*n);
  for(Edge e: edges){
    imp_dists.push_back(std::get<2>(e));
  }
  for(auto di: bone_tree_dist){
    imp_dists.push_back(di.first);
  }
  std::sort(imp_dists.begin(), imp_dists.end());
  
  int b = 0, e = (int)imp_dists.size();
  while(b < e){
    int mid = b + (e-b)/2;
    if(calc_k(edges, bone_tree_dist, n, imp_dists[mid]) < k)b = mid+1;
    else e = mid;
  }
  std::cout << calc_k(edges, bone_tree_dist, n, s) << " " << (long) imp_dists[b] << '\n'; 
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
  return 0;
}