#include <bits/stdc++.h>

using namespace std;

pair<int, int> bingo_board[26];
bool is_called[5][5];

bool isBingo() {
	int res = 0;

	for (int i = 0; i < 5; i++) {
		bool parallel_line = true;
		bool horizontal_line = true;

		for (int j = 0; j < 5; j++) {
			if (!is_called[i][j]) {
				parallel_line = false;
			}
			if (!is_called[j][i]) {
				horizontal_line = false;
			}
		}

		if (parallel_line)
			res++;
		if (horizontal_line)
			res++;
	}

	bool cross_line = true;
	bool reverse_cross_line = true;
	for (int i = 0; i < 5; i++) {
		if (!is_called[i][i])
			cross_line = false;

		if (!is_called[4 - i][i])
			reverse_cross_line = false;
	}

	if (cross_line)
		res++;
	if (reverse_cross_line)
		res++;

	// 3개 이상 그어져야 빙고
	return res >= 3;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int tmp;
			cin >> tmp;
			// 입력 받은 수의 좌표를 저장하는 방식
			bingo_board[tmp] = { i, j };
		}
	}
	int answer = 0;
	bool isEnd = false;

	for (int i = 1; i <= 25; i++) {
		int tmp;
		cin >> tmp;

		int x = bingo_board[tmp].first;
		int y = bingo_board[tmp].second;

		is_called[x][y] = true;

		if (!isEnd && isBingo()) {
			answer = i;
			isEnd = true;
		}
	}

	cout << answer;

	return 0;
}