#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef multiset<int> IS;

int n;
IP a[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n && n) {
    for (int i=0; i<n; ++i) cin>>a[i].first>>a[i].second;
    sort(a, a+n);
    IS clo;
    int ini = 0;
    int cnt = 0;
    int mod = 0;
    int len = 0;
    for (int i=0; i<n; ++i) {
      clo.insert(a[i].second);
      auto it = clo.begin();
      while (*it<a[i].first) {
	it = clo.erase(it);
	--cnt;
      }
      if (*it==a[i].first) it = clo.erase(it);
      else {
	ini = a[i].first;
	++cnt;
      }
      if (mod<cnt || (mod==cnt && len<*it-ini)) {
	mod = cnt;
	len = *it-ini;
      }
    }
    cout << mod << ' ' << len << endl;
  }
  return 0;
}





