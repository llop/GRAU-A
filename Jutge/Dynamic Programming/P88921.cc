#include <vector>
#include <iostream>
using namespace std;


typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;
typedef vector<bool> BoolVec;
typedef vector<BoolVec> BoolMat;


inline void dynamic(const int x, const int y, const BoolMat &avail, IntMat &sol) {
  if (sol[x][y] < 0) {
    int v = 0;
    const int nx = x - 1;
    if (nx >= 0 && avail[nx][y]) {
      dynamic(nx, y, avail, sol);
      v += sol[nx][y];
    }
    const int ny = y - 1;
    if (ny >= 0 && avail[x][ny]) {
      dynamic(x, ny, avail, sol);
      v += sol[x][ny];
    }
    if (v > 1000000) {
      v = 1000000;
    }
    sol[x][y] = v;
  }
}

int main() {
  int x, y;
  cin >> x >> y;
  while (x || y) {
    BoolMat avail(x, BoolVec(y));
    IntMat sol(x, IntVec(y, -1));
    sol[0][0] = 1;
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
	char c;
	cin >> c;
	avail[i][j] = c == '.';
      }
    }
    dynamic(x - 1, y - 1, avail, sol);
    if (sol[x - 1][y - 1] >= 1000000) {
      cout << "too many paths" << endl;
    } else {
      cout << sol[x - 1][y - 1] << endl;
    }
    cin >> x >> y;
  }
  return 0;
}


















