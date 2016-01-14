#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> IP;

int n;
IP a[100001];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>n) {
    for (int i=0; i<n; ++i) cin>>a[i].second>>a[i].first;
    sort(a, a+n);
    int acc=1;
    int j=0;
    for (int i=1; i<n; ++i) {
      if (a[i].second>a[j].first) {
	++acc;
	j=i;
      }
    }
    cout<<acc<<endl;
  }
  return 0;
}




   
// 100 700  
// 200 300 
// 400 1100 
// 500 600 
// 800 1000
// 900 1400
// 1200 1300  

// 100 700  -> cnt=1 ---
// 200 300  -> cnt=1
// 400 1100 -> cnt=2 ---
// 500 600  -> cnt=2
// 800 1000 -> cnt=3
// 900 1400 -> cnt=3
// 1200 1300  



















