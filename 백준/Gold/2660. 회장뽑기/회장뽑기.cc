#include <bits/stdc++.h>

#define MAX 51
#define INF 51

using namespace std;

int n;
int member_conn[MAX][MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; i++)
		fill(member_conn[i], member_conn[i] + n + 1, INF);

	while (1) {
		int a, b;
		cin >> a >> b;

		if (a == -1 && b == -1) break;

		member_conn[a][b] = 1;
		member_conn[b][a] = 1;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;

				member_conn[i][j] = min(member_conn[i][j], member_conn[i][k] + member_conn[k][j]);
			}
		}
	}

	int chairman = 0;
	int min_score = INF;
	int score[MAX];

	for (int i = 1; i <= n; i++) {
		int cur_score = 0;

		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			cur_score = max(cur_score, member_conn[i][j]);
		}

		score[i] = cur_score;
		min_score = min(min_score, cur_score);
	}
	vector<int> chairman_list;

	for (int i = 1; i <= n; i++) {
		if (score[i] == min_score) {
			chairman_list.push_back(i);
		}
	}

	cout << min_score << " " << chairman_list.size() << "\n";
	for (auto tmp : chairman_list)
		cout << tmp << " ";

	return 0;
}