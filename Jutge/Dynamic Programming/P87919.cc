#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

int n, a;
int c[101];
int par[100001];

void print(int x) {
  if (!par[x]) cout<<x;
  else {
    cout<<x-par[x]<<',';
    print(par[x]);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>c[i];
    cin>>a;
    sort(c, c+n);
    for (int i=0; i<=a; ++i) par[i]=-1;
    par[0]=0;
    for (int i=0; i<n; ++i) for (int j=c[i]; j<=a; ++j) if (par[j-c[i]]!=-1) par[j]=j-c[i];
    if (par[a]==-1) cout<<-1<<endl;
    else {
      print(a);
      cout<<endl;
    }
  }
  return 0;
}


