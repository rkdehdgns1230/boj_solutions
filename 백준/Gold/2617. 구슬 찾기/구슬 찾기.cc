#include <bits/stdc++.h>

#define MAX 100

using namespace std;

int n, m;

vector<int> heavier[MAX];
vector<int> lighter[MAX];

bool visited[MAX];

bool bfs(int x, vector<int> adj[]) {
	fill(visited, visited + n + 1, false);
	visited[x] = true;

	queue<int> q;
	q.push(x);

	int cnt = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int nxt : adj[cur]) {
			if (visited[nxt]) continue;
			visited[nxt] = true;
			cnt++;
			q.push(nxt);
		}
	}
	return cnt >= (n + 1) / 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		heavier[a].push_back(b);
		lighter[b].push_back(a);
	}

	int answer = 0;

	for (int i = 1; i <= n; i++) {
		if (bfs(i, heavier) || bfs(i, lighter))
			answer++;
	}

	cout << answer;

	return 0;
}

/*
(N + 1) / 2 번째 구슬만 아니면 된다.
무거운 기준이든, 가벼운 기준이든 확실히 무겁고 가벼운 것이 (N + 1) / 2개를 넘기면
중간인 구슬이 될 수 없음을 의미한다.

개수가 그것보다 작으면, 중간인 구슬이 될 가능성이 있다.
*/