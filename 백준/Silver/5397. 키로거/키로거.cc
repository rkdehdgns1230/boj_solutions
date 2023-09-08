#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	cin >> t;

	while (t--) {
		list<char> L;

		string keyLogger;
		cin >> keyLogger;

		list<char>::iterator ptr = L.end();

		for (char& c : keyLogger) {
			if (c == '<' && ptr != L.begin()) {
				ptr--;
			}
			else if (c == '<');
			else if (c == '>' && ptr != L.end()) {
				ptr++;
			}
			else if (c == '>');
			else if (c == '-' && ptr != L.begin()) {
				ptr--;
				ptr = L.erase(ptr);
			}
			else if (c == '-');
			else {
				L.insert(ptr, c);
			}
		}
		
		for (char& c : L)
			cout << c;
		cout << "\n";

	}

	return 0;
}