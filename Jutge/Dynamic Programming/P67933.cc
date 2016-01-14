#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

LL tbl[16][16][2];

LL dyn(int v, int c, int l) {
  if (v<0 || c<0) return 0;
  LL &r=tbl[v][c][l];
  if (r==-1) {
    r=dyn(v-1, c, 0)*5;
    if (!l) r+=dyn(v, c-1, 1)*21;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(tbl, -1, sizeof tbl);
  tbl[0][0][0]=tbl[0][0][1]=1;
  int n, v, c;
  while (cin>>n>>v) {
    c=n-v;
    cout<<dyn(v-1, c, 0)*5+dyn(v, c-1, 1)*21<<endl;
  }
  return 0;
}





