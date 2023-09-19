#include <bits/stdc++.h>

#define MAX 400

using namespace std;

int rectangle[MAX][MAX];

int n;

// len 길이의 사각형을 (x, y)를 중심으로 그린다.
void drawRectangle(int len, int x, int y) {
	if (len == 1) {
		rectangle[x][y] = 1;
		return;
	}

	int side = len / 2; // len은 홀수임
	for (int i = x - side; i <= x + side; i++) {
		rectangle[i][y - side] = 1; rectangle[i][y + side] = 1;
	}
	for (int j = y - side; j <= y + side; j++) {
		rectangle[x - side][j] = 1; rectangle[x + side][j] = 1;
	}

	drawRectangle(len - 4, x, y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int length = (4 * n - 3);
	int mid_x = length / 2 + 1;
	int mid_y = length / 2 + 1;

	drawRectangle(length, mid_x, mid_y);

	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			if (rectangle[i][j] == 1)
				cout << "*";
			else
				cout << " ";
		}cout << "\n";
	}

	return 0;
}