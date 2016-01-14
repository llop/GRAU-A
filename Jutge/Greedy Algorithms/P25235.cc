#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<LL, int> IP;
typedef vector<IP> IPV;
typedef priority_queue<IP> IPQ;

int n, m, x, y;
IPV adj[100001];
int dis[100001];
int stp[100001];

inline void dijkstra() {
  // distancia vertex inicial = 0; impossible arribar-hi; 0 passos
  dis[x] = 0;
  stp[x] = 0;
  // iniciar algoritme
  IPQ que;
  que.push(IP(0, x));
  while (!que.empty()) {
    const IP &p = que.top();
    LL d = -p.first;
    int u = p.second;
    que.pop();
    if (dis[u] >= d) {
      for (const IP &a : adj[u]) {
	int distancia = a.first;
	int v = a.second;
	if (dis[v] == -1 || (dis[v] > distancia + d) || (dis[v] == distancia + d && stp[v] > stp[u] + 1)) {
	  dis[v] = distancia + d;
	  stp[v] = stp[u] + 1;
	  que.push(IP(-dis[v], v));
	}
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  while (cin >> n >> m) {
    // reset distancies i adj
    memset(dis, -1, sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
      adj[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      int c;
      cin >> u >> v >> c;
      adj[u].push_back(IP(c, v));
    }
    cin >> x >> y;
    
    // correr dijkstra
    dijkstra();
    if (dis[y] != -1) {
      cout << "cost " << dis[y] << ", " << stp[y] << " step(s)" << endl;
    } else {
      cout << "no path from " << x << " to " << y << endl;
    }
  }
  return 0;
}


