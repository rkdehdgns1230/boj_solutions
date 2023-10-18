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
	int cnt = 0;

	// i: start point
	for (int i = 0; i <= pattern.length(); i++) {
		int res = 0;
		cnt = 0;
		// idx: start point부터 탐색 직접적으로 담당
		for (int idx = i; idx < str.length(); idx++) {
			if (str[idx] == pattern[cnt++]) {

				if (cnt == pattern.length()) {
					res++;
					cnt = 0;
				}
			}
			else
				cnt = 0;
		}
		answer = max(answer, res);
	}

	cout << answer;


	return 0;
}