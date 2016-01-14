#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int n;                  // number of vertices
double c[101][2];       // vertex coords
double tbl[101][101];   // memo table
double dis[101][101];   // distances table

// returns the cheapest triangulation of the polygon
// formed by vertices [x..y]
double dyn(int x, int y) {
  double &r=tbl[x][y];
  if (r<0.0) {
    // base case: vertex x is next to y, so they are joined by an edge
    // of the polygon and cost is zero
    if (x+1==y) r=0.0;        
    else {
      // inductive step: cost is min amongst all possible ways
      // to split the polygon in two
      r=1e18;                           // large initial value
      for (int i=x+1; i<y; ++i)         // for each vertex between x and y
        r=min(r, dyn(x, i)+dyn(i, y)    // cheapest triangulation of 2 polygons [x..i] and [i..y]
                +dis[x][i]+dis[i][y]);  // plus adding the two closing diagonals
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) {
      cin>>c[i][0]>>c[i][1];                    // read coords
      for (int j=0; j<n; ++j) tbl[i][j]=-1.0;   // reset memoization table
      for (int j=0; j<i-1; ++j) {               // precalculate euclidean distances
        double c1=c[i][0]-c[j][0];
        double c2=c[i][1]-c[j][1];
        dis[j][i]=sqrt(c1*c1+c2*c2);
      }
    }
    cout<<fixed<<setprecision(4)<<dyn(0, n-1)<<endl;
  }
  return 0;
}