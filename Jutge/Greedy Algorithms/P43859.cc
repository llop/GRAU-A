#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> P;
typedef vector<vector<P> > G;

vector<int> cost_min(const G &g, int x) {
	int n = int(g.size());
	vector<bool> b(n, false);
	vector<int> v(n, -1);
	v[x] = 0;
	priority_queue<P, vector<P>, greater<P> > q;
	q.push(P(0, x));
	while (!q.empty()) {
		x = q.top().second;
		q.pop();
		if (!b[x]) {
			b[x] = true;
			for (int i = 0; i < int(g[x].size()); i++) {
				int y = g[x][i].first;
				int d = g[x][i].second;
				if (v[y] == -1 || v[y] > v[x] + d) {
					v[y] = v[x] + d;
					q.push(P(v[y], y));
				}
			}
		}
	}
	return v;
}

int main() {
	int n, m, u, v, c, x, y;
	while (cin >> n >> m) {
		G g(n);
		for (int i = 0; i < m; i++) {
			cin >> u >> v >> c;
			g[u].push_back(P(v, c));
		}
		cin >> x >> y;
		vector<int> d = cost_min(g, x);
		if (d[y] != -1) cout << d[y] << endl;
		else cout << "no path from " << x << " to " << y << endl;
	}
	return 0;
}
