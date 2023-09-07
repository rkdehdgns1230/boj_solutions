#include <bits/stdc++.h>

using namespace std;

int n;
string a, b;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	while (n--) {
		cin >> a >> b;

		vector<int> a_cnt(26, 0);
		vector<int> b_cnt(26, 0);

		for (char& c : a) 
			a_cnt[c - 'a']++;
		
		for (char& c : b)
			b_cnt[c - 'a']++;

		bool isStrfry = true;
		for (int i = 0; i < 26; i++) {
			if (a_cnt[i] != b_cnt[i]) {
				cout << "Impossible\n";
				isStrfry = false;
				break;
			}
		}
		if (isStrfry)
			cout << "Possible\n";
	}

	return 0;
}