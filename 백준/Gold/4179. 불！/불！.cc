#include <bits/stdc++.h>

#define MAX 1001

using namespace std;

string miro[MAX];
int dis[MAX][MAX];
bool fired[MAX][MAX]; // 이미 불에 탄 영역 정보를 담는다.
int r, c;

int answer = -1;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool check(int x, int y) {
	return (0 <= x && x < r && 0 <= y && y < c);
}

void BFS() {
	// 지훈이와 불의 위치를 잡는다.
	queue<pair<int, int>> q;
	queue<pair<int, int>> fire_q;

	int cur_time = 0;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (fired[i][j])
				fire_q.push({ i, j });
		}
	}

	while (1) {
		/*
			지훈이가 이동 시작 가능한 위치를 큐에 넣는다.
			현재 불의 위치를 fire_q에 넣는다.
		*/
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				// 불이 번지지 않은 위치에 대해서만
				if (dis[i][j] == cur_time && !fired[i][j])
					q.push({ i, j });
			}
		}

		// 지훈이가 더 이상 이동할 위치가 없는 경우 종료
		if (q.empty()) {
			return;
		}

		// 시간을 기준으로 queue에 넣고 뺴야 한다. (이미 불이 난 케이스의 경우 위치 추가 불가)
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!check(nx, ny)) {
					// 탈출 성공을 의미한다.
					answer = dis[x][y] + 1;
					return;
				}

				// 이미 방문한 위치 or 벽 or 불이난 위치 -> 이동 X
				if (dis[nx][ny] != -1 || miro[nx][ny] == '#' || fired[nx][ny]) 
					continue;
				dis[nx][ny] = dis[x][y] + 1;
			}
		}

		// 불 확산 로직
		int cur_size = fire_q.size();
		while (cur_size--) {
			int x = fire_q.front().first;
			int y = fire_q.front().second;
			fire_q.pop();

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!check(nx, ny) || miro[nx][ny] == '#' || fired[nx][ny]) 
					continue;
				fired[nx][ny] = true;
				fire_q.push({ nx, ny });
			}
		}

		cur_time++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		// 거리 정보를 저장하는 배열의 원소들을 -1로 초기화한다.
		fill(dis[i], dis[i] + MAX, -1);
	}

	for (int i = 0; i < r; i++) {
		cin >> miro[i];

		for (int j = 0; j < c; j++) {
			if (miro[i][j] == 'J') {
				dis[i][j] = 0;
			}
			if (miro[i][j] == 'F') {
				fired[i][j] = true;
			}
		}
	}

	BFS();

	if (answer != -1) cout << answer;
	else cout << "IMPOSSIBLE\n";

	return 0;
}