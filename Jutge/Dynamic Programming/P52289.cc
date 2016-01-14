#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

string s1, s2;
int sol[501][501];

inline bool cmp(int i, int j, int len) {
  for (int k=0; k<len; ++k) {
    if (s1[i+k]<s1[j+k]) return 0;
    if (s1[i+k]>s1[j+k]) return 1;
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(sol, 0, sizeof(sol));
  while (cin>>s1>>s2) {
    int max=0;
    for (int i=1; i<=(int)s1.size(); ++i) {
      for (int j=1; j<=(int)s2.size(); ++j) {
	sol[i][j] = 0;
	if (s1[i-1]==s2[j-1]) {
	  sol[i][j]=sol[i-1][j-1]+1;
	  // sol found?
	  if (sol[i][j]>max) {
	    max=sol[i][j];
	  }
	}
      }
    }
    
    int k=-1;
    for (int i=1; i<=(int)s1.size(); ++i) {
      for (int j=1; j<=(int)s2.size(); ++j) {
	if (sol[i][j]==max && (k==-1 || cmp(k, i-max, max))) {
	  k=i-max;
	}
      }
    }
    for (int i=0; i<max; ++i) cout<<s1[i+k];
    cout<<'\n';
  }
  return 0;
}


