#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef std::pair<int, int> PI;
typedef std::vector<PI> VPI;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

inline PI MINCONST(PI i, PI j, int w, int h){
  int x_const = std::abs(i.first - j.first)*2;
  int y_const = std::abs(i.second - j.second)*2;
  if((long)x_const * h > (long)y_const * w){
    return {x_const, w};
  }
  return  {y_const, h};
}

void solve(){
  int n, m, h, w;
  std::cin >> n >> m >> h >> w;
  
  VPI free_pos(n);

  for(int i = 0; i < n; i++){
    int x,y;
    std::cin >> x >> y;
    free_pos[i] = {x, y};
  }
  
  VPI occ_pos(m);
  for(int i = 0; i < m; i++){
    int x,y;
    std::cin >> x >> y;
    occ_pos[i] = {x, y};
  }
  
  int counter = 0;
  Program lp(CGAL::SMALLER, true, 1, false, 0);
  for(int i = 0; i < n; i++){
    lp.set_c(i, -1);
    for(int j = i+1; j < n; j++){
      PI min_v = MINCONST(free_pos[i], free_pos[j], w, h);
      lp.set_a(i, counter, min_v.second);
      lp.set_a(j, counter, min_v.second);
      lp.set_b(counter, min_v.first);
      counter++;
    }
    
    if(m == 0) continue;
    PI min_constrain = MINCONST(free_pos[i], occ_pos[0], w, h);
    for(int j = 1; j < m; j++){
      PI curr_const = MINCONST(free_pos[i], occ_pos[j], w, h);
      if((long)curr_const.first * min_constrain.second 
          < (long)min_constrain.first * curr_const.second){
        min_constrain = curr_const;
      }
    }
    lp.set_a(i, counter, min_constrain.second); 
    lp.set_b(counter, min_constrain.first-min_constrain.second); 
    counter++;

  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  long sol = (long)std::ceil(-2 * (w+h) * CGAL::to_double(s.objective_value()));
  std::cout << sol << '\n';
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  int t;
  std::cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  
  return 0;
}