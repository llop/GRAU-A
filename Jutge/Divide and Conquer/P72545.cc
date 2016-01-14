#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
typedef vector<int> IV;

// returns the k-th smallest element contained in v1 and v2, taking into account repeated elements
// precondition: v1 and v2 are sorted in nondecreasing order, 1 <= k <= v1.size()+v2.size()
int select(int k, const IV &v1, const IV &v2) {
  // handle one of the arrays being empty + 1st elemet case
  if (v1.empty()) return v2[k-1];
  if (v2.empty()) return v1[k-1];
  if (k==1) return min(v1[0], v2[0]);
  
  const IV &a=v1.size()<=v2.size()?v1:v2;
  const IV &b=v1.size()<=v2.size()?v2:v1;
  
  int l=max(0, k-(int)b.size());
  int r=min((int)a.size(), k);
  
  while (1) {
    int na=(l+r)>>1;
    int i=na-1;
    int j=k-na-1;
    if (na && (j==-1 || a[i]>=b[j])) {
      if (j+1==(int)b.size() || a[i]<=b[j+1]) return a[i];
      else r = na;
    } else {
      if (i+1==(int)a.size() || a[i+1]>=b[j]) return b[j];
      else l = na+1;
    }
  }
  
  /*
  --k;
  // handle one of the arrays being empty + 1st elemet case
  if (v1.empty()) return v2[k];
  if (v2.empty()) return v1[k];
  if (!k) return min(v1[0], v2[0]);
  // max reachable indices
  int lim_v1=min(k, (int)v1.size()-1);
  int lim_v2=min(k, (int)v2.size()-1);
  // say we need the k-th largest element
  // it is easy to see we need to take the 'i' _first_elements_ of v1, and 'j' _first_elements_ of v2
  // where (i+1) + (j+1) equals k
  // so we run a binary search on values of 'i' and 'j'
  int i=(LL)(k*v1.size())/(v1.size()+v2.size());  
  int j=k-i-1;
  while (1) {
    if (v1[i]<=v2[j]) {
      // i+j+1=k, v1[i]<=v2[j]<=v1[i+1] => v2[j] is k-th
      if (i==lim_v1 || v1[i+1]>=v2[j]) return v2[j];
      i+=(lim_v1-i+1)>>1;
      j=k-i-1;
    } else {
      // i+j+1=k, v2[j]<v1[i]<=v2[j+1] => v1[i] is k-th
      if (j==lim_v2 || v1[i]<=v2[j+1]) return v1[i];
      j+=(lim_v2-j+1)>>1;
      i=k-j-1;
    }
  }
  */
}

int main() {
  IV a = { 3, 4, 8 };
  IV b = { 1, 7 };
  for (int i=1; i<=5; ++i) cout << i << ' ' << select(i, a, b) << endl;
  return 0;
}





