#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

inline void dynamic(const int x, const int y, const IntVec &art, const IntVec &bob, IntMat &sol) {
  if (sol[x][y] < 0) {
    int v = 0;
    const int x1 = x - 1;
    const int y1 = y - 1;
    if (art[x] == bob[y]) {
      dynamic(x1, y1, art, bob, sol);
      v = sol[x1][y1] + 1;
    } else {
      dynamic(x, y1, art, bob, sol);
      dynamic(x1, y, art, bob, sol);
      v = sol[x][y1];
      if (sol[x1][y] > v) {
	v = sol[x1][y];
      }
    }
    sol[x][y] = v;
  }
}

int main() {
  int m, n;
  while (cin >> m >> n) {
    const int fm = m;
    const int fn = n;
    ++m;
    ++n;
    IntVec art(m);
    IntVec bob(n);
    for (int i = 1; i < m; ++i) {
      cin >> art[i];
    }
    for (int i = 1; i < n; ++i) {
      cin >> bob[i];
    }
    IntMat sol(m, IntVec(n, -1));
    for (int i = 0; i < m; ++i) {
      sol[i][0] = 0;
    }
    for (int j = 1; j < n; ++j) {
      sol[0][j] = 0;
    }
    dynamic(fm, fn, art, bob, sol);
    cout << sol[fm][fn] << endl;
  }
  return 0;
}


















