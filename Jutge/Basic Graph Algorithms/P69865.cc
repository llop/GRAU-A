#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> P;
typedef vector<P> T;
typedef vector<vector<char> > G;

int mov_c_x[8] = { 2, 2, -2, -2, 1, -1, 1, -1 };
int mov_c_y[8] = { 1, -1, 1, -1, 2, 2, -2, -2 };
int mov_a_x[8] = { 1, 1, -1, -1 };
int mov_a_y[8] = { 1, -1, 1, -1 };

G read_graph(int n, int m, T &as, T &cs, int &count) {
	count = 0;
	G g(n, vector<char>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		char c;
		cin >> c;
		if (c == 'B') { c = '.'; as.push_back(P(i, j)); }
		else if (c == 'K') { c = '.'; cs.push_back(P(i, j)); }
		if (c != '.' && c != 'T') count++;
		g[i][j] = c;
	}
	return g;
}

bool valid_pos(int n, int m, int x, int y, const G &g) {
	return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != 'T';
}

int count_coins(int n, int m, G &g, T &as, T &cs, int count) {
	int s = 0;
	G g1 = g;
	queue<P> q;
	for (int i = 0; i < int(cs.size()); i++) { q.push(cs[i]); g1[cs[i].first][cs[i].second] = 'T'; }
	while (!q.empty()) {
		P p = q.front(); q.pop();
		for (int j = 0; j < 8; j++) {
			int x = p.first + mov_c_x[j];
			int y = p.second + mov_c_y[j];
			if (valid_pos(n, m, x, y, g1)) {
				q.push(P(x, y));
				if (g1[x][y] != '.') {
					s += g1[x][y] - 48;
					g[x][y] = '.';
					if (!(--count)) return s;
				}
				g1[x][y] = 'T';
			}
		}
	}
	g1 = g;
	for (int i = 0; i < int(as.size()); i++) { q.push(as[i]); g1[as[i].first][as[i].second] = 'T'; }
	while (!q.empty()) {
		P p = q.front(); q.pop();
		for (int j = 0; j < 4; j++) {
			int x = p.first + mov_a_x[j];
			int y = p.second + mov_a_y[j];
			if (valid_pos(n, m, x, y, g1)) {
				q.push(P(x, y));
				if (g1[x][y] != '.') {
					s += g1[x][y] - 48;
					g[x][y] = '.';
					if (!(--count)) return s;
				}
				g1[x][y] = 'T';
			}
		}
	}
	return s;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int count;
		T cs, as;
		G g = read_graph(n, m, as, cs, count);
		cout << count_coins(n, m, g, as, cs, count) << endl;
	}
	return 0;
}
