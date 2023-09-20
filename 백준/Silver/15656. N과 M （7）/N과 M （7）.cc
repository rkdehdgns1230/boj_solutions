#include <bits/stdc++.h>

using namespace std;

int n, m;

int pick[10];
int arr[10];

void backtracking(int cnt) {
	if (cnt == m) {
		for (int i = 0; i < cnt; i++) {
			cout << arr[pick[i]] << " ";
		}cout << "\n";
		return;
	}
	
	for (int i = 0; i < n; i++) {
		pick[cnt] = i;
		backtracking(cnt + 1);
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

	backtracking(0);

	return 0;
}