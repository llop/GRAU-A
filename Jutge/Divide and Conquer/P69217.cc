#include <iostream>
#include <queue>
using namespace std;

typedef queue<string> SQ;

int n;
string s;
SQ que;
SQ que_arr[26];

inline int code(const char &c) {
  return c - 'a';
}

int main() {
  // esta funcion accelera el cin/cout
  ios_base::sync_with_stdio(0);
  while (cin >> s) que.push(s);
  n = s.size();
  
  for (int i = n - 1; i >= 0; --i) {
    while (not que.empty()) {
      const string t = que.front();
      que.pop();
      int ind = code(t[i]);
      que_arr[ind].push(t);
    }
    
    for (int j = 0; j < 26; ++j) {
      while (not que_arr[j].empty()) {
	que.push(que_arr[j].front());
	que_arr[j].pop();
      }
    }
  }
  
  bool b = 1;
  while (not que.empty()) {
    if (b) b = 0;
    else cout << ' ';
    cout << que.front();
    que.pop();
  }
  cout << endl;
  return 0;
}

