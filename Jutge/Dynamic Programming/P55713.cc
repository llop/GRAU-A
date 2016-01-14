#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<LL, int> LIP;
typedef vector<LIP> LIPV;
typedef vector<int> IV;
typedef priority_queue<LIP, LIPV, greater<LIP>> LIPQ;

int t, n, m, k, q;
LIPV adj[100001];

LL dis[100001];
int cit[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>t;
  for (int i=0; i<t; ++i) {
    cin>>n>>m;
    for (int j=0; j<n; ++j) {
      adj[j].clear();
      dis[j]=-1;
    }
    if (i) cout<<endl;
    cout<<"Case #"<<i+1<<endl;
    for (int j=0; j<m; ++j) {
      int u, v;
      LL d;
      cin>>u>>v>>d;
      adj[u].push_back({d, v});
      adj[v].push_back({d, u});
    }
    LIPQ que;
    cin>>k;
    for (int j=0; j<k; ++j) {
      int x;
      cin>>x;
      dis[x]=0;
      cit[x]=x;
      que.push({0, x});
    }
    while (!que.empty()) {
      int x=que.top().second;
      LL d=que.top().first;
      que.pop();
      if (d<=dis[x]) {
	for (const LIP &p : adj[x]) {
	  if (dis[p.second]==-1 || dis[p.second]>d+p.first) {
	    dis[p.second]=d+p.first;
	    cit[p.second]=cit[x];
	    que.push({dis[p.second], p.second});
	  } else if (dis[p.second]==d+p.first && cit[p.second]>cit[x]) {
	    cit[p.second]=cit[x];
	    que.push({dis[p.second], p.second});
	  }
	}
      }
    }
    cin>>q;
    for (int j=0; j<q; ++j) {
      int x;
      cin>>x;
      cout<<"To get to "<<x<<", distance "<<dis[x]<<", from city "<<cit[x]<<"."<<endl;
    }
  }
  return 0;
}





