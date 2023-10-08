#include <bits/stdc++.h>
#define MAX 101

using namespace std;

int n;

int world[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int cnt = 1;

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

// 각 섬에 소속된 영역에 식별자 부여
void island() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (world[i][j] == 0 || visited[i][j]) continue;

			cnt++;

			queue<pair<int, int>> q;
			q.push({ i, j });
			visited[i][j] = true;

			while (!q.empty()) {
				int x = q.front().first;
				int y = q.front().second;
				q.pop();
				world[x][y] = cnt;

				for (int i = 0; i < 4; i++) {
					int nx = x + dx[i];
					int ny = y + dy[i];

					if (!check(nx, ny) || world[nx][ny] == 0 || visited[nx][ny]) continue;
					visited[nx][ny] = true;
					q.push({ nx, ny });
				}
			}

		}
	}
}

// a와 b간의 최소 거리를 구한다.
int min_bridges(pair<int, int> a) {
	queue<pair<int, int>> q;
	q.push(a);

	int d[MAX][MAX];
	for (int i = 0; i < n; i++)
		fill(d[i], d[i] + n, -1);

	d[a.first][a.second] = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!check(nx, ny) || d[nx][ny] >= 0 || (world[a.first][a.second] == world[nx][ny])) continue;

			d[nx][ny] = d[x][y] + 1;
			q.push({ nx, ny });

			if ((world[a.first][a.second] != world[nx][ny]) && world[nx][ny] != 0) {
				return d[x][y];
			}
		}
	}
	// 다른 육지에 도달하지 못한 경우
	return -1;
}

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << world[i][j] << " ";
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int answer = 1000001;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			cin >> world[i][j];
	
	island();

	//print();

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (world[x][y] == 0)
				continue;

			// 육지의 임의이 좌표를 골라, 가장 가까운 다른 섬으로의 거리를 구한다.
			int cur_min = min_bridges({ x, y });
			if (cur_min == -1) continue;

			answer = min(answer, cur_min);
		}
	}

	cout << answer;

	return 0;
}