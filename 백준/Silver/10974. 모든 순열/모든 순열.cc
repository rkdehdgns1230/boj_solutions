#include <bits/stdc++.h>
#define MAX 9

using namespace std;

int n;
vector<int> res;
bool visited[MAX];

void backtracking(int cnt) {
	if (cnt == n) {
		for (int i = 0; i < n; i++) {
			cout << res[i] << " ";
		}cout << "\n";
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (visited[i]) continue;

		res[cnt] = i;
		visited[i] = true;
		backtracking(cnt + 1);
		visited[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	res = vector<int>(n, 0);

	backtracking(0);

	return 0;
}