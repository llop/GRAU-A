#include <vector>
#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s1, s2;
    cin >> s1 >> s2;
    int res = 0;
    for (int j = 0; j < 6; ++j) {
      int p;
      cin >> p;
      res ^= p;
    }
    cout << "Game #" << i << ": " << (res ? s1 : s2) << endl;
  }
  return 0;
}


















