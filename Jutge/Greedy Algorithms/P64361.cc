#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef pair<double, int> DIP;

int n, c;
IP pro[1001];
DIP gap[1001];

inline double calc(double m) {
  double t=0;
  for (int i=0; i<n-1; ++i) {
    double tn=gap[i].first;
    int idx=gap[i].second;
    int d=pro[idx].first-pro[idx-1].first;
    if (tn>0) {
      double ma=min(d*tn, m);
      double x=ma/(d*tn);
      t+=d*(6-5*x);
      m-=ma;
    } else t+=d;
  }
  return 60*t;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>n;
  for (int i=0; i<n; ++i) cin>>pro[i].first>>pro[i].second;
  // precalc
  for (int i=1; i<n; ++i) {
    double d=pro[i].first-pro[i-1].first;
    double h=(pro[i].second-pro[i-1].second)/1000.0;
    gap[i-1]={h/d, i};
  }
  sort(gap, gap+n-1);
  // cyclists queries
  cin>>c;
  for (int i=0; i<c; ++i) {
    double ma;
    int h, m, s;
    cin>>ma>>h>>m>>s;
    int t=h*3600+m*60+s;
    cout<<(calc(ma)>t?"SHOOT":"PASS")<<endl;
  }
  return 0;
}