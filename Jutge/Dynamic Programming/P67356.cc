#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;

struct State {
  int h1, m1, h2, m2, p;
};
typedef queue<State> SQ;

string s1, s2;
int h1, h2, m1, m2, n1, n2, t;
IP a1[51];
IP a2[51];
int tbl[31][31][31][31][2];

inline bool win() {
  tbl[h1][m1][h2][m1][0]=t;
  SQ que;
  que.push({ h1, m1, h2, m2, 0 });
  while (!que.empty()) {
    State s=que.front();
    que.pop();
    if (s.p&1) {
      // player 2
      // don't use magic?
      int hh1=s.h1-1;
      if (!hh1) return 0;
      int mm2=min(m2, s.m2+5);
      int &rr=tbl[hh1][s.m1][s.h2][mm2][!s.p];
      if (rr<t) rr=t, que.push({ hh1, s.m1, s.h2, mm2, !s.p });
      // use magic
      for (int i=0; i<n2; ++i) if (a2[i].second<=s.m2) {
	int hh1=max(0, s.h1-a2[i].first);
	if (!hh1) return 0;
	int mm2=s.m2-a2[i].second;
	int &rr=tbl[hh1][s.m1][s.h2][mm2][!s.p];
	if (rr<t) rr=t, que.push({ hh1, s.m1, s.h2, mm2, !s.p });
      }
    } else {
      // player 1
      // don't use magic?
      int hh2=s.h2-1;
      if (!hh2) return 1;
      int mm1=min(m1, s.m1+5);
      int &rr=tbl[s.h1][mm1][hh2][s.m2][!s.p];
      if (rr<t) rr=t, que.push({ s.h1, mm1, hh2, s.m2, !s.p });
      // use magic
      for (int i=0; i<n1; ++i) if (a1[i].second<=s.m1) {
	int hh2=max(0, s.h2-a1[i].first);
	if (!hh2) return 1;
	int mm1=s.m1-a1[i].second;
	int &rr=tbl[s.h1][mm1][hh2][s.m2][!s.p];
	if (rr<t) rr=t, que.push({ s.h1, mm1, hh2, s.m2, !s.p });
      }
    }
  }
  // will never reach this!
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  for (int i=0; i<=30; ++i) for (int j=0; j<=30; ++j)
    for (int a=0; a<=30; ++a) for (int b=0; b<=30; ++b) for (int c=0; c<2; ++c)
      tbl[i][j][a][b][c]=0;
  t=1;
  while (cin>>s1>>h1>>m1>>s2>>h2>>m2) {
    cin>>n1;
    for (int i=0; i<n1; ++i) cin>>a1[i].first;
    for (int i=0; i<n1; ++i) cin>>a1[i].second;
    cin>>n2;
    for (int i=0; i<n2; ++i) cin>>a2[i].first;
    for (int i=0; i<n2; ++i) cin>>a2[i].second;
    cout<<(win()?s1:s2)<<endl;
    ++t;
  }
  return 0;
}





