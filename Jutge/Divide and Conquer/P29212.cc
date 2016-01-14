#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

typedef long long LL;

LL mpow(LL a, LL b, LL m) {
  if (!b) return 1;
  LL c = mpow(a, b>>1, m);
  c = c*c;
  if (b&1) c = (c%m)*a;
  return c%m;
}

LL n, k, m;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n>>k>>m) cout<<mpow(n, k, m)<<endl;
  return 0;
}





