#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_handle VH;

void solve(){
  int n,k,f;
  long s;
  std::cin >> n >> k >> f >> s;
  
  std::vector<P> tents(n);
  for(int i = 0; i < n; i++){
    int x,y;
    std::cin >> x >> y;
    tents[i] = P(x,y);
  }
  
  Triangulation t;
  t.insert(tents.begin(), tents.end());
  graph g(n);
  std::unordered_map<VH, int> m;
  int i =0;
  std::vector<std::pair<K::FT, std::pair<int, int>>> q;
  for(auto u = t.finite_vertices_begin(); u!=t.finite_vertices_end(); u++){
    m[u] = i++;
  }
  
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++){
    auto f = (e->first);
    int i = e->second;
    auto vs = f->vertex(f->cw(i));
    auto vt = f->vertex(f->ccw(i));
    int i1 = m[vs];
    int i2 = m[vt];

    K::FT d = CGAL::squared_distance(vs->point(),vt->point());
    q.push_back({d, {i1, i2}});
    if(d<s){
      boost::add_edge(i1,i2,g);
    }
  }
  int num = boost::connected_components(g, boost::dummy_property_map());
  std::sort(q.begin(), q.end());

  std::cout <<(long)CGAL::to_double(q[n - f + 1]) << ' ' << num << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  int t;
  std::cin >> t;
  while(t--)solve();
  return 0;
}