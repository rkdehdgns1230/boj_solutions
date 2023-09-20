#include <bits/stdc++.h>

using namespace std;

int arr[9];
int pick[9];
int n, m;

void backtracking(int idx, int cnt) {
	if (cnt == m) {
		for (int i = 0; i < cnt; i++) {
			cout << arr[pick[i]] << " ";
		}cout << "\n";
	}

	for (int i = idx; i < n; i++) {
		pick[cnt] = i;
		backtracking(i + 1, cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + n);

	backtracking(0, 0);

	return 0;
}