#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long LL;

struct Song {
  double v;
  int f, d;
};

int n;
Song fd[100001];

inline bool cmp(const Song &a, const Song &b) {
  return a.v>b.v;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    LL tot=0;
    for (int i=0; i<n; ++i) {
      cin>>fd[i].f>>fd[i].d;
      fd[i].v=fd[i].f/(double)fd[i].d;
      tot+=fd[i].f;
    }
    sort(fd, fd+n, cmp);
    LL acc=0;
    LL tim=0;
    for (int i=0; i<n; ++i) {
      tim+=fd[i].d;
      acc+=fd[i].f*tim;
    }
    cout<<fixed<<setprecision(4)<<acc/(double)tot<<'\n';
  }
  return 0;
}





