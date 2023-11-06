#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<string> str_v;
	int len = 0;
	int max_len = 0;

	for (int i = 0; i < 5; i++) {
		string str;
		cin >> str;

		str_v.push_back(str);
		max_len = max(max_len, (int) str.length());
	}
	
	
	while (len < max_len) {
		for (int i = 0; i < 5; i++) {
			if (str_v[i].length() <= len) continue;
			cout << str_v[i][len];
		}
		len++;
	}

	return 0;
}