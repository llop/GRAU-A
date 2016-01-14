#include <vector>
#include <iostream>
using namespace std;

typedef vector<char> ChrVec;
typedef vector<ChrVec> ChrMat;
typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

int xmk[] = { 1, 1, 0 };
int ymk[] = { 0, 1, 1 };
int mksiz = 3;
int xmh[] = { 2, 1 };
int ymh[] = { 1, 2 };
int mhsiz = 2;

int dynamic(const int x, const int y, const ChrMat &map, IntMat &sol) {
  if (sol[x][y] != -1) {
    return sol[x][y];
  }
  int r = 0;
  const char c = map[x][y];
  if (c == 'R') {
    for (int i = 0; i < mksiz; ++i) {
      const int nx = x - xmk[i];
      const int ny = y - ymk[i];
      if (nx < 0 || ny < 0) {
	++r;
      } else {
	r += dynamic(nx, ny, map, sol);
      }
    }
  } else if (c == 'C') {
    for (int i = 0; i < mhsiz; ++i) {
      const int nx = x - xmh[i];
      const int ny = y - ymh[i];
      if (nx < 0 || ny < 0) {
	++r;
      } else {
	r += dynamic(nx, ny, map, sol);
      }
    }
  }
  return sol[x][y] = r;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    ChrMat map(n, ChrVec(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	cin >> map[i][j];
      }
    }
    IntMat sol(n, IntVec(m, -1));
    cout << dynamic(n - 1, m - 1, map, sol) << endl;
  }
  return 0;
}


















