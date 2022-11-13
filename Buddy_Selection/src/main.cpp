///2
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS>
                                                                graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
typedef std::map<edge_desc, boost::edge_weight_t>               edge_weight_map;                 
typedef boost::associative_property_map<edge_weight_map>        weight_map;

struct Counter
{
  struct value_type { template<typename T> value_type(const T&) { } };
  void push_back(const value_type&) { ++count; }
  size_t count = 0;
};

int intersection_size(const std::set<int>& s1, const std::set<int>& s2)
{
  Counter c;
  set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(c));
  return c.count;
}

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n); // exterior property map
  boost::edmonds_maximum_cardinality_matching(G,
          boost::make_iterator_property_map(mate_map.begin(),
          boost::get(boost::vertex_index, G)));
          
  return boost::matching_size(G,
                  boost::make_iterator_property_map(mate_map.begin(),
                  boost::get(boost::vertex_index, G)));
}


void solve(){
  int n, c, f;
  std::cin >> n >> c >> f;
  std::unordered_map<std::string, int> sti;
  
  std::vector<std::set<int>> intrests(n);
  int num_of_c=0;
  std::string s;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < c; ++j){
      std::cin >> s;
      auto it = sti.find(s);
      if(it != sti.cend()){
        intrests[i].insert((*it).second);
      }else{
        sti.insert({s, num_of_c});
        intrests[i].insert(num_of_c);
        num_of_c++;
      }
    }
  }
  int num_edges = 0;
  graph G(n);
  for(int i = 0; i < n; ++i){
    for(int j = i+1; j < n; ++j){
      if(intersection_size(intrests[i], intrests[j]) > f){
        num_edges++;
        boost::add_edge(i, j, G);
      }
    }
  }
  

  if(maximum_matching(G) == n/2){
    std::cout << "not optimal \n";
  } else {
    std::cout << "optimal \n";
  }
  
  
  
}

int main(){
  int t;
  std::cin >> t;
  for(int i = 0; i < t; ++i){
    solve();
  }
}