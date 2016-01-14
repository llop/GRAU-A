#include <vector>
using namespace std;

int first_occurrence(double x, const vector<double> &v) {
	int len = int(v.size());
	if (len == 0) return -1;
	else {
		if (v[0] == x) return 0;
		else if (len == 1 || v[0] > x) return -1;
	}
	int esq = 1;
	int dre = len - 1;
	int m = (esq + dre) / 2;
	while (esq < dre) {
		if (v[m] == x && v[m - 1] != x) return m;
		else if (v[m] < x) esq = m + 1;
		else dre = m - 1;
		m = (esq + dre) / 2;
	}
	if (v[m] == x && v[m - 1] != x) return m;
	return -1;
}

int main() {
	return 0;
}
