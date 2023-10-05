#include <bits/stdc++.h>
#define MAX 51

using namespace std;

int n, m;
int g, r; // green, red
int garden[MAX][MAX]; // 0: 호수, 1: 배양액 X, 2: 배양액 O

vector<pair<int, int>> v;

bool g_picked[MAX];
bool r_picked[MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int answer;

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

void bfs() {
	queue<pair<pair<int, int>, bool>> q; // 배양액 정보를 담은 queue (true: g, false: r)

	// first; time
	// second 1: 초록 배양액, 2: 빨간 배양액 방문 표시, 3: 꽃
	pair<int, int> visited[MAX][MAX];
	int res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			visited[i][j] = { 0, 0 };
	}

	for (int i = 0; i < v.size(); i++) {
		if (g_picked[i]) {
			//cout << "green: " << v[i].first << ", " << v[i].second << endl;
			visited[v[i].first][v[i].second] = { 0, 1 };
			q.push({ v[i], false });
		}

		if (r_picked[i]) {
			//cout << "red: " << v[i].first << ", " << v[i].second << endl;
			visited[v[i].first][v[i].second] = { 0, 2 };
			q.push({ v[i], true });
		}
	}

	while (!q.empty()) {
		int size = q.size();

		while (size--) {
			int x = q.front().first.first;
			int y = q.front().first.second;
			bool is_red = q.front().second;
			q.pop();

			// 이미 꽃이 피어난 경우 배양액은 사라진다.
			if (visited[x][y].second == 3)
				continue;

			int sign = is_red ? 2 : 1; // 빨강이면 2, 초록이면 1로 표기할 것이므로

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				// 범위 밖이거나, 호수로는 퍼질 수 없다. or 이미 방문한 칸 또한 불가능 (꽃, 배양액)
				if (!check(nx, ny) || garden[nx][ny] == 0 || visited[nx][ny].second == 3)
					continue;

				// 현 시점에 다른 종류의 배양액이 만난 경우 -> 꽃이 핌
				if (is_red && visited[nx][ny].second == 1 && visited[nx][ny].first == visited[x][y].first + 1) {
					visited[nx][ny].second = 3;
					res++;
					continue;
				}
				else if (!is_red && visited[nx][ny].second == 2 && visited[nx][ny].first == visited[x][y].first + 1) {
					visited[nx][ny].second = 3;
					res++;
					continue;
				}
				// 그렇지 않고, 이미 방문된 칸인 경우 건너띈다.
				else if (visited[nx][ny].second != 0) continue;

				visited[nx][ny].first = visited[x][y].first + 1;
				visited[nx][ny].second = sign;
				q.push({ { nx, ny }, is_red });
			}
		}
	}

	answer = max(answer, res);
}

void pick_culture_medium(int r_cnt, int g_cnt, int idx) {
	if (r_cnt == r && g_cnt == g) {
		// 시뮬레이션 실행 (BFS)
		bfs();
		return;
	}

	if (idx >= v.size())
		return;

	for (int i = idx; i < v.size(); i++) {
		// 빨간 배양액을 심기로 결정한 경우
		if (r_cnt < r) {
			r_picked[i] = true;
			pick_culture_medium(r_cnt + 1, g_cnt, i + 1);
			r_picked[i] = false;
		}
		if (g_cnt < g) {
			// 초록 배양액을 심기로 결정한 경우
			g_picked[i] = true;
			pick_culture_medium(r_cnt, g_cnt + 1, i + 1);
			g_picked[i] = false;
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	cin >> g >> r;


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> garden[i][j];

			if (garden[i][j] == 2) {
				v.push_back({ i, j });
			}
		}
	}

	// 배양액 개수에 따라 배양액을 뿌릴 수 있는 칸을 고른다. -> 백 트래킹
	// 고른 칸에 대해서 배양액을 뿌릴 수 있는 모든 경우의 수에 대해 시뮬레이션을 돌린다. -> 조합 (next_permutation 사용)
	pick_culture_medium(0, 0, 0);

	cout << answer << '\n';

	return 0;
}

// 18개 위치 중 5개 뽑는 경우의 수