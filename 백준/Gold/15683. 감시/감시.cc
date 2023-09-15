#include <bits/stdc++.h>

#define MAX 9

using namespace std;

int n, m; // 세로, 가로

// 동, 서, 남, 북
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int answer = 0;
int working_room[MAX][MAX];

vector<pair<int, int>> cam_sites;
// 1: 그대로, 2: 수직 2개, 3: 1번 + -1방향, 4: 1번 + 2번, 5번: 모든 방향
vector<int> cam_dir(8, 0);

bool visited[MAX][MAX];

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

void camera_on(int x, int y, int dir) {
	while (1) {
		x += dx[dir];
		y += dy[dir];

		// 사무실 밖 or 벽에 부딪힘
		if (!check(x, y) || working_room[x][y] == 6)
			break;

		// 이미 방문한 케이스 건너 띔
		if (visited[x][y])
			continue;

		visited[x][y] = true;
	}
}

void simulation() {
	int result = 0;

	for (int i = 0; i < n; i++) {
		fill(visited[i], visited[i] + m, false);
	}

	for (int i = 0; i < cam_sites.size(); i++) {
		int x = cam_sites[i].first;
		int y = cam_sites[i].second;
		int dir = cam_dir[i];

		visited[x][y] = true;

		if (working_room[x][y] == 1) {
			camera_on(x, y, dir);
		}
		else if (working_room[x][y] == 2) {
			int left_dir = (dir - 1 >= 0) ? dir - 1 : 3;
			int right_dir = (dir + 1 <= 3) ? dir + 1 : 0;

			camera_on(x, y, left_dir);
			camera_on(x, y, right_dir);
		}
		else if (working_room[x][y] == 3) {
			int left_dir = (dir - 1 >= 0) ? dir - 1 : 3;

			camera_on(x, y, dir);
			camera_on(x, y, left_dir);
		}
		else if (working_room[x][y] == 4) {
			int left_dir = (dir - 1 >= 0) ? dir - 1 : 3;
			int right_dir = (dir + 1 <= 3) ? dir + 1 : 0;

			camera_on(x, y, dir);
			camera_on(x, y, left_dir);
			camera_on(x, y, right_dir);
		}
		else {
			camera_on(x, y, 0);
			camera_on(x, y, 1);
			camera_on(x, y, 2);
			camera_on(x, y, 3);
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (visited[i][j])
				result++;

	answer = (answer > result) ? answer : result;
}

// 시간 복잡도: 4^8
void dfs(int idx) {
	if (idx == cam_sites.size()) {
		simulation();
		return;
	}

	for (int i = 0; i < 4; i++) {
		cam_dir[idx] = i;
		dfs(idx + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	int wall_count = 0;

	// cctv는 최대 8개가 존재할 수 있음 -> 8개에 대해서 모든 경우의 수를 탐색하면 된다.
	// 8 -> 4개의 방향
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> working_room[i][j];

			// cctv 위치는 따로 저장한다.
			if (1 <= working_room[i][j] && working_room[i][j] <= 5) {
				cam_sites.push_back({ i, j });
			}
			if (working_room[i][j] == 6)
				wall_count++;
		}
	}

	dfs(0);

	cout << n * m - wall_count - answer;

	return 0;
}