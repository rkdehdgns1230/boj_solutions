#include <bits/stdc++.h>
#define MAX 301

using namespace std;

int n, m, r;
int arr[MAX][MAX];

void rotate(int sta_x, int sta_y, int end_x, int end_y) {
	int tmp = arr[sta_x][sta_y];

	int x = sta_x, y = sta_y;

	while (y != end_y) {
		arr[x][y] = arr[x][y + 1];
		y++;
	}

	while (x != end_x) {
		arr[x][y] = arr[x + 1][y];
		x++;
	}

	while (y != sta_y) {
		arr[x][y] = arr[x][y - 1];
		y--;
	}

	while (x != sta_x) {
		arr[x][y] = arr[x - 1][y];
		x--;
	}

	arr[sta_x + 1][sta_y] = tmp;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> r;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	while (r--) {
		int tmp_n = n - 1;
		int tmp_m = m - 1;

		int sta_n = 0;
		int sta_m = 0;

		while (tmp_n >= sta_n && tmp_m >= sta_m) {
			rotate(sta_n, sta_m, tmp_n, tmp_m);
			sta_n++;
			sta_m++;
			tmp_n--; 
			tmp_m--;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}

	return 0;
}