#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string str;

	string pattern;

	getline(cin, str);
	getline(cin, pattern);

	int answer = 0;

	int f = str.find(pattern);
	while (f != string::npos) {
		answer++;
		f = str.find(pattern, f + pattern.size());
	}

	cout << answer;


	return 0;
}