#include <bits/stdc++.h>

#define MAX 65
#define endl '\n'
using namespace std;

int n, q;

int world_map[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int biggest_iceberg = 0;

int calc_pow(int a, int p) {
	int res = 1;
	for (int i = 0; i < p; i++) {
		res *= a;
	}
	return res;
}

void rotate_clock_dir(int x, int y, int nx, int ny) {
	int tmp[MAX][MAX];
	for (int i = x; i < nx; i++)
		for (int j = y; j < ny; j++)
			tmp[i - x][j - y] = world_map[i][j];

	
	for (int i = 0; i < nx - x; i++) {
		for (int j = 0; j < ny - y; j++) {
			world_map[x + i][y + j] = tmp[ny - y - 1 - j][i];
		}
	}
	/*cout << x << ", " << y << " " << nx << ", " << ny << endl;
	cout << "뭐가 또 문제여\n";*/
}

void fire_storm(int L, int l, int x, int y, int map_size) {
	// 원하는 레벨에 도달한 경우

	if (L == l) {
		int len = calc_pow(2, L);
		// x ~ x + level, y ~ y + level 범위의 칸을 90도 회전시킨다.
		rotate_clock_dir(x, y, x + len, y + len);

		return;
	}
	// 4개의 칸으로 쪼개야 한다.
	int len = calc_pow(2, l - 1);

	fire_storm(L, l - 1, x, y, map_size);
	fire_storm(L, l - 1, x + len, y, map_size);
	fire_storm(L, l - 1, x, y + len, map_size);
	fire_storm(L, l - 1, x + len, y + len, map_size);
}

bool check(int x, int y, int map_size) {
	return (0 <= x && x < map_size && 0 <= y && y < map_size);
}

void melt(int map_size) {
	queue<pair<int, int >> q;

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			int cnt = 0;
			// 이미 녹은 얼음은 건너띈다.
			if (world_map[i][j] <= 0) continue;

			for (int k = 0; k < 4; k++) {
				int x = i + dx[k];
				int y = j + dy[k];

				// 맵 밖이거나, 얼음이 없는 경우 카운트 X
				if (!check(x, y, map_size) || world_map[x][y] <= 0) continue;
				cnt++;
			}
			if (cnt < 3)
				q.push({ i, j });
		}
	}

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		// 얼음을 녹인다.
		world_map[x][y]--;
	}
}

bool visited[MAX][MAX];

// 얼음 덩어리 구하기 위함
void bfs(int x, int y, int map_size) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;

	int res = 0;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		q.pop();
		res++;

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (!check(nx, ny, map_size) || visited[nx][ny] || world_map[nx][ny] == 0) continue;

			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}

	biggest_iceberg = max(biggest_iceberg, res);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;
	int answer = 0;
	int map_size = calc_pow(2, n);

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			cin >> world_map[i][j];
		}
	}

	for (int i = 0; i < q; i++) {
		int l;
		cin >> l;

		fire_storm(l, n, 0, 0, map_size);
		melt(map_size);

		/*cout << " =================== " << endl;
		for (int i = 0; i < map_size; i++)
		{
			for (int j = 0; j < map_size; j++)
				cout << world_map[i][j] << " ";
			cout << "\n";
		}*/
	}

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++)
			if (world_map[i][j] > 0) {
				answer += world_map[i][j];
				
				if (!visited[i][j]) {
					bfs(i, j, map_size);
				}
			}
	}
	cout << answer << endl;
	cout << biggest_iceberg;
	return 0;
}