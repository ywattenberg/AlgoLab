///1
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>



typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x) {
  double a = ceil(CGAL::to_double(x));
  while (a+1 >= x) a -= 1;
  while (a < x) a += 1;
  return a;
}

double floor_to_double(const K::FT& x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}


int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  
  while(n > 0){
    std::vector<K::Point_2> p(n);
    for(int i = 0; i < n; i++){
      long x,y;
      std::cin >> x >> y;
      p[i] = K::Point_2(x,y);
    }
    Min_circle mc(p.begin(), p.end(), true);
    Traits::Circle c = mc.circle();
    std::cout << (long)ceil_to_double(CGAL::sqrt(c.squared_radius())) << '\n';
    std::cin >> n;
  }
}