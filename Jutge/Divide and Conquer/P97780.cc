#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

typedef long long LL;

double poly[5];

inline double eval(double x) {
  return poly[0]+poly[1]*x+poly[2]*x*x+poly[3]*x*x*x+poly[4]*x*x*x*x;
}

inline double uhoh(double z) {
  int x = z*100000;
  return x/100000.0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  int t=1;
  while (getline(cin, s)) {
    for (int i=0; i<5; ++i) poly[i]=0;
    istringstream ss(s);
    double c;
    int i;
    while (ss >> c >> i) poly[i]=c;
    bool b = eval(0)>eval(1);
    bool loop = 1;
    double l=0;
    double r=1;
    double z;
    while (loop) {
      z=(r+l)/2;
      double d1=eval(z);
      double d2=eval(z+0.0000000001);
      if (d1*d2<0 && r-l<0.00000001) loop = 0;
      else {
	if (b) d1=-d1;
	if (d1<0) l=z;
	else r=z;
      }
    }
    cout << "Case " << t++ << ": zero at " << fixed << setprecision(5) << uhoh(z) << '.' << endl;
  }
  return 0;
}





