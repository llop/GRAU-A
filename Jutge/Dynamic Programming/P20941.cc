#include <iostream>
using namespace std;

typedef long long LL;

const int MAXHEIGHT = 6;

LL num[MAXHEIGHT];      // num[i] = nombre d'arbres AVL d'alçada i
LL tot[MAXHEIGHT + 1];  // tot[i] = acumulat del # d'arbres fins alçada i

LL avl(int &h) {
  char c;
  cin >> c;
  if (c == '0') {
    // es una fulla
    return 0;
  }
  // llegir en preordre
  int hlef, hrig;
  hlef = hrig = 0;
  LL rlef = avl(hlef);
  LL rrig = avl(hrig);
  
  h = (hlef > hrig ? hlef : hrig) + 1;
  
  const int nh = h - 1;
  const int nnh = h - 2;
  
  if (hlef == nnh) {
    // fulla esquerra es 1 més baixa que la dreta
    return rlef * num[nh] + rrig;
  }
  return num[nnh] * num[nh] + rlef * (num[nnh] + num[nh]) + rrig + (hrig == nnh ? 0 : num[nnh]);
}

int main() {
  // precalc
  tot[0] = 0;
  num[0] = num[1] = tot[1] = 1;
  tot[2] = 2;
  for (int i = 2; i < MAXHEIGHT; ++i) {
    const int ni = i - 1;
    const int nni = i - 2;
    num[i] = num[ni] * (2 * num[nni] + num[ni]);
	tot[i + 1] = tot[i] + num[i];
	// cout << i << ' ' << num[i] << ' ' << tot[i] << endl;
  }
  // 
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int h = 0;
    LL rank = avl(h) + tot[h] + 1;
	cout << rank << endl;
  }
  return 0;
}