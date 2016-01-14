#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> IV;
typedef set<int> IS;

int n;
int a[1000001];
int b[1000001];

int queues() {
  IS s;
  for (int i=0; i<n; ++i) {
    int idx=b[a[i]];
    auto it=s.upper_bound(idx);
    if (it==s.begin()) s.insert(it, idx);
    else {
      --it;
      s.erase(it);
      s.insert(idx);
    }
  }
  return s.size();
}

int stacks() {
  IS s;
  for (int i=0; i<n; ++i) {
    int idx=b[a[i]];
    auto it=s.upper_bound(idx);
    if (it==s.end()) s.insert(it, idx);
    else {
      s.erase(it);
      s.insert(idx);
    }
  }
  return s.size();
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t=1;
  while (cin>>n && n) {
    for (int i=0; i<n; ++i) cin>>a[i];
    for (int i=0; i<n; ++i) {
      int x;
      cin>>x;
      b[x]=i;
    }
    cout<<"Case "<<t<<": "<<queues()<<' '<<stacks()<<endl;
    ++t;
  }
  return 0;
}




