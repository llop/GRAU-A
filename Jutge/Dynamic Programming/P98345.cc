#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> IntVec;
typedef vector<IntVec> IntMat;

// variant de l'edit distance
int main() {
  string s;
  while (cin >> s) {
    const int n = s.size();
    IntMat sol(n, IntVec(n, 0));
    // primer calcular el cost de palindromitzar una lletra amb la del costat,
    // després amb la que està 2 més enllà, després 3, ...
    // i sempre anar pillant el mínim cost
    for (int k = 1; k < n; ++k) {
      int i = 0;
      int j = k;
      while (j < n) {
	if (s[i] == s[j]) {
	  sol[i][j] = sol[i + 1][j - 1];
	} else {
	  sol[i][j] = (sol[i][j - 1] < sol[i + 1][j] ? sol[i][j - 1] : sol[i + 1][j]) + 1;
	}
	++i;
	++j;
      }
    }
    if (sol[0][n - 1]) {
      cout << sol[0][n - 1] << endl;
    } else {
      cout << "Passes the Dislex-Wonga test" << endl;
    }
  }
  return 0;
}


















