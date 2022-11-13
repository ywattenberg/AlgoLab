#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


bool solve(){
  int n,d;
  std::cin >> n;
  if(n==0)return false;
  std::cin >> d;
  
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  for(int i = 0; i < n; i++){
    int norm = 0;
    for(int j = 0; j < d; j++){
      int a;
      std::cin >> a;
      lp.set_a(j, i, a);
      norm += a*a;
    }
    lp.set_a(d, i, std::sqrt(norm));

    //std::cout << "norm: " << std::sqrt(norm) << '\n';
    int b;
    std::cin >> b;
    lp.set_b(i, b);
  }
  lp.set_l(d, true, 0);
  lp.set_c(d, -1);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_optimal()){
    double sol = -CGAL::to_double(s.objective_value());
    std::cout << (long)std::floor(sol) << '\n';
  }else if(s.is_unbounded()){
    std::cout << "inf\n";
  }else {
    std::cout << "none\n";
  }
  return true;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  while(solve());
  return 0;
}