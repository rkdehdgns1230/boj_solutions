#include <bits/stdc++.h>
#define MAX 21

using namespace std;

int dice[7] = { 0, 1, 2, 3 ,4, 5, 6 }; // 1, 2, 3, 4, 5, 6이 주사위의 각 위치를 의미한다.
int board[MAX][MAX];
int n, m, k;

// 우, 하, 좌, 상 순으로 방향
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

void roll(int d) {
	int tmp_dice[7];

	// 오른쪽으로 주사위를 굴리는 경우 (y+1)
	if (d == 0) {
		tmp_dice[1] = dice[4];
		tmp_dice[2] = dice[2];
		tmp_dice[3] = dice[1];
		tmp_dice[4] = dice[6];
		tmp_dice[5] = dice[5];
		tmp_dice[6] = dice[3];
	}
	// 왼쪽으로 주사위를 굴리는 경우 (y-1)
	else if (d == 2) {
		tmp_dice[1] = dice[3];
		tmp_dice[2] = dice[2];
		tmp_dice[3] = dice[6];
		tmp_dice[4] = dice[1];
		tmp_dice[5] = dice[5];
		tmp_dice[6] = dice[4];
	}
	// 위쪽
	else if (d == 3) {
		tmp_dice[1] = dice[5];
		tmp_dice[2] = dice[1];
		tmp_dice[3] = dice[3];
		tmp_dice[4] = dice[4];
		tmp_dice[5] = dice[6];
		tmp_dice[6] = dice[2];
	}
	// 아래쪽
	else {
		tmp_dice[1] = dice[2];
		tmp_dice[2] = dice[6];
		tmp_dice[3] = dice[3];
		tmp_dice[4] = dice[4];
		tmp_dice[5] = dice[1];
		tmp_dice[6] = dice[5];
	}

	for (int i = 1; i <= 6; i++) {
		dice[i] = tmp_dice[i];
	}
	return;
}

int calc_score(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });

	int num = board[x][y];

	bool visited[MAX][MAX];
	for (int i = 0; i < n; i++)
		fill(visited[i], visited[i] + m, false);

	visited[x][y] = true;
	int result = 0;

	while (!q.empty()) {
		int cur_x = q.front().first;
		int cur_y = q.front().second;
		q.pop();
		result++;
		for (int i = 0; i < 4; i++) {
			int nx = cur_x + dx[i];
			int ny = cur_y + dy[i];

			if (!check(nx, ny) || visited[nx][ny] || board[nx][ny] != num) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> board[i][j];

	int dir = 0; // 처음 이동 방향은 동쪽(오른쪽)
	int x = 0, y = 0;


	int answer = 0;

	while (k--) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		// 격자를 벗어난 경우 이동 방향을 반대로 설정
		if (!check(nx, ny)) {
			dir += 2;
			dir %= 4; // 4 -> 0, 5 -> 1
			
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
		//cout << nx << ", " << ny << " 방문" << endl;
		x = nx, y = ny;

		roll(dir);
		// 2. 해당 칸의 점수를 획득
		int res = calc_score(nx, ny);
		//cout << "현재 점수: " << res << " x " << board[nx][ny] << endl;
		answer += (res * board[nx][ny]);

		int A = dice[6]; // 주사위의 밑면
		int B = board[nx][ny];

		if (A > B) {
			dir++;
			dir %= 4;
		}
		else if (A < B) {
			dir--;
			if (dir < 0)
				dir = 3;
		}
	}

	cout << answer << endl;

	return 0;
}