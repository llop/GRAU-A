#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;
typedef vector<char> CharVec;
typedef vector<CharVec> CharMat;
typedef vector<bool> BoolVec;
typedef vector<BoolVec> BoolMat;

const int movx[] = { -1, -1, -1 };
const int movy[] = { -1, 0, 1 };
const int ksadd[] = { 1, 0, 1 };

inline void dynamic(const int x, const int y, const int l, const int w, const CharMat &map, IntMat &sol, BoolMat &found) {
  if (!found[x][y]) {
    int v = -1;
    for (int i = 0; i < 3; ++i) {
      const int nx = x + movx[i];
      const int ny = y + movy[i];
      if (nx >= 0 && nx < l && ny >= 0 && ny < w && map[nx][ny] != '*') {
	dynamic(nx, ny, l, w, map, sol, found);
	if (sol[nx][ny] != -1) {
	  const int nv = ksadd[i] + sol[nx][ny];
	  if (v < 0 || nv < v) {
	    v = nv;
	  }
	}
      }
    }
    if (v != -1) {
      if (map[x][y] == 'T') {
	v += 3;
      }
    }
    sol[x][y] = v;
    found[x][y] = true;
  }
}

int main() {
  int w, l;
  cin >> w >> l;
  CharMat map(l, CharVec(w));
  IntMat sol(l, IntVec(w, -1));
  BoolMat found(l, BoolVec(w, false));
  for (int i = 0; i < l; ++i) {
    for (int j = 0; j < w; ++j) {
      char c;
      cin >> c;
      map[i][j] = c;
    }
  }
  for (int i = 0; i < w; ++i) {
    if (map[0][i] == 'M') {
      sol[0][i] = 0;
    }
    found[0][i] = true;
  }
  const int lrow = l - 1;
  int min = -1;
  for (int i = 0; i < w; ++i) {
    if (map[lrow][i] != '*') {
      dynamic(lrow, i, l, w, map, sol, found);
      if (sol[lrow][i] != -1 && (min < 0 || sol[lrow][i] < min)) {
	min = sol[lrow][i];
      }
    }
  }
  if (min == -1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << min << endl;
  }
  return 0;
}


















