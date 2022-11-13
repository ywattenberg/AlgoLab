///1
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel KI;

typedef CGAL::Point_2<KI> PI;
#define IN(x) int x;std::cin>>x

void tc(){
  int m,n,a,b; std::cin>>m>>n;
  
  int num_contained = 0;
  std::vector<int> num_triangles_containing_leg(m,0);
  std::vector<std::vector<int>> con(n);
  std::vector<PI> ps(m);
  
  for(int i=0;i<m;i++){
    std::cin>>a>>b;
    ps[i]=PI(a,b);
  }
  int best = n;
  int low = 0;
  for(int i=0;i<n;i++){//triangles
  
    IN(p11);IN(p12);IN(p21);IN(p22);IN(p31);IN(p32);
    IN(p41);IN(p42);IN(p51);IN(p52);IN(p61);IN(p62);
    PI p1(p11,p12);
    PI p2(p21,p22);
    PI p3(p31,p32);
    PI p4(p41,p42);
    PI p5(p51,p52);
    PI p6(p61,p62);
    //Add high
    
    auto o1 = CGAL::orientation(p1,p2,p3);
    auto o2 =  CGAL::orientation(p3,p4,p5);
    auto o3 =  CGAL::orientation(p5,p6,p1);
    auto pr1 = CGAL::orientation(p1,p2,ps[0]);
    auto pr2 = CGAL::orientation(p3,p4,ps[0]);
    auto pr3 = CGAL::orientation(p5,p6,ps[0]);
    for(int j=1;j<m;j++){//legs
      //!trg.has_on_unbounded_side(ps[j-1])&&!trg.has_on_unbounded_side(ps[j])
      //trg.has_on_bounded_side(ps[j-1])&&trg.has_on_bounded_side(ps[j])
      bool cond1= false;
      if((pr1 == CGAL::COLLINEAR  || pr1 == o1) &&
          (pr2 == CGAL::COLLINEAR || pr2 == o2) &&
          (pr3 == CGAL::COLLINEAR || pr3 == o3)) {
        cond1 = true;
      }
      pr1 = CGAL::orientation(p1,p2,ps[j]);
      pr2 = CGAL::orientation(p3,p4,ps[j]);
      pr3 = CGAL::orientation(p5,p6,ps[j]);
      if(cond1 &&
        ((pr1 == CGAL::COLLINEAR || pr1 ==o1) &&
          (pr2 == CGAL::COLLINEAR || pr2 == o2) &&
          (pr3 == CGAL::COLLINEAR || pr3 == o3))
        ){
        num_triangles_containing_leg[j]++;
        con[i].push_back(j);
        if(num_triangles_containing_leg[j]==1){
          num_contained++;
        }
      }
    }
    while(num_contained==(m-1)){
      //update best
      best = std::min(best,i-low+1);
      //remove low
      for(int j=0;j<(int)con[low].size();j++){
        int leg = con[low][j];
        num_triangles_containing_leg[leg]--;
        if (num_triangles_containing_leg[leg]==0){
          num_contained--;
        }
      }
      low+=1;
    }
  }
  std::cout << best << std::endl;
  
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  for(int i=0;i<n;i++){
    tc();
  }
}