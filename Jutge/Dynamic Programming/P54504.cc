#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

const int suits[] = { 1, 5, 8, 14 };

inline void dynamic(const int x, const int y, IntMat &sol) {
  if (sol[y][x] < 0) {
    int v = -1;
    const int x1 = x - suits[y];
    if (x1 >= 0) {
      dynamic(x1, y, sol);
      v = sol[y][x1] + 1;
    }
    const int y1 = y - 1;
    if (y1 >= 0) {
      dynamic(x, y1, sol);
      if (v == -1 || sol[y1][x] < v) {
	v = sol[y1][x];
      }
    }
    sol[y][x] = v == -1 ? 0 : v;
  }
}

int main() {
  IntMat sol(4, IntVec(500001, -1));
  for (int i = 0; i < 4; ++i) {
    sol[i][0] = 0;
  }
  int n;
  cin >> n;
  while (n != -1) {
    dynamic(n, 3, sol);
    cout << sol[3][n] << endl;
    cin >> n;
  }
  return 0;
}


















