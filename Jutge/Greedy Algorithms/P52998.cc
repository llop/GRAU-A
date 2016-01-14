#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;

int n;
int d[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>d[i];
    sort(d, d+n);
    LL tim=0;
    LL acc=0;
    for (int i=0; i<n; ++i) {
      tim+=d[i];
      acc+=tim;
    }
    cout<<fixed<<setprecision(4)<<acc/(double)n<<endl;
  }
  return 0;
}





