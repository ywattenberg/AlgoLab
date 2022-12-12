///1
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void solve(){
  int n;
  std::cin >> n;
  graph G(n*n);
  std::vector<std::vector<bool>> present(n, std::vector<bool>(n));
  
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        int p;
        std::cin >> p;
        present[i][j] = p;
      }
    }
  
  auto index = [n] (int x, int y){return y*n + x;};
  auto white = []  (int x, int y){return (x + y) & 1;};
  
  int count = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(!present[i][j])continue;
      count++;
      if(white(i,j))continue;
      
      if(i-1 >= 0){
        if(j-2 >= 0 && present[i-1][j-2]){boost::add_edge(index(i,j), index(i-1,j-2), G);}
        if(j+2 < n  && present[i-1][j+2]){boost::add_edge(index(i,j), index(i-1,j+2), G);}
      }
      if(i+1 < n){
        if(j-2 >= 0 && present[i+1][j-2]){boost::add_edge(index(i,j), index(i+1,j-2), G);}
        if(j+2 < n  && present[i+1][j+2]){boost::add_edge(index(i,j), index(i+1,j+2), G);}
      }
      if(i-2 >= 0){
        if(j-1 >= 0 && present[i-2][j-1]){boost::add_edge(index(i,j), index(i-2,j-1), G);}
        if(j+1 < n  && present[i-2][j+1]){boost::add_edge(index(i,j), index(i-2,j+1), G);}
      }
      if(i+2 < n){
        if(j-1 >= 0 && present[i+2][j-1]){boost::add_edge(index(i,j), index(i+2,j-1), G);}
        if(j+1 < n  && present[i+2][j+1]){boost::add_edge(index(i,j), index(i+2,j+1), G);}
      }
    }
  }
  std::vector<vertex_desc> mate_map(n*n);
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  int result = count - matching_size;
  std::cout << result << std::endl;
  
  //std::cout << min << '\n';
}
int main(){
  int t;
  std::cin >> t;
  while(t--)solve();
}
