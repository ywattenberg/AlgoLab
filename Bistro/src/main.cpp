#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Gmpq.h>
#include <CGAL/squared_distance_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef std::vector<K::Point_2> VP;

double ceil_to_double(const K::FT& x) {
  double a = ceil(CGAL::to_double(x));
  while (a+1 >= x) a -= 1;
  while (a < x) a += 1;
  return a;
}

bool solve(){
  int n,m;
  std::cin >> n;
  if(n == 0)return false;
  VP exist(n);
  for(int i = 0; i < n; i++){
    int x,y;
    std::cin >> x >> y;
    exist[i] = K::Point_2(x,y);
  }
  Triangulation t;
  t.insert(exist.begin(), exist.end());
  std::cin >> m;
  for(int i = 0; i < m; i++){
    int x,y;
    std::cin >> x >> y;
    K::Point_2 p(x,y);
    auto dist = CGAL::squared_distance(t.nearest_vertex(p)->point(), p);
    std::cout << (long)ceil_to_double(dist) << '\n';
  }
  return true;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  while(solve());
  return 0;
}