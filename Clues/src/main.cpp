//1
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Index = std::size_t;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Index,K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb,Fb>;
using Delaunay = CGAL::Delaunay_triangulation_2<K,Tds>;
using Edge = std::tuple<Index,Index,K::FT>;
using EdgeV = std::vector<Edge>;
using P = K::Point_2;
using graph = boost::adjacency_list<boost::vecS, boost::vecS,
      boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
>;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
using edge_it = boost::graph_traits<graph>::edge_iterator;            // to iterate over all edges

void solve(){
  int n,m;
  long r;
  std::cin >> n >> m >> r;
  r *= r;
  
  std::vector<std::pair<P, int>> ant;
  ant.reserve(n);
  for(int i = 0; i < n; i++){
    int x,y; std::cin >> x >> y;
    ant.push_back({P(x,y), i});
  }
  
  std::vector<std::pair<P, P>> querries;
  querries.reserve(m);
  for(int i = 0; i < m; i++){
    int x,y,a,b;
    std::cin >> x >> y >> a >> b;
    querries.emplace_back(P(x,y),P(a,b));
  }
  
  Delaunay t;
  t.insert(ant.begin(), ant.end());
  
  graph G(n);
  
  for(auto v = t.finite_vertices_begin(); v !=  t.finite_vertices_end(); v++){
    int i = v->info();
    auto adj1 = t.incident_vertices(v);
    do{
      if(t.is_infinite(adj1))continue;
      int i1 = adj1->info();
      //if(i1 == i)continue;
      if(CGAL::squared_distance(v->point(),adj1->point()) <= r)boost::add_edge(i1, i, G);
      auto adj2 = t.incident_vertices(adj1);
      do{
        if(t.is_infinite(adj2))continue;
        int i2 = adj2->info();
        if(i2 == i)continue;
        if(CGAL::squared_distance(v->point(),adj2->point()) <= r)boost::add_edge(i2, i, G);
      }while(++adj2 != t.incident_vertices(adj1));
    }while(++adj1 != t.incident_vertices(v));
  }
  
  if(!boost::is_bipartite(G)){
    //std::cout << "not bipartid \n";
    for(auto p : querries){
      std::cout << 'n';
    }
    std::cout << '\n';
    return;
  }
  
  std::vector<int> comp(n);
  boost::connected_components(G,
    boost::make_iterator_property_map(comp.begin(), boost::get(boost::vertex_index, G)));
  
  for(auto [a,b] : querries){
    if(CGAL::squared_distance(a,b) <= r){
      std::cout << 'y';
      continue;
    }
    
    auto ca = t.nearest_vertex(a);
    auto cb = t.nearest_vertex(b);
    if(std::max(CGAL::squared_distance(a,ca->point()), CGAL::squared_distance(b,cb->point())) > r){
      std::cout << 'n';
      continue;
    }
    if(comp[ca->info()] == comp[cb->info()]){
      std::cout << 'y';
    }else{
      std::cout << 'n';
    }
  }
  std::cout << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
}