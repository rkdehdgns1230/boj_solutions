#include <bits/stdc++.h>

using namespace std;

string board;

bool concatenate(int& cnt, string &res) {
	while (cnt - 4 >= 0) {
		res += "AAAA";
		cnt -= 4;
	}

	while (cnt - 2 >= 0) {
		res += "BB";
		cnt -= 2;
	}

	return cnt == 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string res;

	cin >> board;

	int cnt = 0; // 연속된 X의 개수를 저장

	for (int i = 0; i < board.length(); i++) {
		if (board[i] == '.') {
			// 폴리오미노로 대체 불가능한 경우
			if (!concatenate(cnt, res)) {
				cout << "-1\n";
				return 0;
			}
			
			res += ".";
		}
		else {
			cnt++;
		}
	}
	if (!concatenate(cnt, res)) 
		cout << "-1\n";
	else
		cout << res << "\n";

	return 0;
}