#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	map<string, bool> entry;

	for (int i = 0; i < n; i++) {
		string name, op;
		cin >> name >> op;
		
		if (op == "enter") {
			entry[name] = true;
		}
		else {
			if (entry.find(name) != entry.end()) {
				entry[name] = false;
			}
		}
	}
	vector<string> answer;

	for (auto it = entry.begin(); it != entry.end(); it++) {
		if (it->second)
			answer.push_back(it->first);
	}

	for (int i = answer.size() - 1; i >= 0; i--) {
		cout << answer[i] << "\n";
	}

	return 0;
}