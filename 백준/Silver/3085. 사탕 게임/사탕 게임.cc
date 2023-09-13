#include <bits/stdc++.h>

#define MAX 51

using namespace std;

int n;
string board[MAX];
int max_length = 0;

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void simulation(int x1, int y1, int x2, int y2) {
	int tmp = 1;

	// 변경 사항이 있는 곳만 최대 길이 갱신 여부를 판단 -> O(N)
	for (int i = 1; i < n; i++) {
		if (board[x1][i] == board[x1][i - 1])
			tmp++;
		else
			tmp = 1;
		
		max_length = max(max_length, tmp);
	}

	tmp = 1;
	for (int i = 1; i < n; i++) {
		if(board[x2][i] == board[x2][i-1])
			tmp++;
		else 
			tmp = 1;
		
		max_length = max(max_length, tmp);
	}

	tmp = 1;
	for (int i = 1; i < n; i++) {
		if (board[i][y1] == board[i - 1][y1])
			tmp++;
		else 
			tmp = 1;

		max_length = max(max_length, tmp);
	}

	tmp = 1;
	for (int i = 1; i < n; i++) {
		if (board[i][y2] == board[i - 1][y2])
			tmp++;
		else
			tmp = 1;

		max_length = max(max_length, tmp);
	}
}

void change(int x1, int y1, int x2, int y2) {
	char tmp = board[x1][y1];
	board[x1][y1] = board[x2][y2];
	board[x2][y2] = tmp;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> board[i];
	}

	// 교환을 할 두 개의 사탕을 pick (위치를 하나 골라서 인접한 두 개의 칸과 바꾼다고 생각)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (check(i + 1, j)) {
				// (i, j), (i + 1, j) 세로 교환
				change(i, j, i + 1, j);
				simulation(i, j, i + 1, j);
				change(i, j, i + 1, j);
			}

			if (check(i, j + 1)) {
				// (i, j), (i, j + 1) 가로 교환
				change(i, j, i, j + 1);
				simulation(i, j, i, j + 1);
				change(i, j, i, j + 1);
			}
		}
	}

	cout << max_length;

	return 0;
}