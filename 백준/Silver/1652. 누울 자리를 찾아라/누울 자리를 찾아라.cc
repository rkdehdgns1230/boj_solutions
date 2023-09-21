#include <bits/stdc++.h>

#define MAX 101

using namespace std;

string room[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> room[i];
	}

	int horizontal_cnt = 0;
	int parallel_cnt = 0;

	for (int i = 0; i < n; i++) {
		int cnt = 0;

		for (int j = 0; j < n; j++) {
			if (room[i][j] == '.')
				cnt++;
			else {
				if (cnt >= 2)
					parallel_cnt++;
				cnt = 0;
			}
		}
		if (cnt >= 2)
			parallel_cnt++;
	}

	for (int i = 0; i < n; i++) {
		int cnt = 0;

		for (int j = 0; j < n; j++) {
			if (room[j][i] == '.')
				cnt++;
			else {
				if (cnt >= 2)
					horizontal_cnt++;
				cnt = 0;
			}
		}
		if (cnt >= 2)
			horizontal_cnt++;
	}


	cout << parallel_cnt << " " << horizontal_cnt << "\n";

	return 0;
}