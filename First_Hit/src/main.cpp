#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;


double floor_to_double(const K::FT& x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

bool solve(){
  int n;
  std::cin >> n;
  if(n == 0){
    return false;
  }
  long x,y,a,b;
  std::cin >> x >> y >> a >> b;
  P sp(x,y);
  P e_p(x,y);
  P e_q(a,b);
  K::Ray_2 ray(e_p, e_q);
  
  std::vector<S> segs(n);
  for(int i = 0; i < n; i++){
    std::cin >> x >> y >> a >> b;
    segs[i] = S(P(x,y), P(a,b));
  }
  std::random_shuffle(segs.begin(), segs.end());
  S best_seg;
  bool found = false;
  
  for(int i = 0; i < n; i++){
    if((!found && CGAL::do_intersect(segs[i], ray)) || (found && CGAL::do_intersect(segs[i], best_seg))){
      auto res = (!found)? (CGAL::intersection(segs[i], ray)):(CGAL::intersection(segs[i], best_seg));
      found = true;
      if(const P* op = boost::get<P>(&*res)){
        best_seg = S(sp, *op);

      } else if(const S* os = boost::get<S>(&*res)){
        K::FT d_s = CGAL::squared_distance(os->source(), sp);
        K::FT d_t = CGAL::squared_distance(os->target(), sp);
        if (d_s < d_t){
          best_seg = S(sp, os->source());
        }else {
          best_seg = S(sp, os->target());
        }
      }
    }
  }
  
  if(!found){
    std::cout << "no\n"; 
  } else {
    P tmp_p = best_seg.target();
    std::cout << (long) floor_to_double(tmp_p.x()) << ' ' << (long) floor_to_double(tmp_p.y()) << '\n'; 
  }
  return true;
}

int main(){
  
  while(solve());
}