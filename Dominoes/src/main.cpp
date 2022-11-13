
#include <iostream>
#include <limits>
#include<ios>

using namespace std;

int main(){
  int t;   
  cin >> t; // get number of test cases
  
  for(int i = 0; i < t; ++i){
    int n;
    cin >> n; // get number of dominos
   
    int domino_stack = 2;
    int next_domino;
    int j = 0;
    for(; j < n; ++j){
      --domino_stack; //shorten domino
      if (domino_stack <= 0){
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // read in the rest of the inputs
        break;
      } else {
        cin >> next_domino;
        if (next_domino > domino_stack) {
          domino_stack = next_domino;
        }
      }
    }
    cout << j << endl;
  }
  
  
  
  return 0;
}