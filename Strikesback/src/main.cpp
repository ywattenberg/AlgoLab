///1
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

typedef CGAL::Gmpq IT;
typedef CGAL::Quadratic_program<IT> Program;

typedef K::Point_2 P;
typedef std::vector<P> VP;
typedef std::vector<int> VI;

#define FOR(C, D) for(int C = 0; C < D; C++)


void solve(){
  int a,s,b,e;
  std::cin >> a >> s >> b >> e;
  VP ast(a), shots(s), bounty(b);

  VI ds(a);
  FOR(i, a){
    int x, y, d;
    std::cin >> x >> y >> d;
    ast[i] = P(x,y); ds[i] = d;
  }
  
  FOR(i, s){
    int x,y;
    std::cin >> x >> y;
    shots[i] = P(x,y);
  }
  
  FOR(i, b){
    int x,y;
    std::cin >> x >> y;
    bounty[i] = P(x,y);
  }
  
  Triangulation t;
  t.insert(bounty.begin(), bounty.end());
  std::vector<K::FT> shot_r(s, -1);
  Program lp (CGAL::LARGER, true, 0, false, 0);
  
  FOR(i, s){
    auto near = t.nearest_vertex(shots[i]);
    if(near == nullptr)
      continue;
    K::FT dist = CGAL::squared_distance(near->point(), shots[i]);
    shot_r[i] = dist;
  }

  FOR(i,a){
    lp.set_b(i, ds[i]);
    FOR(j, s){
      K::FT dist = CGAL::squared_distance(ast[i], shots[j]);
      if(shot_r[j] < 0 || dist < shot_r[j]){
        lp.set_a(j, i, CGAL::Gmpq(1, std::max(K::FT(1), dist)));
      }
    }
  }
  FOR(i, s)lp.set_a(i, a, -1);
  lp.set_b(a, -e);
  
  auto sol = CGAL::solve_linear_program(lp, CGAL::Gmpq());
  if (sol.is_infeasible()){
    std::cout << "n\n";
    return;
  }
  std::cout << "y\n"; 
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  int t;
  std::cin >> t;
  while(t--)solve();
}