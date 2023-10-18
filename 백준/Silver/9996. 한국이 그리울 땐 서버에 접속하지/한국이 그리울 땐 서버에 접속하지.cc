#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	string p;
	cin >> p;

	int star_idx = 0;
	for (int i = 0; i < p.length(); i++) {
		if (p[i] == '*') {
			star_idx = i;
			break;
		}
	}

	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		// 별표는 문자열의 중간에만 위치함에 유의하자.

		bool isRight = true;
		int cnt = 0;

		// ab*bc -> abc 같은 케이스를 거르기 위해
		if (p.length() - 1 > str.length()) {
			cout << "NE\n";
			continue;
		}

		// 별표 앞 뒤에 위치한 부분 문자열의 일치 여부만 판단하면 된다.
		for (int i = 0; i < star_idx; i++) {
			if (p[i] != str[i]) {
				isRight = false;
				break;
			}
		}

		if (!isRight) {
			cout << "NE\n";
			continue;
		}

		for (int i = 0; i < p.length() - star_idx - 1; i++) {
			if (p[p.length() - 1 - i] != str[str.length() - 1 - i]) {
				isRight = false;
				break;
			}
		}


		if (isRight)
			cout << "DA\n";
		else
			cout << "NE\n";
	}

	return 0;
}