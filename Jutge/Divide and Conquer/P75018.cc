#include <iostream> 
#include <set>

using namespace std;

int main() {
  set<int> s;
  int v, n, a;
  cin >> v >> n;
  while (v != 0 && n != 0) {
    bool single = true;
    for (int i = 0; i < n; i++) {
      cin >> a;
      if (single) {
	if (s.find(a) != s.end()) single = false;
	else s.insert(v - a);
      }
    }
    s.clear();
    if (single) cout << "single" << endl;
    else cout << "married" << endl;
    cin >> v >> n;
  }
  return 0;
}