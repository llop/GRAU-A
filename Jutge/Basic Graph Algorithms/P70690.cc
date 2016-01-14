#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector <char> CV;
typedef vector < CV > CVV;
struct Pos{
	int x;
	int y;
};

const int XMOV[4] = { 1, 0, 0, -1 };
const int YMOV[4] = { 0, 1, -1, 0 };
int n, m;

bool BFS(CVV &mapa, int f, int c)
{
	queue <Pos> q;
	Pos p;
	p.x=f;p.y=c;
	q.push(p);//encuem coordenades origen
	mapa[f][c]='X'; //marquem posicio origen com a visitada
	while (not q.empty()){
		p = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i){
			int x=p.x+XMOV[i];
			int y=p.y+YMOV[i];
			if (x>=0 and x<n and y>=0 and y<m){
				if (mapa[x][y]=='t') return true;
				if (mapa[x][y]=='.'){
					mapa[x][y]='X'; //marquem posicio visitada
					//p.x=x;p.y=y;
					q.push({ x, y }); //encuem la nova posicio
				}
			}
		}
	}
	return false;
}

int main()
{
	cin >> n >> m;
	CVV mapa (n,CV(m));
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			cin >> mapa[i][j];
		}
	}
	int f, c;
	cin >> f >> c;
	--f;--c;
	if (BFS(mapa,f,c)) cout << "yes" << endl;
	else cout << "no" << endl;
}