#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;
typedef vector<double> DV;
typedef pair<double, int> DIP;
typedef priority_queue<DIP, vector<DIP>, greater<DIP>> DIPQ;
typedef vector<int> IV;
typedef vector<IV> IM;

int n, r;
DV f;
IM adj;

inline void build() {
  adj=IM(2*n);
  DIPQ que;
  for (int i=0; i<n; ++i) que.push({f[i], i});
  int idx=n;
  while ((int)que.size()>1) {
    DIP a=que.top();
    que.pop();
    DIP b=que.top();
    que.pop();
    adj[idx].push_back(a.second);
    adj[idx].push_back(b.second);
    que.push({a.first+b.first, idx});
    ++idx;
  }
  r=idx-1;
}

double dfs(int x, int len) {
  if (adj[x].empty()) return (f[x]/100.0)*len;
  return dfs(adj[x][0], len+1)+dfs(adj[x][1], len+1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>n;
  f=DV(n);
  for (int i=0; i<n; ++i) cin>>f[i];
  build();
  cout<<fixed<<setprecision(4)<<"nombre esperat de bits per lletra: "<<dfs(r, 0)<<endl;
  return 0;
}





