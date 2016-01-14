#include <vector>
#include <iostream>
using namespace std;

typedef vector<unsigned long long> LVec;

inline void dynamic(const int x, LVec &cat) {
  if (!cat[x]) {
    unsigned long long n = 0;
    for (int i = 1; i <= x; ++i) {
      const int x1 = i - 1;
      const int x2 = x - i;
      dynamic(x1, cat);
      dynamic(x2, cat);
      n += cat[x1] * cat[x2];
    }
    cat[x] = n;
  }
}

int main() {
  LVec cat(34, 0);
  cat[0] = 1;
  int x;
  while (cin >> x) {
    if (x % 2) {
      cout << 0 << endl;
    } else {
      dynamic(x / 2, cat);
      cout << cat[x / 2] << endl;
    }
  }
  return 0;
}


















