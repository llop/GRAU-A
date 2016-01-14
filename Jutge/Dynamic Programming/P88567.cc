#include <vector>
#include <sstream>
#include <iostream>
using namespace std;


typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

int main() {
  // cache letters array
  const int lsiz = ('Z' - 'A') + 1;
  IntVec letters(lsiz);
  letters[0] = 1;
  for (int i = 1; i < lsiz; ++i) {
    letters[i] = i + 1 + letters[i - 1];
  }
  // read lines
  IntMat msol;
  string s;
  int row = 0;
  while (getline(cin, s)) {
    IntVec vsol;
    IntVec nsol;
    const int ssiz = s.size();
    for (int i = 0; i < ssiz; ++i) {
      const char c = s[i];
      int val = letters[c - 'A'];
      int nval = val;
      if (row) {
	val += msol[row - 1][i];
      }
      nsol.push_back(nval);
      if (i) {
	cout << ' ';
	nsol[i] += nsol[i - 1];
	val += nsol[i - 1];
      }
      vsol.push_back(val);
      cout << val;
    }
    cout << endl;
    msol.push_back(vsol);
    ++row;
  }
  return 0;
}


















