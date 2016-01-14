#include <iostream>
#include <map>
using namespace std;

int main() {
	int x;
	string s, a;
	map<string, int> m;
	map<string, int>::iterator i;
	while (cin >> s >> a) {
		if (a == "enters") {
			if (m.find(s) == m.end()) m[s] = 0;
			else cout << s << " is already in the casino" << endl;
		} else if (a == "wins") {
			cin >> x;
			if ((i = m.find(s)) != m.end()) i->second += x;
			else cout << s << " is not in the casino" << endl;
		} else {
			if ((i = m.find(s)) != m.end()) {
				cout << s << " has won " << i->second << endl;
				m.erase(i);
			} else cout << s << " is not in the casino" << endl;
		}
	}
	cout << "----------" << endl;
	for (i = m.begin() ; i != m.end(); i++) cout << i->first << " is winning " << i->second << endl;
	return 0;
}
