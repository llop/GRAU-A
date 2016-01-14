#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;

int n, m;
double a[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>a[i];
    sort(a, a+n);
    m=0; 
    double mx=a[0]-1;
    for (int i=0; i<n; ++i) {
      if (a[i]>mx) {
	mx=a[i]+1;
	++m;
      }
    }
    cout<<m<<endl;
  }
  return 0;
}





