#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;
typedef std::vector<std::pair<int, int>> VPI;

bool solve(){
  int n, m;
  std::cin >> n >> m;
  if(n == 0 && m == 0){
    return false;
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  for(int i = 0; i < n; i++){
    int l,u;
    std::cin >> l >> u;
    lp.set_b(i, u);
    lp.set_b(i+n, -l);
  }
  
  //VI cost(m);
  for(int i = 0; i < m; i++){
    int c;
    std::cin >> c;
    //cost[i] = c;
    lp.set_c(i, c);
    for(int j = 0; j < n; j++){
      int g;
      std::cin >> g;
      lp.set_a(i, j, g);
      lp.set_a(i, j+n, -g);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_optimal()){
    double sol = CGAL::to_double(s.objective_value());
    std::cout << std::floor(sol) << '\n';
  }else {
    std::cout << "No such diet.\n";
  }
  
  
  return true;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  while(solve());
  return 0;
}