#include <vector>
#include <iostream>
using namespace std;

bool resistant_search(double x, const vector<double> &v) {
	int len = int(v.size());
	if (len == 0) return false;
	else if (len == 1) return v[0] == x;
	int esq = 0;
	int dre = len - 1;
	int m = (esq + dre) / 2;
	while (esq + 2 <= dre) {
		if (v[m] == x or v[m-1] == x or v[m+1] == x) return true;
		else if (v[m] < x) esq = m + 1;
		else dre = m - 1;
		m = (esq + dre) / 2;
	}
	return v[m] == x or v[m+1] == x;
}

int main() {
	return 0;
}
