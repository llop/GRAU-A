#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> IV;

int n, c;
IV a;

void merge(int lef, int m, int rig) {
  int l = rig - lef + 1;
  IV t(l);
  int i = lef;
  int j = m + 1;
  int k = 0;
  while (i <= m && j <= rig) {
    if (a[i] > a[j]) {
      c += (m - i + 1);
      t[k] = a[j++];
    } else t[k] = a[i++];
    k++;
  }
  while (i <= m) t[k++] = a[i++];
  while (j <= rig) t[k++] = a[j++];
  for (int n = 0; n < l; n++) a[lef + n] = t[n];
}

void merge_sort(int lef, int rig) {
  if (lef < rig) {
    int m = (lef + rig) / 2;
    merge_sort(lef, m);
    merge_sort(m + 1, rig);
    merge(lef, m, rig);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  while (cin >> n) {
    a = IV(n);
    c = 0;
    for (int i = 0; i < n; ++i) cin >> a[i];
    merge_sort(0, n - 1);
    cout << c << endl;
  }
  return 0;
}
