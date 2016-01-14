#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> IV;
typedef pair<int, int> IP;
typedef vector<IP> IPV;
typedef vector<IPV> IPM;
typedef priority_queue<IP, vector<IP>, greater<IP>> IPQ;

int n, m, ini, fi;
IPM adj;
IV cos;
IV cam;

void dijkstra() {
  IPQ que;
  que.push(IP(0, ini));
  cos[ini] = 0;
  cam[ini] = 1;
  while (!que.empty()) {
    const IP &p = que.top();
    int d = p.first;
    int x = p.second;
    que.pop();
    if (d <= cos[x]) {
      for (const IP &yp : adj[x]) {
	int y = yp.second;
	if (d + yp.first < cos[y]) {
	  cos[y] = d + yp.first;
	  cam[y] = cam[x];
	  que.push(IP(cos[y], y));
	} else if (d + yp.first == cos[y]) {
	  cam[y] += cam[x];
	}
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  while (cin >> n >> m) {
    adj = IPM(n);
    cos = IV(n, 100000000);
    cam = IV(n, 1);
    for (int i = 0; i < m; ++i) {
      int x, y, z;
      cin >> x >> y >> z;
      adj[x].push_back(IP(z, y));
    }
    cin >> ini >> fi;
    dijkstra();
    if (100000000 == cos[fi]) {
      cout << "no path from " << ini << " to " << fi << endl;
    } else {
      cout << "cost " << cos[fi] << ", " << cam[fi] << " way(s)" << endl;
    }
  }
  return 0;
}
