#include <bits/stdc++.h>

#define MAX 41
#define ST_MAX 11

using namespace std;

int n, m, k;

int note_book[MAX][MAX];
int sticker[ST_MAX][ST_MAX];
// 스티커 복사
int tmp_sticker[ST_MAX][ST_MAX];

bool canAdd(int x, int y, int r, int c) {
	for (int i = x; i < x + r; i++) {
		for (int j = y; j < y + c; j++) {
			// 붙이려는 곳에 이미 부착된 경우
			if (tmp_sticker[i - x][j - y] == 1 && note_book[i][j] == 1) {
				return false;
			}
		}
	}
	//cout << x << ", " << y << "에 부착 성공\n";
	return true;
}

void add_sticker(int x, int y, int r, int c) {
	// 현재 위치에 스티커를 붙인다.
	for (int a = x; a < x + r; a++) {
		for (int b = y; b < y + c; b++) {
			if (note_book[a][b] == 1) continue;

			note_book[a][b] = tmp_sticker[a - x][b - y];
		}
	}
}

void simulation(int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			tmp_sticker[i][j] = sticker[i][j];
		}
	}
	/*cout << "0도 회전\n";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << tmp_sticker[i][j] << " ";
		}cout << endl;
	}*/

	// 스티커 부착 시도
	for (int i = 0; i <= n - r; i++) {
		for (int j = 0; j <= m - c; j++) {
			// 붙일 수 있는 경우 발견
			if (canAdd(i, j, r, c)) {
				add_sticker(i, j, r, c);
				return;
			}
		}
	}

	// 실패시 90도 회전
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			tmp_sticker[i][j] = sticker[r - 1 - j][i];
		}
	}
	/*cout << "90도 회전\n";
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			cout << tmp_sticker[i][j] << " ";
		}cout << endl;
	}*/

	// 스티커 부착 시도 (r, c 바뀜)
	for (int i = 0; i <= n - c; i++) {
		for (int j = 0; j <= m - r; j++) {
			// 붙일 수 있는 경우 발견
			if (canAdd(i, j, c, r)) {
				add_sticker(i, j, c, r);
				return;
			}
		}
	}

	// 실패시 180도 회전
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			tmp_sticker[i][j] = sticker[r - i - 1][c - j - 1];
		}
	}
	/*cout << "180도 회전\n";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << tmp_sticker[i][j] << " ";
		}cout << endl;
	}*/

	// 스티커 부착 시도
	for (int i = 0; i <= n - r; i++) {
		for (int j = 0; j <= m - c; j++) {
			// 붙일 수 있는 경우 발견
			if (canAdd(i, j, r, c)) {
				add_sticker(i, j, r, c);
				return;
			}
		}
	}

	// 실패시 270도 회전
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			tmp_sticker[i][j] = sticker[j][c - 1 - i];
		}
	}
	/*cout << "270도 회전\n";
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			cout << tmp_sticker[i][j] << " ";
		}cout << endl;
	}*/

	// 스티커 부착 시도 (r, c 바뀜)
	for (int i = 0; i <= n - c; i++) {
		for (int j = 0; j <= m - r; j++) {
			// 붙일 수 있는 경우 발견
			if (canAdd(i, j, c, r)) {
				add_sticker(i, j, c, r);
				return;
			}
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int answer = 0;
	cin >> n >> m >> k;

	for (int i = 0; i < k; i++) {
		int r, c;
		cin >> r >> c;

		for (int a = 0; a < r; a++) 
			for (int b = 0; b < c; b++)
				cin >> sticker[a][b];
		
		simulation(r, c);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (note_book[i][j] == 1)
				answer++;
		}
	}
	cout << answer;

	return 0;
}