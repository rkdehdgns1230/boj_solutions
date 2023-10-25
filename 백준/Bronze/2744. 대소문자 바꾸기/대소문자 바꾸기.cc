#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string str;
	cin >> str;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			cout << (char) (str[i] - 32);
		}
		else {
			cout << (char)(str[i] + 32);
		}
	}
	return 0;
}