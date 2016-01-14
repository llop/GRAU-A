#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> CV;
typedef vector<CV> CM;
typedef pair<int, int> IP;
typedef queue<IP> IPQ;

const int XMOV[4] = { 1, 0, 0, -1 };
const int YMOV[4] = { 0, 1, -1, 0 };

int n, m, f, c, cnt;
CM tbl;
IPQ que;

inline bool valid(int x, int y) {
  return x >= 0 and x < n and y >= 0 and y < m;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  tbl = CM(n, CV(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> tbl[i][j];
    }
  }
  cin >> f >> c;
  --f;
  --c;
  tbl[f][c] = 'X';
  
  cnt = 0;
  que.push(IP(f, c));
  // BFS
  while (not que.empty()) {
    const IP &p = que.front();
    int x = p.first;
    int y = p.second;
    que.pop();
    
    for (int i = 0; i < 4; ++i) {
      int a = x + XMOV[i];
      int b = y + YMOV[i];
      if (valid(a, b) && tbl[a][b] != 'X') {
	if (tbl[a][b] == 't') ++cnt;
	tbl[a][b] = 'X';  // macar posicio com visitada
	que.push(IP(a, b));
      }
    }
    
  }
  
  cout << cnt << endl;
  
  return 0;
}
