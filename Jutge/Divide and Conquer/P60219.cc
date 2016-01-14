#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef set<string> SS;
typedef vector<string> SV;

SS has;
SS had;

bool cmp(const string &a, const string &b) {
  if (a.size() == b.size()) return a < b;
  return a.size() < b.size();
}

void print(int t) {
  if (t != 1) cout << endl;
  cout << "GAME #" << t << endl;
  cout << "HAS:" << endl;
  for (const string &s : has) cout << s << endl;
  cout << endl;
  SV had_vec;
  for (const string &s : had) had_vec.push_back(s);
  sort(had_vec.begin(), had_vec.end(), cmp);
  cout << "HAD:" << endl;
  for (const string &s : had_vec) cout << s << endl;
  has.clear();
  had.clear();
}

int main() {
  ios_base::sync_with_stdio(0);
  
  int t = 0;
  bool quit = false;
  while (!quit) {
    string s;
    cin >> s;
    if (s == "QUIT") quit = true;
    if (s == "END" or quit) print(++t);
    else {
      if (has.find(s) == has.end()) {
	has.insert(s);
	had.erase(s);
      } else {
	has.erase(s);
	had.insert(s);
      }
    }
  }
  
  return 0;
}
