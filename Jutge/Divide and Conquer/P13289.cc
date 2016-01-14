#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> IP;

LL t, n, ini, fi;
IP a[100001];
char c;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  t = 0;
  while (cin>>ini>>fi && fi) {
    cin >> n;
    for (int i=0; i<n; ++i) cin>>a[i].first>>c>>a[i].second;
    sort(a, a+n);
    LL acc = 0;
    LL mn = ini;
    for (int i=0; i<n; ++i) {
      LL dif = a[i].first-mn;
      if (dif>0) acc += (dif/8)*8;
      if (mn<a[i].second) mn=a[i].second;
    }
    cout<<'#'<<++t<<": "<<acc+((fi-mn)/8)*8<<endl;
  }
  return 0;
}





