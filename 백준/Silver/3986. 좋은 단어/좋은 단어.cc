#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t, answer = 0;
	cin >> t;

	while (t--) {
		stack<char> S;
		string str;

		cin >> str;

		for (int i = 0; i < str.length(); i++) {
			if (S.empty()) {
				S.push(str[i]);
			}
			else if(S.top() == str[i]){
				S.pop();
			}
			else {
				S.push(str[i]);
			}
		}

		if (S.empty()) {
			answer++;
		}
	}
	cout << answer;

	return 0;
}