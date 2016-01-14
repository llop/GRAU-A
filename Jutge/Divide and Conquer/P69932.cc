#include <sstream>
#include <iostream>
#include <set>
using namespace std;

void check(multiset<int>::iterator &i, const multiset<int> &s, int &last, int &count, bool &b) {
	while (i != s.end() && *i < last) i++;
	if (i != s.end() && *i > last) {
		last = *i;
		count++;
		b = !b;
		i++;
	}
}

int seq_mes_llarga(const multiset<int> &e, const multiset<int> &o) {
	if (e.empty() && o.empty()) return 0;
	else if (e.empty() || o.empty()) return 1;
	multiset<int>::iterator ie = e.begin();
	multiset<int>::iterator io = o.begin();
	bool b = *ie < *io;
	int last = b ? *ie : *io;
	int count = 1;
	if (b) ie++;
	else io++;
	while (ie != e.end() && io != o.end()) {
		if (b) check(io, o, last, count, b);
		else check(ie, e, last, count, b);
	}
	if (b) check(io, o, last, count, b);
	else check(ie, e, last, count, b);
	return count;
}

int main() {
	string s;
	while (getline(cin, s)) {
		multiset<int> e, o;
		istringstream ss(s);
		int x;
		while (ss >> x) {
			if (x % 2 == 0) e.insert(x);
			else o.insert(x);
		}
		cout << seq_mes_llarga(e, o) << endl;
	}
	return 0;
}
