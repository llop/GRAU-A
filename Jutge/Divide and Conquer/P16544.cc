#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef set<IP> IPS;

int n;
IP a[100001];
int c[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>a[i].first;
    for (int i=0; i<n; ++i) cin>>a[i].second;
    sort(a, a+n);
    int acc=1;
    IPS b;
    for (int i=0; i<n; ++i) {
      int y=a[i].second;
      auto it=b.upper_bound({y,0});
      if (it==b.begin()) c[i]=1;
      else {
	--it;
	c[i]=c[it->second]+1;
	++it;
	while (it!=b.end() && c[it->second]<=c[i]) it=b.erase(it);
	acc=max(acc,c[i]);
      }
      b.insert({y, i});
    }
    cout<<acc<<endl;
  }
  return 0;
}





