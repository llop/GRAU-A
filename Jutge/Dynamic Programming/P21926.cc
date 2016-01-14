#include <vector>
#include <iostream>
using namespace std;


typedef vector<int> IntVec;


inline void dynamic(const int idx, const int mod, IntVec &sol) {
  if (sol[idx] < 0) {
    dynamic(idx - 1, mod, sol);
    dynamic(idx - 2, mod, sol);
    sol[idx] = (sol[idx - 1] + sol[idx - 2]) % mod;
  }
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    const int ssiz = n > 1 ? n + 1 : 2;
    IntVec sol(ssiz, -1);
    sol[0] = 0;
    sol[1] = 1;
    dynamic(n, m, sol);
    cout << sol[n] << endl;
  }
  return 0;
}


















