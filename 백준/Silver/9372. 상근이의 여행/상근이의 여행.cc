#include <bits/stdc++.h>
#define MAX 1001

using namespace std;

int t;
int n, m;

vector<int> world[MAX];

int bfs() {
	int res = 0;

	queue<int> q;
	q.push(1);

	vector<bool> visited(n + 1, false);
	visited[1] = true;

	while (!q.empty()) {
		int x = q.front();
		q.pop();

		for (int i = 0; i < world[x].size(); i++) {
			int y = world[x][i];

			if (visited[y]) continue;
			visited[y] = true;
			res++;
			
			q.push(y);
		}
	}
	
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	while (t--) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++) {
			world[i].clear();
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;

			world[a].push_back(b);
			world[b].push_back(a);
		}

		cout << bfs() << "\n";
	}

	return 0;
}