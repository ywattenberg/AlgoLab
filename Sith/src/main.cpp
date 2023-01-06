#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Index = int;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Index,K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb,Fb>;
using Delaunay = CGAL::Delaunay_triangulation_2<K,Tds>;
using POPI = std::pair<K::Point_2,int>;

int biggest_comp(const int k, const long r, const std::vector<POPI>& plan){
  Delaunay t;
  t.insert(plan.begin()+k, plan.end());
  std::vector<int> reached(plan.size(), 1);
  boost::disjoint_sets_with_storage<> uf(plan.size());
  int n_comp = plan.size()-k;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index c1 = uf.find_set(e->first->vertex((e->second+1)%3)->info());
    Index c2 = uf.find_set(e->first->vertex((e->second+2)%3)->info());
    if (c1 != c2 && t.segment(e).squared_length() <= r) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
      int new_v = reached[c1] + reached[c2];
      reached[uf.find_set(c1)] = new_v;
      if(new_v >= k)
        return new_v;
      if(--n_comp == 1)break;
    }
  }
  return *std::max_element(reached.begin(), reached.end());
}

void solve(){
  int n;
  long rad;
  std::cin >> n >> rad;
  rad = rad * rad;
  std::vector<POPI> plan(n);
  for(int i= 0; i < n; i++){
    int x, y;
    std::cin >> x >> y;
    plan[i] = {K::Point_2(x,y), i};
  }
  
  int l = 1, r = n/2+1;
  while(l < r){
    int m = l + (r - l)/2;
    int res = biggest_comp(m, rad, plan);
    //std::cout << res << std::endl;
    if(m > res){
      r = m;
    }else l = m+1;
  }
  std::cout << l-1 << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
  return 0;
}