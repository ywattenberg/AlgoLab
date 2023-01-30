/// 
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation = CGAL::Delaunay_triangulation_2<K>;
using Edge_iterator = Triangulation::Edge_iterator;
using P = K::Point_2;

long dist_to_time(K::FT d){
  return std::ceil(std::sqrt(d - 0.5));
}

bool sol(){
  int n; std::cin >> n;
  if(!n)return false;
  int x1,x2,y1,y2; std::cin >> x1 >> y1 >> x2 >> y2;
  std::vector<P> bat(n);
  for(int i = 0; i< n; i++){
    int x,y;
    std::cin >> x >> y;
    bat[i] = P(x,y);
  }
  Triangulation t;
  t.insert(bat.begin(), bat.end());
  std::vector<K::FT> min_dist;
  min_dist.reserve(n);
  for(auto vert = t.finite_vertices_begin(); vert != t.finite_vertices_end(); vert++){
    K::FT min_res = std::numeric_limits<double>::max();
    Triangulation::Edge_circulator e = t.incident_edges(vert);
    if(e != NULL){
      do{
        if (!t.is_infinite(e)){
          min_res = std::min(min_res, t.segment(e).squared_length());
        }
      }while(++e != t.incident_edges(vert));
    }
    const K::FT x = vert->point().x();
    const K::FT y = vert->point().y();
    K::FT edge_min = std::min({std::abs(x1-x), std::abs(x2-x), std::abs(y1-y), std::abs(y2-y)});
    min_dist.push_back(std::min((std::sqrt(min_res)/2), edge_min));
  }
  std::sort(min_dist.begin(), min_dist.end());
  std::cout << dist_to_time(min_dist[0]) << " " << dist_to_time(min_dist[n/2]) << " " <<  dist_to_time(min_dist[n-1]) << "\n";
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while (sol());
}
