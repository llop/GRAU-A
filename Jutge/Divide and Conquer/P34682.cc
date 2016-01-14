#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

typedef long long LL;

int n, m, a, t;
LL s[1000001];

inline void bin() {
  int l = 0;
  int r = n;
  while (l<r) {
    int mid=(l+r)>>1;
    LL x = s[mid]+a;
    if (x>=mid+1) r=mid;
    else l=mid+1;
  }
  if (l>=n || s[l]+a!=l+1) cout << "no fixed point for " << a << endl;
  else cout << "fixed point for " << a << ": " << l+1 << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  t = 1;
  while (cin >> n) {
    cout << "Sequence #" << t++ << endl;
    for (int i=0; i<n; ++i) cin >> s[i];
    cin >> m;
    for (int i=0; i<m; ++i) {
      cin >> a;
      bin();
    }
    cout << endl;
  }
  return 0;
}





