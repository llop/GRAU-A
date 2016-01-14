#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef vector<int> IV;
typedef pair<int, int> IP;
typedef vector<IP> IPV;
typedef vector<IPV> G;

// struct que representa una arista ()
struct E {
  int w;     // peso de la arista
  int x, y;  // vertices de la arista
  
  // operador menor-que
  // se necesita para la priority queue, que debe ordenar por el peso 'w'
  inline friend bool operator<(const E &a, const E &b) {
    return a.w > b.w;
  }
};
typedef priority_queue<E> EQ;

int n, m;
G g;     // grafo: lista de adyacencias
IV par;  // array de padres del MST
IV wei;  // array de pesos del MST


void prim() {
  // inicializar el array de padres
  // al principio, ningun vertice tiene padre (indicado con -1)
  par = IV(g.size(), -1);
  wei = IV(g.size());
  // inicializar la cola de prioridad
  // añadimos una arista "fantasma" que une el vertice origen consigo mismo
  // asi conseguimos que este vertice origen sea la raiz del MST
  EQ que;
  que.push({ 0, 0, 0 });
  while (!que.empty()) {
    // la arista que sacamos es la de menor peso de todas las que hemos examinado
    const E &e = que.top();
    int w = e.w;
    int x = e.x;
    int y = e.y;
    que.pop();
    if (par[y] == -1) {
      // si el vertice 'y' no tenia padre, se lo asignamos ahora
      // luego añadimos a la cola todas las aristas que conectan con 'y'
      par[y] = x;
      wei[y] = w;
      for (const IP &a : g[y]) {
	int w = a.first;
	int z = a.second;
	que.push({ w, y, z });
      }
    }
  }
}

inline void add_edge(int x, int y, int w) {
  g[x].push_back(IP(w, y));
  g[y].push_back(IP(w, x));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n>>m) {
    g=G(n);
    for (int i=0; i<m; ++i) {
      int x, y, w;
      cin>>x>>y>>w;
      --x, --y;
      add_edge(x, y, w);
    }
    prim();
    int acc=0;
    for (int i = 1; i < (int)g.size(); ++i) acc+=wei[i];
    cout<<acc<<endl;
  }
  return 0;
}





