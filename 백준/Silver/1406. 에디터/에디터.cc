#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	list<char> L;

	string initial_str;
	cin >> initial_str;

	for (char& c : initial_str)
		L.push_back(c);

	cin >> n;

	list<char>::iterator ptr = L.end();

	for (int i = 0; i < n; i++) {
		char op;
		cin >> op;

		if (op == 'P') {
			char c;
			cin >> c;
			L.insert(ptr, c);
		}
		else if (op == 'L' && ptr != L.begin()) {
			ptr--;
		}
		else if (op == 'D' && ptr != L.end()) {
			ptr++;
		}
		else if (op == 'B') {
			if (ptr == L.begin())
				continue;
			ptr--;
			ptr = L.erase(ptr);
		}
	}

	for (char& c : L)
		cout << c;

	return 0;
}