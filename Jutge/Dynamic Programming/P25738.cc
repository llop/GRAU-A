#include <string.h>
#include <iostream>
using namespace std;

const int MAX = 2001;
int tbl[MAX];
int tim[MAX];
int t, n;

int main() {
  cin >> t;
  for (int i = 0; i < t; ++i) {
    cin >> n;
	for (int j = 0; j < n; ++j) {
	  tbl[j] = 1;
	  cin >> tim[j];
	}
	// longest increasing subsequence
	for (int i = 1; i < n; ++i) {
	  for (int j = 0; j < i; ++j) {
	    if (tim[i] >= (tim[j] + 10) && tbl[i] <= tbl[j]) {
		  tbl[i] = tbl[j] + 1;
		}
	  }
	}
	
	int max = 0;
	for (int i = 0; i < n; ++i) {
	  if (max < tbl[i]) {
	    max = tbl[i];
	  }
	}
	cout << max << endl;
  }
  return 0;
}