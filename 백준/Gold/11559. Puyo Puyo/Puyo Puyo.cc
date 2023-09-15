#include <bits/stdc++.h>

using namespace std;

string puyo[13];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool visited[12][6];

queue<pair<int, int>> bomb_q;

bool check(int x, int y) {
	return (0 <= x && x < 12 && 0 <= y && y < 6);
}

bool canBomb(int x, int y) {
	// 터질 대상을 비우고 시작
	while (!bomb_q.empty())
		bomb_q.pop();

	queue<pair<int, int>> q;
	q.push({ x, y });
	bomb_q.push({ x, y });

	visited[x][y] = true;

	char c = puyo[x][y];
	int cnt = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		cnt++;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!check(nx, ny) || puyo[nx][ny] != c || visited[nx][ny])
				continue;

			visited[nx][ny] = true;
			q.push({ nx, ny });
			bomb_q.push({ nx, ny });
		}
	}
	// 4개 이상 겹쳐야 뿌요를 터트린다.
	return cnt >= 4;
}

void bomb() {
	while (!bomb_q.empty()) {
		int x = bomb_q.front().first;
		int y = bomb_q.front().second;
		bomb_q.pop();

		puyo[x][y] = '.';
	}
}

void clean() {
	for (int i = 0; i < 6; i++) {
		int idx = 11;
		for (int j = 11; j >= 0; j--) {
			if (puyo[j][i] != '.')
				puyo[idx--][i] = puyo[j][i];
		}
		// 나머지 칸은 빈칸으로 매꾼다.
		for (int j = idx; j >= 0; j--) {
			puyo[j][i] = '.';
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 12; i++) {
		cin >> puyo[i];
	}

	int combo = 0;


	while (1) {
		bool isBomb = false;

		for (int i = 0; i < 12; i++)
			fill(visited[i], visited[i] + 6, false);

		// 터지는 케이스 탐색 및 터트림 + 연쇄 계산
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (visited[i][j] || puyo[i][j] == '.') continue;

				if (canBomb(i, j)) {
					isBomb = true;
					bomb();
				}
			}
		}

		// 터트린 케이스가 없으면 종료를 의미
		if (!isBomb)
			break;

		// 터트린 잔해를 지우는 작업
		clean();

		combo++;
	}

	cout << combo;

	return 0;
}