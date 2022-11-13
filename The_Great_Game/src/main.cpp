///3
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> IV;

int recurse(int n, int field, bool turn, vector<IV>* adj_list, IV* fst, IV* snd){
  if (turn){
    if ((*fst)[field] > -1){
      return (*fst)[field];
    }
    else if ((*fst)[field] == -1){
      int min = -1, tmp;
      for(int i : (*adj_list)[field]){
        tmp = recurse(n, i, !turn, adj_list, fst, snd)+1;
        if(tmp < min || min == -1){
          min = tmp;
        }
      }
      (*fst)[field] = min;
      return min;
    }
    cout << "ERROR" << endl;
    return 0;
  } else {
    if ((*snd)[field] > -1){
      return (*snd)[field];
    }
    else if ((*snd)[field] == -1){
      int max = -1, tmp;
      for(int i : (*adj_list)[field]){
        tmp = recurse(n, i, !turn, adj_list, fst, snd)+1;
        if(tmp > max || max == -1){
          max = tmp;
        }
      }
      (*snd)[field] = max;
      return max;
    }
  }
  cout << "ERROR" << endl;
  return 0;
}

void solve(){
  int n, m, r, b;
  cin >> n >> m >> r >> b;
  r--;
  b--;

  vector<IV> adj_list(n);
  int u,v;
  for(int i = 0; i < m; i++){
    cin >> u >> v;
    adj_list[u-1].push_back(v-1);
  }
  
  IV  fst(n, -1);
  IV  snd(n, -1);
  fst[n-1] = 0;
  snd[n-1] = 0;
  int sh = recurse(n, r, true, &adj_list, &fst, &snd);
  fill(fst.begin(), fst.end(), -1);
  fill(snd.begin(), snd.end(), -1);
  fst[n-1] = 0;
  snd[n-1] = 0;
  int mo = recurse(n, b, true, &adj_list, &fst, &snd);
  if (mo == sh){
    cout << (mo % 2 == 0) << endl;
  } else {
    cout << (mo < sh) << endl;
  }
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
    solve();
  }
}