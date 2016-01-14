#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

struct Zam {
  double x, y, r;
  int d;
};
typedef vector<Zam> ZV;
typedef queue<int> ZQ;

inline double dis(double x, double y) {
  return sqrt(x * x + y * y);
}

inline bool can_reach(const Zam &a, const Zam &b, double r) {
  double d = dis(a.x - b.x, a.y - b.y);
  return r >= d - a.r - b.r;
}

int n;
double d;
ZV vec;
ZQ que;

int main() {
  ios_base::sync_with_stdio(0);
  while (cin >> n >> d) {
    vec = ZV(n);
    for (int i = 0; i < n; ++i) {
      cin >> vec[i].x >> vec[i].y >> vec[i].r;
      vec[i].d = -1;
    }
    vec[0].d = 0;
    
    que.push(0);
    while (not que.empty()) {
      int idx = que.front();
      que.pop();
      for (int i = 1; i < n; ++i) {
	if (vec[i].d == -1) {
	  if (can_reach(vec[idx], vec[i], d)) {
	    vec[i].d = vec[idx].d + 1;
	    que.push(i);
	  }
	}
      }
    }
    
    if (vec[n - 1].d == -1) cout << "Xof!" << endl;
    else cout << vec[n - 1].d << endl;
  }
  return 0;
}
