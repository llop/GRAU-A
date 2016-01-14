#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;

int x, d, n;
int sta[100002];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>x>>d>>n) {
    for (int i=1; i<=n; ++i) cin>>sta[i];
    sort(sta+1, sta+n+1);
    sta[0]=0;
    sta[n+1]=d;
    int acc=-1;
    int mx=-1;
    for (int i=1; i<=n+1; ++i) if (mx<sta[i]) {
      mx=sta[i-1]+x;
      ++acc;
    }
    cout<<acc<<endl;
  }
  return 0;
}





