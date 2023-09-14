#include <bits/stdc++.h>

#define MAX 1001

using namespace std;

int t;
int w, h;

string building[MAX];

int dis[MAX][MAX];
bool fired[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int answer = -1;

bool check(int x, int y) {
	return (0 <= x && x < h && 0 <= y && y < w);
}

void BFS() {
	queue<pair<int, int>> q;
	queue<pair<int, int>> fire_q;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (building[i][j] == '@')
				q.push({ i, j });
			if(fired[i][j])
				fire_q.push({ i, j });
		}
	}

	int cur_time = 0;

	while (1) {
		int cur_q_size = q.size();

		// 더 이상 이동할 수 없는 경우
		if (cur_q_size == 0) {
			answer = -1;
			return;
		}

		while (cur_q_size--) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			if (fired[x][y]) continue;

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				// 빌딩 탈출 성공!
				if (!check(nx, ny)) {
					answer = dis[x][y] + 1;
					return;
				}

				if (dis[nx][ny] != -1 || building[nx][ny] == '#' || fired[nx][ny])
					continue;
				dis[nx][ny] = dis[x][y] + 1;
				q.push({ nx, ny });
			}
		}

		// 화재 번짐
		int cur_fire_q_size = fire_q.size();

		while (cur_fire_q_size--) {
			int x = fire_q.front().first;
			int y = fire_q.front().second;
			fire_q.pop();

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!check(nx, ny) || building[nx][ny] == '#' || fired[nx][ny])
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

	cin >> t;

	while (t--) {
		cin >> w >> h;

		for (int i = 0; i < h; i++) {
			cin >> building[i];

			fill(dis[i], dis[i] + MAX, -1);
			fill(fired[i], fired[i] + MAX, false);

			for (int j = 0; j < w; j++) {
				if (building[i][j] == '@') {
					dis[i][j] = 0;
				}

				if (building[i][j] == '*') {
					fired[i][j] = true;
				}
			}
		}
		BFS();

		if (answer == -1) cout << "IMPOSSIBLE\n";
		else cout << answer << "\n";
	}

	return 0;
}