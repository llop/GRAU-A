#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;
typedef queue<IP> IPQ;

const int MOVX[4] = { -1, 1, 0, 0 };
const int MOVY[4] = { 0, 0, -1, 1 };

int n, m;
char tbl[102][102];
int dis[102][102];
int cnt[102][102];
IP tc;

int dfs(int x, int y) {
  int &r=cnt[x][y];
  if (r==-1) {
    r = 0;
    for (int i=0; i<4; ++i) {
      int xx=x+MOVX[i];
      int yy=y+MOVY[i];
      if (tbl[xx][yy]!='#' && dis[xx][yy]<dis[x][y])
	r=max(r, dfs(xx, yy));
    }
    if (tbl[x][y]=='P') ++r;
  }
  return r;
}

inline void bfs() {
  dis[1][1]=0;
  IPQ que;
  que.push({1,1});
  while (!que.empty()) {
    int x=que.front().first;
    int y=que.front().second;
    que.pop();
    for (int i=0; i<4; ++i) {
      int xx=x+MOVX[i];
      int yy=y+MOVY[i];
      if (tbl[xx][yy]!='#' && dis[xx][yy]==-1) {
	dis[xx][yy]=dis[x][y]+1;
	que.push({xx,yy});
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n>>m) {
    tc={-1,-1};
    for (int i=0; i<=n+1; ++i) tbl[i][0]=tbl[i][m+1]='#';
    for (int i=0; i<=m+1; ++i) tbl[0][i]=tbl[n+1][i]='#';
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
      dis[i][j]=cnt[i][j]=-1;
      cin>>tbl[i][j];
      if (tbl[i][j]=='T') tc={i,j};
    }
    if (tc.first==-1) cout<<"El telecos ha fugit."<<endl;
    else {
      bfs();
      if (dis[tc.first][tc.second]==-1) cout<<"El telecos esta amagat."<<endl;
      else cout<<dis[tc.first][tc.second]<<' '<<dfs(tc.first, tc.second)<<endl;
    }
  }
  return 0;
}





