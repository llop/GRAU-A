#include <iostream>
#include <map>
using namespace std;

int main() {
	string s, a;
	map<string, int> m;
	map<string, int>::iterator i;
	while (cin >> s) {
		if (s == "minimum?") {
			if (m.empty()) cout << "indefinite minimum" << endl;
			else {
				i = m.begin();
				cout << "minimum: " << i->first << ", " << i->second << " time(s)" << endl;
			}
		} else if (s == "maximum?") {
			if (m.empty()) cout << "indefinite maximum" << endl;
			else {
				(i = m.end())--;
				cout << "maximum: " << i->first << ", " << i->second << " time(s)" << endl;
			}
		} else {
			cin >> a;
			i = m.find(a);
			if (s == "store") {
				if (i == m.end()) m[a] = 1;
				else i->second++;
			} else if (i != m.end() && !--i->second) m.erase(i);
		}
	}
	return 0;
}
