#include <bits/stdc++.h>

using namespace std;

string students[6];


int answer = 0;

bool points[25];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0 ,0, -1, 1 };

bool check(int x, int y) {
	return (0 <= x && x < 5 && 0 <= y && y < 5);
}

bool bfs() {
	queue<pair<int, int>> q;

	// 0으로 초기화
	bool visited[5][5] = {};
	bool student_map[5][5] = {};

	for (int i = 0; i < 25; i++) {
		// 칠공주파 후보 여부 판단
		if (points[i]) {
			int x = i / 5;
			int y = i % 5;

			student_map[x][y] = true;

			// 첫 시작점을 위해 큐에 넣는다.
			if (q.empty()) {
				q.push({ x, y });
				visited[x][y] = true;
			}
		}
	}

	int adj_num = 0;
	int dasom_num = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		adj_num++;
		if (students[x][y] == 'S')
			dasom_num++;

		if (7 - adj_num + dasom_num < 4)
			return false;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!check(nx, ny) || visited[nx][ny] || !student_map[nx][ny])
				continue;

			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}

	// 모두 인접한지 && 다솜파 수가 더 많은지
	return adj_num == 7 && dasom_num >= 4;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	for (int i = 0; i < 5; i++) {
		cin >> students[i];
	}

	// 25명 중 7명을 뽑아서 -> 모든 경우의 수 탐색
	// 서로 인접해있는지 여부는 BFS로 판단

	// 1은 7개만 -> next_permutation을 이용해 조합을 구현할 예정
	fill(points + 18, points + 25, true);

	// 모든 순열 조합을 확인한다.
	do {
		int x, y;
		// 서로 인접한지 여부 + 이다솜파 인원 수 확인
		if (!bfs())
			continue;

		answer++;

	} while (next_permutation(points, points + 25));
	
	cout << answer << "\n";


	return 0;
}