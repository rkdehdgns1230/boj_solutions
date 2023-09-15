#include <bits/stdc++.h>
#define MAX 51
#define INF 1301

using namespace std;

int n, m;
int arr[MAX][MAX];

vector<pair<int, int>> chicken;
vector<pair<int, int>> house;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 2)
				chicken.push_back({ i, j });
			else if (arr[i][j] == 1)
				house.push_back({ i, j });
		}
	}

	vector<int> brute(chicken.size(), 1);
	fill(brute.begin(), brute.begin() + chicken.size() - m, 0); // 뒤의 m개의 칸에만 1을 기입

	int answer = INF;

	do {
		int chicken_distance = 0;

		for (auto it : house) {
			int tmp = INF;
			for (int i = 0; i < chicken.size(); i++) {
				// 폐업 대상은 건너 띈다.
				if (brute[i] == 0)
					continue;

				tmp = min(tmp, (abs(chicken[i].first - it.first) + abs(chicken[i].second - it.second)));
			}
			chicken_distance += tmp;
		}

		answer = (answer > chicken_distance) ? chicken_distance : answer;

	} while (next_permutation(brute.begin(), brute.end()));

	cout << answer;

	return 0;
}