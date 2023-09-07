#include <bits/stdc++.h>

using namespace std;

int firstAlphabet[26];
int secondAlphabet[26];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string a, b;
	cin >> a >> b;

	int ans = 0;

	for (char& c : a) {
		firstAlphabet[c - 'a']++;
	}
	for (char& c : b) {
		secondAlphabet[c - 'a']++;
	}


	for (int i = 0; i < 26; i++) {
		if (firstAlphabet[i] != secondAlphabet[i]) {
			ans += abs(firstAlphabet[i] - secondAlphabet[i]);
		}
	}
	cout << ans;

	return 0;
}