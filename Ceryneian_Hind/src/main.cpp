#include<iostream>

void testcase() {
  int n, m;
  std::cin >> n >> m;
  
  for (int i = 0; i < n; ++i) {
    int s; std::cin >> s;
  }
  
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
  }
  
  std::cout << "impossible" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
  
  return 0;
}