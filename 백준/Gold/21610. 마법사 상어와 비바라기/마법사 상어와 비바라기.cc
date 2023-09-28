#include <bits/stdc++.h>

#define MAX 51

using namespace std;

int n, m;

int world_map[MAX][MAX];
bool isCloudy[MAX][MAX];

int dx[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

bool check(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void bibaragi() {
	isCloudy[n][1] = true;
	isCloudy[n][2] = true;
	isCloudy[n-1][1] = true;
	isCloudy[n-1][2] = true;
}

// d 방향으로 s 만큼 구름을 이동시킨다.
void moveCloud(int d, int s) {
	queue<pair<int, int>> q;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (isCloudy[i][j]) {
				q.push({ i, j });
				isCloudy[i][j] = false;
			}
		}
	}

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		// d 방향으로 s만큼 이동
		x += (dx[d] * s);
		y += (dy[d] * s);

		if (x > n) {
			x = (x % n == 0) ? n : x % n;
		}
		// x가 음수인 경우 양수가 될 때 까지 이동
		else if (x <= 0) {
			x = n + (x % n); // -3 (1에서 왼쪽으로 네 칸) -> 5 - 3 = 2
		}

		if (y > n) {
			y = (y % n == 0) ? n : y % n;
		}
		// y가 음수인 경우 양수가 될 때 까지 이동
		else if (y <= 0) {
			y = n + (y % n);
		}
		//cout << "좌표 이동 : " << x << ", " << y << endl;
		// 구름 이동 + 물의 양 증가 한 번에 처리
		isCloudy[x][y] = true;
		world_map[x][y] += 1;
	}
}

// 물 복사 마법 시전 (물 증가한 칸 == 구름 있는 칸)
// 구름 제거하고, 물 증가시키고, 새로운 구름 생성
void magic() {
	queue<pair<int, int>> gureum; // queue 활용해 구름 중복 생성하는 경우 제거

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (isCloudy[i][j]) {
				gureum.push({ i, j });
			}
		}
	}
	
	// 2, 4, 6, 8 방향이 대각선 방향
	int d[] = { 2, 4, 6, 8 };

	// 대각선 확인하며, 구름이 있는 칸의 개수를 센다.
	while (!gureum.empty()) {
		int x = gureum.front().first;
		int y = gureum.front().second;
		gureum.pop();

		int cnt = 0;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[d[i]];
			int ny = y + dy[d[i]];

			// 대각선 확인은 범위 내에서만 한다.
			if (!check(nx, ny))
				continue;

			if (world_map[nx][ny] > 0)
				cnt++;
		}
		// 대각선 칸에 물이 담긴 만큼 물 복사 마법 시전
		world_map[x][y] += cnt;
	}

	// 미리 물의 양이 2칸이 넘는 경우 구름을 생성 (구름 없는 칸에서만 구름 생성 가능)
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (world_map[i][j] >= 2 && !isCloudy[i][j]) {
				isCloudy[i][j] = true;
				world_map[i][j] -= 2;
			}
			else if (isCloudy[i][j]) {
				isCloudy[i][j] = false;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> world_map[i][j];

	// 비바라기는 초기에 시전
	bibaragi();

	for (int i = 0; i < m; i++) {
		int d, s;
		cin >> d >> s;

		moveCloud(d, s);

		/*for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				cout << isCloudy[j][k] << " ";
			}
			cout << endl;
		}*/

		magic();
	}

	int answer = 0;

	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= n; k++) {
			//cout << isCloudy[j][k] << " ";
			answer += world_map[j][k];
		}
		//cout << endl;
	}

	cout << answer;

	return 0;
}

// 비바라기 시전: (N, 1), (N, 2), (N-1, 1), (N-1, 2) 비구름 생성 (초기에만 실행)

// 구름 이동 가능 방향 8가지 (대각선 방향 포함)
// 이동 가능칸 최대 50칸, 범위 밖으로 벗어나면 -> 모든 경계 연결된 것 마냥 좌표 이동

// 물복사버그 마법 -> 구름에 의해 물이 증가한 칸 기준, 대각선 1칸씩 칸에 물이 있는 수만큼 해당 칸에 물이 복사됨

// 이후 물이 두 칸 이상 차있는 바구니에서 구름이 생성된다. (기존 실행에 의해 구름이 제거된 칸은 제외한다)