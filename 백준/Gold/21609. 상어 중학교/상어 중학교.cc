#include <bits/stdc++.h>
#define MAX 21
#define INF 1001 // 삭제된 칸 처리 위해 사용

using namespace std;

int world[MAX][MAX];

int n, m;

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, -1, 0, 1 };

bool visited[MAX][MAX];

int answer = 0;

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << world[i][j] << " ";
		}
		cout << endl;
	}
}

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

pair<int, int> bfs(pair<int, int> p) {
	queue<pair<int, int>> q;
	queue<pair<int, int>> rainbow_q;

	q.push({ p.first, p.second });

	int rainbow_cnt = 0;
	int cnt = 0;
	int idx = world[p.first][p.second];

	visited[p.first][p.second] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		cnt++;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!check(nx, ny))
				continue;

			// 검은색 블록 건너띈다.
			if (world[nx][ny] == -1) continue;
			// 무지개 블록이 아닌 다른 블록 건너띈다.
			if (world[nx][ny] != 0 && world[nx][ny] != idx) continue;
			// 이미 방문한 블록은 건너띈다.
			if (visited[nx][ny]) continue;

			visited[nx][ny] = true;

			// 무지개 블록인 경우 count
			if (world[nx][ny] == 0) {
				rainbow_q.push({ nx, ny });
				rainbow_cnt++;
			}

			q.push({ nx, ny });
		}
	}
	// 무지개 블록은 다시 미방문 처리
	while (!rainbow_q.empty()) {
		int x = rainbow_q.front().first;
		int y = rainbow_q.front().second;
		rainbow_q.pop();

		visited[x][y] = false;
	}

	return { cnt, rainbow_cnt };
}

void delete_group(pair<int, int> p) {
	queue<pair<int, int>> q;
	q.push(p);

	int idx = world[p.first][p.second];
	world[p.first][p.second] = INF; // 삭제 처리

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!check(nx, ny)) continue;

			// 리더와 같은 블록이거나 무지개 블록만 삭제한다.
			if (world[nx][ny] == idx || world[nx][ny] == 0) {
				world[nx][ny] = INF; // 삭제 처리
				q.push({ nx, ny });
			}
		}
	}
}

// 3, 5: 격자에 중력이 작용
void gravity() {
	int tmp_world[MAX][MAX];

	for (int i = 0; i < n; i++)
		fill(tmp_world[i], tmp_world[i] + n, INF);

	// 빈칸의 값은 INF
	for (int y = 0; y < n; y++) {
		int floor = n - 1;
		// 아래에서부터 올라가며, 쌓아올린다.
		for (int x = n - 1; x >= 0; x--) {
			// 검은색 블록은 중력에 의해 움직이지 않는다.
			if (world[x][y] == -1) {
				floor = x; // 현재 바닥의 위치를 바꿔준다.
				tmp_world[floor--][y] = world[x][y];
			}
			else if (world[x][y] != INF) {
				tmp_world[floor--][y] = world[x][y];
			}
		}

		// 남은 칸은 비운다.
		for (int x = floor; x >= 0; x--) {
			tmp_world[x][y] = INF;
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			world[i][j] = tmp_world[i][j];
}

// 4: 격자가 90도 반시계 방향으로 회전
void rotate() {
	int tmp_world[MAX][MAX];

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			tmp_world[x][y] = world[y][n - 1 - x];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			world[i][j] = tmp_world[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> world[i][j];
	}

	// 블록 그룹이 존재할 때까지 반복해야 한다. (블록 그룹은 최소 2개의 블록으로 구성)
	while (1) {
		bool group_exist = false;

		// 가장 큰 블록 그룹의 정보
		int max_group_cnt = 0;
		int max_rainbow_cnt = 0;
		int x = 0;
		int y = 0;

		for (int i = 0; i < n; i++) {
			fill(visited[i], visited[i] + n, false);
		}

		// 1. 가장 큰 블록 그룹을 찾는다.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j]) continue;
				// 검은색 블록과 무지개 블록은 그룹 카운트 대상에서 제외 + 지워진 칸도 제외
				if (world[i][j] == -1 || world[i][j] == 0 || world[i][j] == INF) continue;

				pair<int, int> res = bfs({ i, j });

				if (res.first >= 2 &&
					((max_group_cnt < res.first) ||
						(max_group_cnt == res.first && max_rainbow_cnt <= res.second))) {
					group_exist = true;
					x = i; y = j;
					max_group_cnt = res.first;
					max_rainbow_cnt = res.second;

					//cout << "{" << x << ", " << y << "}: " << world[i][j] << "에 대한 그룹의 개수 : " << res.first << ", " << res.second << endl;
				}
			}
		}

		if (!group_exist) {
			//cout << "더 이상 그룹이 존재하지 않습니다.\n";
			//print();
			break;
		}

		// 점수 계산
		answer += max_group_cnt * max_group_cnt;
		//cout << "현재 누적 점수: " << answer << endl;

		//cout << "최대 그룹의 정보: " << max_group_cnt << " {" << x << ", " << y << "}\n";
		delete_group({ x, y });

		//cout << "중력 작용\n";
		gravity();
		//print();
		//cout << "반시계 90도 회전" << endl;
		rotate();
		//print();
		//cout << "다시 중력 작용\n";
		gravity();
		//print();
	}
	cout << answer;

	return 0;
}