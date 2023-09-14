#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	queue<int> q;

	cin >> N;

	for (int i = 1; i <= N; i++) {
		q.push(i);
	}

	while (1) {
		// 1. 제일 위에 있는 카드를 바닥에 버린다.
		cout << q.front() << " ";
		q.pop();

		if (q.empty()) break;

		// 2. 제일 위에 있는 카드를 제일 아래에 있는 카드 아래로 옮긴다.
		int tmp = q.front();
		q.pop();
		q.push(tmp);
	}

	return 0;
}