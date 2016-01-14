#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

LL tbl[91][91][3];

// 01 - 0
// 10 - 1
// 11 - 2
LL dyn(int z, int u, int fi) {
  if (z<0 || u<0) return 0;
  LL &r=tbl[z][u][fi];
  if (r==-1) {
    if (z+u==2) {
      if (fi==2) r=u==2;
      else r=u==1;
    } else {
      if (fi==0) r = dyn(z, u-1, 1);
      else if (fi==1) r = dyn(z-1, u, 0)+dyn(z-1, u, 2);
      else r = dyn(z, u-1, 0);
    }
  }
  return r;
}

int u, z;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(tbl, -1, sizeof tbl);
  while (cin>>z>>u) {
    if (z+u<2) cout<<1<<endl;
    else cout<<dyn(z, u, 0)+dyn(z, u, 1)+dyn(z, u, 2)<<endl;
  }
  return 0;
}





