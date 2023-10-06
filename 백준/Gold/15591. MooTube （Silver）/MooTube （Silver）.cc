#include <bits/stdc++.h>

#define MAX 5001
#define INF 1000000001

using namespace std;

vector<pair<int, int>> usado[MAX];

int n, q;

void bfs(int x, int k) {
	int ans = 0;
	queue<pair<int, int >> q;
	vector<bool> visited(n + 1, false);
	visited[x] = true;

	q.push({ INF, x });
	
	while (!q.empty()) {
		int y = q.front().second;
		int dis = q.front().first;
		q.pop();

		if (dis < k) continue;

		for (int i = 0; i < usado[y].size(); i++) {
			int next = usado[y][i].first;
			int next_dis = min(dis, usado[y][i].second);

			if (visited[next]) continue;

			if (k <= next_dis) {
				ans++;
				visited[next] = true;
				q.push({ next_dis, next });
			}
		}
	}
	cout << ans << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < n - 1; i++) {
		int p, q, r;
		cin >> p >> q >> r;

		usado[p].push_back({ q, r });
		usado[q].push_back({ p, r });
	}

	for (int i = 0; i < q; i++) {
		int k, v;

		cin >> k >> v;

		bfs(v, k);
	}

	return 0;
}