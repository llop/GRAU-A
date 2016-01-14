#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;

int d, n;
int f[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>d>>n) {
    LL tot=0;
    for (int i=0; i<n; ++i) {
      cin>>f[i];
      tot+=f[i];
    }
    sort(f, f+n);
    LL acc=0;
    LL tim=0;
    for (int i=n-1; i>=0 && f[i]; --i) {
      tim+=d;
      acc+=f[i]*tim;
    }
    cout<<fixed<<setprecision(4)<<acc/(double)tot<<endl;
  }
  return 0;
}





