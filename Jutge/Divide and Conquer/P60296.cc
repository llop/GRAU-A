#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef long long LL;
typedef set<string> SS;
typedef map<string, int> SIM;
typedef pair<int, string> ISP;
typedef vector<ISP> ISPV;

string s, p1, p2;
SS logg;
SIM pnt;
ISPV rnk;

bool cmp(const ISP &a, const ISP &b) {
  if (a.first==b.first) return a.second<b.second;
  return a.first>b.first;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>s) {
    if ((int)s.size()==5) {
      cin>>p1;
      if (!logg.count(p1)) {
	if (!pnt.count(p1)) pnt[p1]=1200;
	logg.insert(p1);
      }
    } else if ((int)s.size()==6) {
      cin>>p1;
      logg.erase(p1);
    } else if ((int)s.size()==4) {
      cin>>p1>>p2;
      if (!logg.count(p1) || !logg.count(p2)) cout<<"jugador(s) no connectat(s)"<<endl;
      else {
	pnt[p1] += 10;
	pnt[p2] = max(1200, pnt[p2]-10);
      }
    } else {
      cin>>p1;
      cout<<p1<<' '<<pnt[p1]<<endl;
    }
  }
  for (auto it : pnt) rnk.push_back({it.second,it.first});
  sort(rnk.begin(), rnk.end(), cmp);
  cout<<"\nRANKING"<<endl;
  for (const ISP &p : rnk) cout<<p.second<<' '<<p.first<<endl;
  return 0;
}





