#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	priority_queue<long long> pq;

	for (int i = 0; i < n; i++) {
		long long tmp;
		cin >> tmp;
		pq.push(-tmp);
	}

	while (m--) {
		long long tmp1 = -pq.top(); pq.pop();
		long long tmp2 = -pq.top(); pq.pop();

		pq.push(-(tmp1 + tmp2));
		pq.push(-(tmp1 + tmp2));
	}

	long long answer = 0;
	while (!pq.empty()) {
		answer += (-pq.top());
		pq.pop();
	}

	cout << answer;

	return 0;
}