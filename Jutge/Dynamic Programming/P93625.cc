#include <vector>
#include <iostream>
using namespace std;


typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;


inline void dynamic(const int n, const int k, IntMat &sol) {
  if (sol[n][k] < 0) {
    const int nn = n - 1;
    const int kk = k - 1;
    dynamic(nn, k, sol);
    dynamic(nn, kk, sol);
    sol[n][k] = sol[nn][k] + sol[nn][kk];
  }
}

int main() {
  IntMat msol;
  for (int i = 0; i < 31; ++i) {
    const int vsiz = i + 1;
    IntVec vsol(vsiz, -1);
    vsol[0] = 1;
    vsol[i] = 1;
    msol.push_back(vsol);
  }
  int n, k;
  while (cin >> n >> k) {    
    dynamic(n, k, msol);
    cout << msol[n][k] << endl;
  }
  return 0;
}


















