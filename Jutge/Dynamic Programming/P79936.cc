#include <vector>
#include <sstream>
#include <iostream>
using namespace std;


typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

inline void dynamic() {
  
}

int main() {
  int w, h, c;
  cin >> w >> h >> c;
  const int nh = h + c;
  const int nw = w + c;
  IntMat mdat(nh, IntVec(nw, 0));
  IntMat mrow(nh, IntVec(nw, 0));
  IntMat mcol(nh, IntVec(nw, 0));
  for (int i = c; i < nh; ++i) {
    for (int j = c; j < nw; ++j) {
      int val;
      cin >> val;
      mdat[i][j] = val;
      mrow[i][j] = val + mrow[i][j - 1] - mdat[i][j - c];
    }
  }
  int x, y;
  x = y = 2 * c - 1;
  for (int i = c; i < nh; ++i) {
    for (int j = c; j < nw; ++j) {
      mcol[i][j] = mrow[i][j] + mcol[i - 1][j] - mrow[i - c][j];
      if (mcol[i][j] > mcol[x][y]) {
	x = i;
	y = j;
      }
    }
  }
  cout << x - 2 * c + 1 << ' ' << y - 2 * c + 1 << endl;
  return 0;
}


















