#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

int n;
LL tbl[151][3];

// 01 - 0
// 10 - 1
// 11 - 2
LL dyn(int len, int fi) {
  LL &r=tbl[len][fi];
  if (r==-1) {
    if (!len) r=1;
    else {
      r=0;
      if (fi==0) r += dyn(len-1, 1);
      else if (fi==1) r += dyn(len-1, 0)+dyn(len-1, 2);
      else r += dyn(len-1, 0);
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(tbl, -1, sizeof tbl);
  while (cin>>n) {
    if (n==0) cout<<1<<endl;
    else if (n==1) cout<<2<<endl;
    else cout<<dyn(n-2, 0)+dyn(n-2, 1)+dyn(n-2, 2)<<endl;
  }
  return 0;
}





