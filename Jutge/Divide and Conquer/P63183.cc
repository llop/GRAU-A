#include <iostream>
#include <set>
using namespace std;

typedef long long LL;
typedef set<int> IS;

int n, x, tak;
string s;
IS fro, mid;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  tak=0;
  cin >> n;
  while (cin>>s>>x) {
    if (s[0]=='d') {
      if ((int)fro.size()<n) {
	fro.insert(x);
	tak += x;
      } else if (*fro.begin()<x) {
	mid.insert(*fro.begin());
	tak += x-(*fro.begin());
	fro.erase(fro.begin());
	fro.insert(x);
      } else {
	mid.insert(x);
      }
    } else {
      if (mid.count(x)) {
	mid.erase(x);
      } else {
	fro.erase(x);
	tak -= x;
	if (!mid.empty()) {
	  fro.insert(*(--mid.end()));
	  tak += *(--mid.end());
	  mid.erase(--mid.end());
	}
      }
    }
    cout<<tak<<endl;
  }
  return 0;
}





