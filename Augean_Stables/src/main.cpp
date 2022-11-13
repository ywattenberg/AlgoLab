#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <algorithm>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<long> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef std::vector<int> VI;

struct stall {
  long f,c,k,l,m;
};

typedef std::vector<stall> VS;

bool comp(const VS& stalls, long a, long p){
  Program lp(CGAL::LARGER, true, 0, true, 1);
  const long A = a*a, B = p*p, C = a*p;
  for(int i = 0; i < stalls.size(); i++){
    lp.set_b(i,stalls[i].f - stalls[i].c);
    lp.set_a(0, i, stalls[i].k + A);
    lp.set_a(1, i, stalls[i].l + B);   
    lp.set_a(2, i, stalls[i].m + C);
  }
  auto s = CGAL::solve_linear_program(lp, ET());
  return !s.is_infeasible();
}

bool search(const VS& stalls, const VI& a, const VI& b, int sum){
  std::vector<std::pair<int, int>> vec;
  for(int i = std::max(0, sum-25); i <= std::min(sum, 25); i++){
    vec.push_back({i, sum-i});
  }
  std::random_shuffle(vec.begin(), vec.end());
  for(auto p: vec){
    if(comp(stalls, a[p.first], b[p.second])){
      return true;
    }
  }
  return false;
}

void solve(){
  int n;
  std::cin >> n;
  std::vector<stall> stalls(n);
  for(int i = 0; i < n; i++){
    std::cin >> stalls[i].f >> stalls[i].c >> stalls[i].k >> stalls[i].l >> stalls[i].m;
  }
  VI as(25);
  as[0] = 0;
  for(int i = 1; i < 25; i++){
    int a;
    std::cin >> a;
    as[i] = as[i-1]+a;
  }
  VI ps(25);
  ps[0] = 0;
  for(int i = 1; i < 25; i++){
    int p;
    std::cin >> p;
    ps[i] = ps[i-1]+p;
  }
  if(!search(stalls,as,ps,48)){
    std::cout << "Impossible!\n";
    return;
  }
  int l = 0, r = 48;
  while(l < r){
    int mid = l + (r - l)/2;
    if(search(stalls,as,ps,mid)){
      r = mid;
    }else{
      l = mid+1;
    }
  }
  if(r == 48){
    std::cout << "Impossible!\n";
  }else{
    std::cout << l << '\n';
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while(t--){
    solve();
  }
  return 0;
}