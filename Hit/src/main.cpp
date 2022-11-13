#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

bool solve(){
  int n;
  std::cin >> n;
  if(n == 0) {
    return false;
  }
  
  long x, y, a, b;
  std::cin >> x >> y >> a >> b;
  K::Point_2 p1(x,y), p2(a,b);
  K::Ray_2 ray(p1, p2);
  
  for(int i = 0; i < n; i++){
    std::cin >> x >> y >> a >> b;
    
    K::Point_2 p1(x,y), p2(a,b);
    K::Segment_2 seg(p1, p2);
    
    if(CGAL::do_intersect(ray, seg)){
      std::cout << "yes\n";
      
      for(int j = i+1; j < n; j++){
        std::cin >> x >> y >> a >> b;
      }
      return true;
    }
  }
  std::cout << "no\n";
  return true;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  bool t = true;
  while(t){
    t = solve();
  };
  return 0;
}