#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;
typedef vector<int> IV;
typedef vector<pair<int, int>> PIV;

void merge(PIV *res, PIV *f, PIV *s){
  auto f_b = (*f).begin();
  auto f_e = (*f).end();
  auto s_b = (*s).begin();
  auto s_e = (*s).end();
  
  while(f_b != f_e && s_b != s_e){
    if((*f_b).first < (*s_b).first){
      (*res).push_back((*f_b));
      f_b++;
    }else{
      (*res).push_back((*s_b));
      s_b++;
    }
  }
  while(f_b != f_e){
    (*res).push_back((*f_b));
    f_b++;
  }
  while(s_b != s_e){
    (*res).push_back((*s_b));
    s_b++;
  }
}

void solve(){
  int n, tmp;
  cin >> n;
  IV m;
  vector<PIV> words;
  for(int i = 0; i < n; i++){
    cin >> tmp;
    m.push_back(tmp);
  }
  for(int i = 0; i < n; i++){
    PIV row;
    for(int j = 0; j < m[i]; j++){
      cin >> tmp;
      row.push_back({tmp, i});
    }
    words.push_back(row);
  }
  
  int num_lists = n;
  int round_num = 1;
  while(num_lists/2>= 1){
    for(int i = 0; i < n-(1<<(round_num-1)); i+=1<<round_num){
      PIV tmp;
      merge(&tmp, &words[i], &words[i+(1<<(round_num-1))]);
      words[i] = tmp;
    }
    num_lists = num_lists/2 + (num_lists%2);
    round_num++;
  }

  PIV sorted = words[0];
  IV seen_words(n,0);
  int num_el = sorted.size();
  int end = 0;
  seen_words[sorted[end].second]++;
  while(end+1 < num_el && std::any_of(seen_words.cbegin(), seen_words.cend(), [](int i) { return i==0; })){
    end++;
    seen_words[sorted[end].second]++;
  }
  
  int curr_min = sorted[end].first - sorted[0].first +1;
  int begin = 0;
  int removed_el = sorted[0].second;
  while(begin < num_el){

    removed_el = sorted[begin].second;
    seen_words[removed_el]--;
    if(seen_words[removed_el] > 0){
      begin++;
      continue;
    } else {
      if(curr_min > sorted[end].first - sorted[begin].first +1){
        curr_min = sorted[end].first - sorted[begin].first +1;
      }
      while(end+1 < num_el && sorted[end].second != removed_el){
        end++;
        seen_words[sorted[end].second]++;
      }
      if(end+1 == num_el){
        break;
      }
    }
    begin++;
  }
  if(seen_words[removed_el] > 0){
    while(seen_words[sorted[begin].second] > 1){
      seen_words[sorted[begin].second]--;
      begin++;
    }
    if(curr_min > sorted[end].first - sorted[begin].first +1){
      curr_min = sorted[end].first - sorted[begin].first +1;
    }
  } 
  
  cout << curr_min << endl;

}

int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
  return 0;
}