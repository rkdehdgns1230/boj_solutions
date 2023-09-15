#include <bits/stdc++.h>
#define MAX 1001

using namespace std;

int n, w, l; // 트럭의 수, 다리의 길이, 최대 하중

int truck[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> w >> l;

	for (int i = 0; i < n; i++) {
		cin >> truck[i];
	}

	int cur_time = 0;
	int idx = 0; // truck index
	queue<pair<int, int>> q; // first: 올라간 시간, second: 트럭 번호
	int cur_load = 0;

	do {
		// 트럭이 다리를 다 건넌 경우
		if (!q.empty() && cur_time - q.front().first >= w) {
			cur_load -= truck[q.front().second];
			q.pop();
		}

		// 현재 w대 이상 존재하는 경우 더 이상 트럭 올라갈 수 없다.
		// 현재 다리에 올라갈 수 있는 경우 (차선이 하나라 한 대만 올라갈 수 있음)
		if (q.size() < w && cur_load + truck[idx] <= l && idx < n) {
			cur_load += truck[idx];
			q.push({ cur_time, idx++ });
		}

		cur_time++;
	} while (!q.empty());


	cout << cur_time;

	return 0;
}