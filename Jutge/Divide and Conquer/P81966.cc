#include <vector>
using namespace std;

int posicio(double x, const vector<double> &v, int esq, int dre) {
	if (esq <= dre) {
		int m = (esq + dre) / 2;
		if (v[m] == x) return m;
		else if (v[m] < x) return posicio(x, v, m + 1, dre);
		else return posicio(x, v, esq, m - 1);
	}
	return -1;
}

int main() {
	return 0;
}
