#include <bits/stdc++.h>

using namespace std;

int n;

int graph[3][3];
bool visited[3][3];

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void dfs(int x, int y) {
	if (!check(x, y) || visited[x][y]) return;

	if (graph[x][y] == -1) {
		visited[x][y] = true;
		return;
	}

	visited[x][y] = true;

	dfs(x + graph[x][y], y);
	dfs(x, y + graph[x][y]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> graph[i][j];

	dfs(0, 0);

	if (visited[n - 1][n - 1])
		cout << "HaruHaru\n";
	else
		cout << "Hing\n";

	return 0;
}