#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;

int t, n, q;
LL tbl[100002];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  t=1;
  while (cin>>n) {
    cout<<'#'<<t<<endl;
    ++t;
    tbl[0]=0;
    for (int i=1; i<=n; ++i) {
      cin>>tbl[i];
      tbl[i]+=tbl[i-1];
    }
    cin>>q;
    for (int i=0; i<q; ++i) {
      int x, y;
      cin>>x>>y;
      if (x>y) swap(x, y);
      cout<<tbl[y]-tbl[x-1]<<endl;
    }
  }
  return 0;
}





