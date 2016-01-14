#include <iostream>
#include <stack>
using namespace std;

typedef stack<int> IS;

int n;
int l[10001][2];
bool a[20001];
int la[20001];
int h[20001];
int e[10001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) {
      int x, y;
      cin>>x>>y;
      if (x>y) swap(x, y);
      l[i][0]=x;
      l[i][1]=y;
      a[x]=1;
      a[y]=0;
      la[x]=i;
      la[y]=i;
    }
    IS s;
    int next=1;
    for (int i=1; i<=2*n; ++i) {
      if (a[i]) {
	int y;
	if (s.empty()) {
	  y=next;
	  ++next;
	} else {
	  y=s.top();
	  s.pop();
	}
	h[i]=e[la[i]]=y;
      } else {
	int y=h[l[la[i]][0]];
	h[i]=y;
	s.push(y);
      }
    }
    cout<<next-1<<endl;
    //for (int i=0; i<n; ++i) cout<<i+1<<' '<<e[i]<<endl;
  }
  return 0;
}




