#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

LL tbl[31][31][3];

LL dyn(int z, int u, int m) {
  if (z<0 || u<0) return 0;
  LL &r=tbl[z][u][m];
  if (r==-1) {
    if (z+u==2) {
      if (!m) r=z==2 || !z;
      else r=u==1;
    } else {
      if (!m) r=dyn(z-1, u, 0)+dyn(z, u-1, 1);
      else if (m==1) r=dyn(z-1, u, 2)+dyn(z, u-1, 0);
      else r=dyn(z-1, u, 1)+dyn(z, u-1, 2);
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(tbl, -1, sizeof tbl);
  int z, u;
  while (cin>>z>>u) {
    if (z+u<2) cout<<(z+u==0 || z==1 ? 1 : 0)<<endl;
    else cout<<dyn(z, u, 0)<<endl;
  }
  return 0;
}





