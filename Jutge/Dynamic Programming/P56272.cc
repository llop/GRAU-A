#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

int r, c;
LL tbl[51][51];
LL sol[51][51];

LL dyn(int x, int y, int z) {
  if (y<0 || y>=z) return 0;
  LL &r=tbl[x][y];
  if (r==-1) {
    if (x) r=dyn(x-1, y-1, z)+dyn(x-1, y+1, z);
    else r=1;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  for (int x=1; x<51; ++x) for (int y=1; y<51; ++y) {
    for (int i=0; i<=x; ++i) for (int j=0; j<=y; ++j) tbl[i][j]=-1;
    sol[x][y]=0;
    for (int i=0; i<y; ++i) sol[x][y]+=dyn(x-1, i, y);
  }
  while (cin>>r>>c) cout<<sol[r][c]<<endl;
  return 0;
}


