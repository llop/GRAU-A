#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>

using namespace std;

const double infinit = numeric_limits<double>::infinity();
typedef pair <int,int> IP; //guardarem distancia-vertex desti
typedef vector <IP> VP;
typedef vector<VP> G;

int n,m,x,y;

void llegir_graf(G &g)
{
  for (int i=0; i<m; ++i){
    int u,v,c;
    cin >> u >> v >> c;
    g[u].push_back(pair<int,int>(c,v));
  }
}

vector <int> dijkstra(G & graf,vector<double> &dist){
  int n=graf.size();
  vector <int> prev (n,-1);
  dist[x]=0;
  vector<bool> visitat(n,false);
  priority_queue<IP,VP,greater<IP> > q;
  q.push({0,x});

  while(not q.empty()){
    int actual=q.top().second; //vertex que estem mirant
    q.pop();

    if (not visitat[actual]){ //si no l'hem visitat...
      visitat[actual]=true; //marquem com a visitat

      for (int i = 0; i < (int)graf[actual].size(); ++i){
        int seg=graf[actual][i].second; //seg=següent vertex
        int ndist=graf[actual][i].first; //nova dist=distancia de vertex actual al següent
        
        if (dist[seg]>dist[actual]+ndist){ //si distancia a següent > dist a l'actual + cost arc...
          dist[seg]=dist[actual]+ndist; //actualitza amb cami mes curt
          prev[seg]=actual;
          q.push({dist[seg],seg}); //encua
        }
      }
    }
  }
  return prev;
}

int main()
{
  while(cin >> n >> m){
//cout << INT_MAX << endl;
    G graf (n); //vector de llistes de vertex desti+distancia
    vector <double> dist (n,infinit);
    llegir_graf(graf);
    cin >> x >> y;
    vector <int> cami = dijkstra(graf,dist);
    if (x == y) cout << x << endl;
    else if (cami[y]==-1) cout << "no path from " << x << " to " << y << endl;
    else {
      stack <int> s;
      int i=y;
      while (i!=-1){
        s.push(i);
        i=cami[i];
      }
      while (s.size()>1){
        cout << s.top() << ' ';
        s.pop();
      }
      cout << s.top();
      s.pop();
      cout << endl;
    }
  }
}
