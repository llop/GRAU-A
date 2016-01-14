#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;

double m, f, d;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin >> m >> f >> d) {
    int l = 0;
    int r = 1e7+1;
    while (l<r) {
      int mid = (l+r)>>1;
      double me = m+mid*f;
      double bk = m*pow(1+d/100, mid);
      if (me<bk) r=mid;
      else l=mid+1;
    }
    cout << l << endl;
  }
  return 0;
}





