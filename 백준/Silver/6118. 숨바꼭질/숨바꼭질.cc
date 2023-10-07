#include <bits/stdc++.h>

#define MAX 20001
#define INF 20001

using namespace std;

int n, m;

int sta = 1; // 재서기의 위치

vector<int> barn[MAX];

void dijkstra() {
	queue<int> q;
	q.push(1);

	int d[MAX];
	fill(d, d + MAX, INF);
	d[1] = 0;

	while (!q.empty()) {
		int x = q.front();
		q.pop();

		// x 헛간과 연결된 헛간들 방문
		for (int i = 0; i < barn[x].size(); i++) {
			int y = barn[x][i];

			if (d[y] > d[x] + 1) {
				d[y] = d[x] + 1;
				q.push(y);
			}
		}
	}

	int res = *max_element(d + 1, d + n + 1);
	int cnt = 0;
	int idx = 0;

	for (int i = 1; i <= n; i++) {
		if (d[i] == res) {
			if (idx == 0)
				idx = i;
			cnt++;
		}
	}

	cout << idx << " " << res << " " << cnt << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		barn[a].push_back(b);
		barn[b].push_back(a);
	}

	dijkstra();

	return 0;
}