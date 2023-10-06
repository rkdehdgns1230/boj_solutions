#include <bits/stdc++.h>

#define MAX 101

using namespace std;

int n, k;

vector<vector<int>> board;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool is_success() {
	int max_fishes = *max_element(board[0].begin(), board[0].end());
	int min_fishes = *min_element(board[0].begin(), board[0].end());

	return (max_fishes - min_fishes) <= k;
}

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void print() {
	cout << "<--------- PRINT --------->\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

// 물고기 수를 조절
void move_fish() {
	vector<vector<int>> tmp_board = board;

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (board[x][y] == -1) continue;

			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];

				if (!check(nx, ny) || board[nx][ny] == -1)continue;

				int diff = board[nx][ny] - board[x][y];
				tmp_board[x][y] += (int)(diff) / 5;
			}
		}
	}

	board = tmp_board;
}

// 어항 정리 1회 수행
void move() {

	// 1. 물고기 증가
	int min_fishes = *min_element(board[0].begin(), board[0].end());

	for (int i = 0; i < n; i++) {
		if (board[0][i] == min_fishes)
			board[0][i]++;
	}

	// 2. 어항 공중 부양 및 회전
	int sx = 0; // 움직일 어항의 시작 좌표를 의미
	int lx = 1, ly = 1; // 움직일 어항의 세로 및 가로 길이를 의미
	
	// sx + lx + ly - 1이 다음 칸에 움직인 이후의 가장 오른쪽 어항의 좌표를 의미 (이 좌표가 공중부양 하기 전까지만 반복)
	while (sx + lx + ly <= n) {
		for (int y = 0; y < ly; y++) {
			for (int x = 0; x < lx; x++) {
				// sx 좌표 부터 시작하는 ly * lx 크기의 어항을 90도 회전시켜서 올려 쌓는 과정
				int ny = lx - x;
				int nx = sx + lx + y;

				board[ny][nx] = board[y][x + sx];
				board[y][x + sx] = -1; // 기존 어항의 정보 삭제
			}
		}
		sx += lx;
		if (lx == ly)
			ly++;
		else
			lx++;

		//print();
	}

	// 3. 물고기 수 조절
	move_fish();
	//print();

	// 4. 다시 일렬로 재배치
	vector<vector<int>> flatten(n, vector<int>(n, -1));

	int idx = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[j][i] == -1) continue;
			flatten[0][idx++] = board[j][i];
		}
	}

	board = flatten;
	//cout << "다시 일렬로 재배치 과정\n";
	//print();

	// 5. 다시 공중 부양 작업 (반으로 접는 과정을 두 번 반복)
	sx = 0; lx = 1; ly = n / 2;
	// 두 번 반복
	for (int i = 0; i < 2; i++) {

		for (int x = 0; x < lx; x++) {
			for (int y = 0; y < ly; y++) {
				int nx = 2 * lx - 1 - x;
				int ny = 2 * ly - 1 + sx - y;

				board[nx][ny] = board[x][sx + y];
				board[x][sx + y] = -1;
			}
		}
		sx += ly;
		ly /= 2;
		lx *= 2;
	}
	/*
	cout << "물고기 두 번 접어 올리기\n";
	print();
	*/

	// 6. 물고기 재배치
	move_fish();

	// 7. 다시 일렬로 재배치
	flatten = vector<vector<int>>(n, vector<int>(n, -1));

	idx = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[j][i] == -1) continue;
			flatten[0][idx++] = board[j][i];
		}
	}

	board = flatten;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	
	// n x n size로 -1 값으로 가득찬 2차원 배열로 초기화 한다.
	board = vector<vector<int>>(n, vector<int>(n, -1));

	for (int i = 0; i < n; i++) {
		cin >> board[0][i];
	}
	
	int answer = 0;

	while (!is_success()) {
		move();
		answer++;
	}

	cout << answer;

	return 0;
}