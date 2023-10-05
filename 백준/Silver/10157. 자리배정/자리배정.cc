#include <bits/stdc++.h>

#define MAX 1001

using namespace std;

int c, r;
int k;

bool show_room[MAX][MAX];

bool check(int x, int y) {
	return (0 <= x && x < c && 0 <= y && y < r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> c >> r;
	cin >> k;
	int cnt = 1;
	
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	int dir = 0;

	int x = 0, y = 0;

	if (k > c * r) {
		cout << 0;
		return 0;
	}
	if (k == 1) {
		cout << "1 1\n";
		return 0;
	}

	show_room[x][y] = true;

	while (1) {
		//cout << dir << " 방향으로 이동\n";

		while(1) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (show_room[nx][ny] || !check(nx, ny))
				break;

			//cout << nx << ", " << ny << "\n";

			show_room[nx][ny] = true;
			x = nx, y = ny;
			cnt++;

			if (cnt == k) {
				cout << x + 1 << " " << y + 1 << "\n";
				return 0;
			}
		}

		dir++;
		dir %= 4;
	}

	return 0;
}