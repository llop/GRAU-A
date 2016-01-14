#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef vector<IP> IPV;

int r, c, l, ini, fi;
char ice[16][16];
LL tbl[16][16][16][2];


inline bool v(int x, int y) {
  return ice[x][y]!='O';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>r>>c>>l && (r || c || l)) {
    IPV os;
    for (int i=0; i<r; ++i) for (int j=0; j<c; ++j) {
      cin>>ice[i][j];
      if (ice[i][j]=='O') os.push_back({i, j});
      if (ice[i][j]=='D') ini=j;
      if (ice[i][j]=='P') fi=j;
    }
    for (const IP &p : os) 
      for (int i=max(0,p.first-2); i<=min(r-1,p.first+2); ++i)
	for (int j=max(0,p.second-2); j<=min(c-1,p.second+2); ++j)
	  ice[i][j]='O';
	
    memset(tbl, 0, sizeof tbl);
    for (int i=0; i<r && v(i, ini); ++i) tbl[i][ini][0][0]=1;
    for (int k=1; k<=l; ++k) {
      for (int i=0; i<r; ++i) {
	for (int j=0; j<c; ++j) if (v(i, j)) {
	  int jj=j-1;
	  while (jj>=0 && v(i, jj)) {
	    tbl[i][j][k][1]+=tbl[i][jj][k-1][0];
	    --jj;
	  }
	  jj=j+1;
	  while (jj<c && v(i, jj)) {
	    tbl[i][j][k][1]+=tbl[i][jj][k-1][0];
	    ++jj;
	  }
	  int ii=i+1;
	  while (ii<r && v(ii, j)) {
	    tbl[ii][j][k][0]+=tbl[i][j][k][1];
	    ++ii;
	  }
	}
      }
    }
    
    LL acc=0;
    for (int k=0; k<=l; ++k) acc+=tbl[r-1][fi][k][0]+tbl[r-1][fi][k][1];
    if (!acc) cout<<"Good bye, Professor Dyer!"<<endl;
    else cout<<acc<<endl;
  }
  return 0;
}





