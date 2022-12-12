#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Gmpq.h>
#include <CGAL/squared_distance_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef std::vector<K::Point_2> VP;

bool survivor(int r, const VP& lamps, const VP& player, const std::vector<int>& rad, int h){
  Triangulation t;
  t.insert(lamps.begin(), lamps.begin()+r+1);
  for(int i = 0; i < player.size(); i++){
    auto close_h = t.nearest_vertex(player[i]);
    auto close_lamp = (*close_h).point();
    if(CGAL::squared_distance(close_lamp, player[i]) >= std::pow(rad[i]+h, 2)){
      return true;
    }
  }
  return false;
}


void solve(){
  int m,n;
  std::cin >> m >> n;
  VP ppl(m);
  std::vector<int> rad(m);
  
  for(int i = 0; i < m; i++){
    int x,y,r;
    std::cin >> x >> y >> r;
    ppl[i] = K::Point_2(x,y);
    rad[i] = r;
  }
  int h;
  std::cin >> h;
  VP lamps;
  
  for(int i = 0; i < n; i++){
    int x,y;
    std::cin >> x >> y;
    lamps.push_back(K::Point_2(x,y));
  }
  //up to l ppl surive ex
  //down to r all get caught
  int l=0,r=n-1;
  while(r >= l){
    int m = (l+r)/2;
    if(survivor(m,lamps,ppl,rad,h)){
      l=m+1;
    }else{
      r=m-1;
    }
  }
  std::vector<int> suv;
  Triangulation t;
  t.insert(lamps.begin(), lamps.begin()+l);
  for(int i = 0; i < m; i++){
    K::Point_2 close_lamp = t.nearest_vertex(ppl[i])->point();
    if(CGAL::squared_distance(close_lamp, ppl[i]) >= std::pow(rad[i]+h, 2)){
      suv.push_back(i);
    }
  }
  for(int i : suv){
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--)solve();
  return 0;
}

