#include <bits/stdc++.h>

using namespace std;

int n;
string str;

string encod_sig[5];
bool visited[5][20000];

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

bool check(int x, int y) {
	return (0 <= x && x < 5 && 0 <= y && (y < n / 5));
}

void dfs(int x, int y, int& cnt) {
	if (visited[x][y])
		return;
	visited[x][y] = true;
	cnt++;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!check(nx, ny) || visited[nx][ny] || encod_sig[nx][ny] == '.') continue;

		dfs(nx, ny, cnt);
	}
}

// 해독 시작 지점을 받는다.
int encoding_signal(int x, int y) {
	// 모든 숫자가 3칸 점유한다고 가정한다.
	// 1을 제외하고는 모두 3칸을 점유, 또한 검은 색으로 칠해진 칸에 대해서만 해당 함수 호출
	int cnt = 0;
	dfs(x, y, cnt);

	if (cnt == 5) return 1;
	else if (cnt == 7) return 7;
	else if (cnt == 9) return 4;
	else if (cnt == 13) return 8;
	else if (cnt == 11) {
		// 2 or 3 or 5
		if (encod_sig[x + 1][y + 2] == '.')
			return 5;
		else if (encod_sig[x + 3][y + 2] == '#')
			return 3;
		else
			return 2;

	}
	else if (cnt == 12) {
		// 0 or 6 or 9
		if (encod_sig[x + 1][y + 2] == '.')
			return 6;
		else if (encod_sig[x + 2][y + 1] == '#')
			return 9;
		else
			return 0;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	cin >> str;

	int sep = n / 5;
	int idx = 0;

	for (int i = 0; i < 5; i++) {
		encod_sig[i] = str.substr(idx, sep);
		idx += sep;
		//cout << encod_sig[i] << endl;
	}

	for (int i = 0; i < sep; i++) {
		if (visited[0][i]) continue;

		if (encod_sig[0][i] == '#') {
			cout << encoding_signal(0, i);
		}
	}

	return 0;
}