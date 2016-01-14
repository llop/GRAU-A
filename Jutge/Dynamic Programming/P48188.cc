#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

int n, mn;
int val[26];
string w1, w2;
LL tbl[1001][1001];

inline int code(const char &c) { return c-'a'; }
inline int f(int a, int b) { int x=a+b; return x/4+(x%4?1:0); /*ceil(x/4)*/ }
inline int cheap(int x) { return min(x, mn+f(x, mn)); }

LL dyn(int i, int j) {
  LL &r=tbl[i][j];
  if (r==-1) {
    r=dyn(i-1, j-1);
    if (w1[i-1]!=w2[j-1]) {
      // change both letters
      //  - both to cheapest
      //  - a to b (or b to a)
      int x=f(val[code(w1[i-1])], mn)+f(val[code(w2[j-1])], mn);
      int y=f(val[code(w1[i-1])], val[code(w2[j-1])]);
      LL r1=min(x, y)+r;
      // insert letter into w1
      //  - min( b, cheapest + change b to cheapest )
      LL r2=cheap(val[code(w2[j-1])])+dyn(i, j-1);
      // insert letter into w2
      //  - min( a, cheapest + change a to cheapest )
      LL r3=cheap(val[code(w1[i-1])])+dyn(i-1, j);
      r=min(r1, min(r2, r3));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    mn=1001;
    for (int i=0; i<n; ++i) {
      cin>>val[i];
      mn=min(mn, val[i]);
    }
    cin>>w1>>w2;
    for (int i=1; i<=(int)w1.size(); ++i) for (int j=1; j<=(int)w2.size(); ++j) tbl[i][j]=-1;
    tbl[0][0]=0;
    for (int i=1; i<=(int)w1.size(); ++i) tbl[i][0]=tbl[i-1][0]+cheap(val[code(w1[i-1])]);
    for (int i=1; i<=(int)w2.size(); ++i) tbl[0][i]=tbl[0][i-1]+cheap(val[code(w2[i-1])]);
    cout<<dyn(w1.size(), w2.size())<<endl;
  }
  return 0;
}


