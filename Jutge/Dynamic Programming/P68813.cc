#include <vector>
#include <iostream>
using namespace std;

typedef long long L;
typedef vector<L> LVec;
typedef vector<LVec> LMat;

inline void dynamic(const int x, const int y, LMat &sol) {
  if (sol[x][y] < 0) {
    L n = 0;
    // parenthesis
    const int x1 = x - 2;
    dynamic(x1, y, sol);
    n += sol[x1][y];
    // minus
    const int x2 = x - 5;
    for (int i = 0; i <= x2; ++i) {
      const int x21 = i;
      const int x22 = x2 - i;
      dynamic(x21, y, sol);
      dynamic(x22, y, sol);
      n += sol[x21][y] * sol[x22][y];
    }
    sol[x][y] = n;
  }
}

int main() {
  LMat sol(26, LVec(26, -1));
  for (int i = 0; i < 26; ++i) {
    sol[0][i] = 0;
    sol[1][i] = i;
  }
  int x, y;
  while (cin >> x >> y) {
    dynamic(x, y, sol);
    cout << sol[x][y] << endl;
  }
  return 0;
}


















