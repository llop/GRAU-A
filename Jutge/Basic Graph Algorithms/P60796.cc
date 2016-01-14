#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char> > G;

int mov_x[] = { 1, -1, 0, 0 };
int mov_y[] = { 0, 0, 1, -1 };

bool arriba_tresor(int x, int y, G &g, int &c) {
	if (g[x][y] == 'X') return false;
	else if (g[x][y] == 't') { c = 0; return true; }
	g[x][y] = 'X';
	queue<pair<pair<int, int>, int> > q;
	q.push(make_pair(make_pair(x, y), 0));
	while (!q.empty()) {
		pair<pair<int, int>, int> p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			x = p.first.first + mov_x[i];
			y = p.first.second + mov_y[i];
			if (g[x][y] == 't') {
				c = p.second + 1;
				return true;
			} else if (g[x][y] == '.') {
				g[x][y] = 'X';
				q.push(make_pair(make_pair(x, y), p.second + 1));
			}
		}
	}
	return false;
}

int main() {
	int n, m, x, y, c;
	cin >> n >> m;
	G g(n + 2, vector<char>(m + 2, 'X'));
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> g[i][j];
	cin >> x >> y;
	if (arriba_tresor(x, y, g, c)) cout << "distancia minima: " << c << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
	return 0;
}
