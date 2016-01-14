#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

int n;
LL p;
int g[100001];

inline bool check(int x) {
  --x;
  int i=0;
  int c=0;
  int mx=g[i]+x;
  while (i<n && c<p) {
    if (g[i]>mx) {
      mx=g[i]+x;
      ++c;
    }
    ++i;
  }
  //cout<<x+1<<(c<p && i==n?" good ":" bad ")<<c<<' '<<i<<endl;
  return c<p && i==n;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>g[i];
    cin>>p;
    sort(g, g+n);
    int l=1;
    int r=(g[n-1]-g[0])+1;
    while (l<r) {
      int x=(l+r)>>1;
      if (check(x)) r=x;
      else l=x+1;
    }
    cout<<l*p<<endl;
  }
  return 0;
}





