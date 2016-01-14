#include <iostream>
#include <vector>
using namespace std;

typedef vector<long long> IV;
typedef vector<IV> IM;

int n, m;
IM mat;

IM mult(const IM &m1, const IM &m2) {
  IM m3(2, IV(2));
  m3[0][0] = (m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0]) % m;
  m3[0][1] = (m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1]) % m;
  m3[1][0] = (m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0]) % m;
  m3[1][1] = (m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1]) % m;
  return m3;
}

IM mod_pow(const IM &m1, int x) {
  if (!x) return { { 1, 0 }, { 0 , 1 } };
  IM m2 = mod_pow(m1, x / 2);
  m2 = mult(m2, m2);
  if (x % 2) m2 = mult(m1, m2);
  return m2;
}

int main() {
  ios_base::sync_with_stdio(0);
  mat = IM(2, IV(2));
  while (cin >> mat[0][0] >> mat[0][1] >> mat[1][0] >> mat[1][1]) {
    cin >> n >> m;
    mat = mod_pow(mat, n);
    cout << mat[0][0] << ' ' << mat[0][1] << endl;
    cout << mat[1][0] << ' ' << mat[1][1] << endl;
    cout << "----------" << endl;
  }
  return 0;
}
