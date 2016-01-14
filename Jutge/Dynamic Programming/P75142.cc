#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

LL sti[26][26];
LL stir(int n, int k) {
  if (n<0 || k<0) return 0;
  return sti[n][k];
}

LL com[26][26];
LL comb(int n, int k) {
  if (n<0 || k<0) return 0;
  return com[n][k];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  // precalc stirling numbers of the first kind
  //memset(sti, 0, sizeof sti);
  //sti[1][1]=1;
  //for (int i=2; i<26; ++i) for(int j=1; j<26; ++j) sti[i][j]=sti[i-1][j-1]-(i-1)*sti[i-1][j];
  
  // precalc stirling numbers of the second kind
  memset(sti, 0, sizeof sti);
  sti[0][0]=sti[1][1]=1;
  for (int i=2; i<26; ++i) for(int j=1; j<26; ++j) sti[i][j]=sti[i-1][j-1]+j*sti[i-1][j];
  
  // precalc combinations
  memset(com, 0, sizeof com);
  com[0][0]=1;
  for (int i=1; i<26; ++i) {
    com[i][0]=com[i][i]=1;
    for (int j=1; j<i; ++j) com[i][j]=com[i-1][j]+com[i-1][j-1];
  }
  
  // solve
  int n, x, y;
  while (cin>>n>>x>>y) cout<<comb(n, y)*stir(n-y, x)<<'\n';
  return 0;
}





