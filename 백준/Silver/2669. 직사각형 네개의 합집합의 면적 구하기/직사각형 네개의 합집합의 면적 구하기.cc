#include <bits/stdc++.h>

using namespace std;

int rectangles[101][101];

int main() {
	int answer = 0;

	for (int i = 0; i < 4; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		for (int j = x1; j < x2; j++) {
			for (int k = y1; k < y2; k++) {
				rectangles[j][k] = 1;
			}
		}
	}

	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			if (rectangles[i][j] == 1)
				answer++;
		}
	}

	cout << answer;

	return 0;
}