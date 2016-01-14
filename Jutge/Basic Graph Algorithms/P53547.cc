#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> IP;
typedef vector<IP> IPV;
typedef vector<int> IV;
typedef vector<IV> IM;
typedef queue<IP> IQ;

const int XMOV[4] = { -1, -1, 1, 1 };
const int YMOV[4] = { -1, 1, -1, 1 };

int t, n, m;
IM tbl;

bool valid(int x, int y) {
  return x >= 0 and x < n and y >= 0 and y < m; 
}

void bfs(int x, int y, int &cnt, int &pos) {
  cnt = tbl[x][y];
  pos = 1;
  tbl[x][y] = -1;
  IQ que;
  que.push(IP(x, y));
  while (!que.empty()) {
    x = que.front().first;
    y = que.front().second;
    que.pop();
    for (int i = 0; i < 4; ++i) {
      int nx = x + XMOV[i];
      int ny = y + YMOV[i];
      if (valid(nx, ny) and tbl[nx][ny] != -1) {
	cnt += tbl[nx][ny];
	++pos;
	tbl[nx][ny] = -1;
	que.push(IP(nx, ny));
      }
    }
  }
}

bool valid() {
  int last = 0;
  int c = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (tbl[i][j] != -1) {
	int cnt, pos;
	bfs(i, j, cnt, pos);
	if (cnt % pos) return false;
	if (c and last != (cnt / pos)) return false;
	last = cnt / pos;
	++c;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int tt = 1; tt <= t; ++tt) {
    cin >> n >> m;
    tbl = IM(n, IV(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	string s;
	cin >> s;
	if (s == "X") tbl[i][j] = -1;
	else tbl[i][j] = atoi(s.c_str());
      }
    }
    cout << "Case " << tt << ": " << (valid() ? "yes" : "no") << endl; 
  }
  return 0;
}
