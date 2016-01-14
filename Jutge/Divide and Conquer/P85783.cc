#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef map<int, IP> IIPM;

struct Num {
  int v, a, b;
  inline friend bool operator<(const Num &x, const Num &y) {
    if (x.v==y.v) {
      if (x.a==y.a) return x.b>y.b;
      return x.a>y.a;
    }
    return x.v<y.v;
  }
};

int h, n, m, x, nn, mm, nnn, mmm;
int sol[4];
int b[1001];
int w[1001];
Num bb[5000001];
Num ww[5000001];


inline void treat_sol(const Num &b1, const Num &w1) {
  int sol2[4]={ b1.a, w1.a, b1.b, w1.b };
  int bt=-1;
  for (int i=0; bt==-1 && i<4; ++i) if (sol2[i]!=sol[i]) bt=sol2[i]>sol[i];
  if (bt==1) for (int i=0; i<4; ++i) sol[i]=sol2[i];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  while (getline(cin, s)) {
    h=atoi(s.c_str());
    n=m=nn=mm=nnn=mmm=0;
    getline(cin, s);
    istringstream s1(s);
    while (s1>>x) {
      for (int i=0; i<n; ++i) bb[nn++]={x+b[i], max(x,b[i]), min(x,b[i])};
      b[n++]=x;
    }
    getline(cin, s);
    istringstream s2(s);
    while (s2 >> x) {
      for (int i=0; i<m; ++i) ww[mm++]={x+w[i], max(x,w[i]), min(x,w[i])};
      w[m++]=x;
    }
    getline(cin, s);
    
    sort(bb, bb+nn);
    sort(ww, ww+mm);
    nnn=mmm=1;
    for (int i=1; i<nn; ++i) if (bb[nnn-1].v!=bb[i].v) bb[nnn++]=bb[i];
    for (int i=1; i<mm; ++i) if (ww[mmm-1].v!=ww[i].v) ww[mmm++]=ww[i];
    
    sol[0]=-1;
    int j=mmm-1;
    for (int i=0; j>=0 && i<nnn; ++i) {
      int k=h-bb[i].v;
      while (j>=0 && ww[j].v>k) --j;
      if (j>=0 && ww[j].v==k) treat_sol(bb[i], ww[j]);
    }
    
    if (sol[0]==-1) cout<<"no solution"<<endl;
    else cout<<sol[0]<<' '<<sol[1]<<' '<<sol[2]<<' '<<sol[3]<<endl;
  }
  return 0;
}







