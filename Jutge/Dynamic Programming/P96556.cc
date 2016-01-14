#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> IntVec;


int main() {
  string s;
  while (cin >> s) {
    int cnt = 0;
    const int ssiz = s.size();
    IntVec sol(ssiz, 1);
    for (int i = 1; i < ssiz; ++i) {
      for (int j = 0; j < i; ++j) {
	if (s[i] > s[j]) {
	  sol[i] += sol[j];
	  cnt += sol[j];
	}
      }
    }
    cout << cnt << endl;
  }
  return 0;
}


















