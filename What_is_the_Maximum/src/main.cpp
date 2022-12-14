#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

bool solve(){
  int p, a, b;
  std::cin >> p;
  if(p == 0){
    return false;
  }
  std::cin >> a >> b;
  
  const int X = 0;
  const int Y = 1;
  const int Z = 2;
    
  Program lp;
  if(p==1){
    lp =  Program(CGAL::SMALLER, true, 0, false, 0);
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
    lp.set_c(X, a); lp.set_c(Y, -b);
  }else{
    lp =  Program(CGAL::LARGER, false, 0, true, 0);
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, -4);
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -a*b);
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);
    lp.set_c(X, a); lp.set_c(Y, b); lp.set_c(Z, 1);
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_optimal()){
    double sol = CGAL::to_double(s.objective_value());
    if(p ==1){
      sol *= -1;
      std::cout << std::floor(sol) << '\n';
    }else{
      std::cout << std::ceil(sol) << '\n';
    }
    
  }else if(s.is_infeasible()){
    std::cout << "no\n";
  } else {
    std::cout << "unbound\n";
  }
  
  return true;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  while(solve());
}