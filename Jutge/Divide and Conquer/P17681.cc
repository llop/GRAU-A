#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef long long LL;

const double PI = acos(-1);

int h1, m1, s1, h2, m2, s2;
char c;
double are[12*60*60];
double tbl[12*60*60*4];

inline double dis(double x1, double y1, double x2, double y2) {
  double x = abs(x1-x2);
  double y = abs(y1-y2);
  return sqrt(x*x+y*y);
}

inline double calc(int h, int m, int s) {
  double t1 = h*2*PI/12;
  double x1 = 3*sin(t1);
  double y1 = -3*cos(t1);
  double t2 = m*2*PI/60;
  double x2 = 4*sin(t2);
  double y2 = -4*cos(t2);
  double t3 = s*2*PI/60;
  double x3 = 5*sin(t3);
  double y3 = -5*cos(t3);
  if (abs(t1-t2)<0.000001 && abs(t1-t3)<0.000001) return 0;
  double a = dis(x1, y1, x2, y2);
  double b = dis(x1, y1, x3, y3);
  double d = dis(x2, y2, x3, y3);
  double sr = (a+b+d)/2;
  return sqrt(sr*(sr-a)*(sr-b)*(sr-d));
}

void build(int nod, int a, int b) {
  if (a>b) return;
  if (a==b) {
    tbl[nod] = are[a];
    return;
  }
  build(nod<<1, a, (a+b)>>1);
  build((nod<<1)+1, ((a+b)>>1)+1, b);
  tbl[nod] = max(tbl[nod<<1], tbl[(nod<<1)+1]);
}

double query(int nod, int a, int b, int i, int j) {
  if (a>b || a>j || b<i) return 0;
  if (a>=i && b<=j) return tbl[nod];
  double r1 = query(nod<<1, a, (a+b)>>1, i, j);
  double r2 = query((nod<<1)+1, ((a+b)>>1)+1, b, i, j);
  return max(r1, r2);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n = 12*60*60-1;
  for (int i=0; i<12; ++i) for (int j=0; j<60; ++j) for (int k=0; k<60; ++k) are[i*3600+j*60+k]=calc(i, j, k);
  build(1, 0, n-1);
  while (cin>>h1>>c>>m1>>c>>s1>>h2>>c>>m2>>c>>s2) {
    cout<<fixed<<setprecision(3)<<query(1, 0, n-1, h1*3600+m1*60+s1, h2*3600+m2*60+s2)<<'\n';
  }
  return 0;
}





