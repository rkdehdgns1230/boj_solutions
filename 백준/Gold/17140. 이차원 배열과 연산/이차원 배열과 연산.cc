#include <bits/stdc++.h>

#define MAX 101 // 배열의 최대 크기는 100 x 100

using namespace std;

int r, c, k;

int arr[MAX][MAX];

int cur_r_len = 3;
int cur_c_len = 3;

bool check() {
	return arr[r - 1][c - 1] == k;
}

// R 연산
void r_op() {
	for (int i = 0; i < cur_r_len; i++) {
		priority_queue<pair<int, int>> pq;
		vector<int> num_cnt(MAX, 0);

		// i행에 속한 수의 개수를 센다.
		for (int j = 0; j < cur_c_len; j++) {
			if (arr[i][j] == 0) continue;
			num_cnt[arr[i][j]]++;
			arr[i][j] = 0; // 0으로 초기화 해줘야 함.
		}

		for (int j = 1; j <= 100; j++) {
			if (num_cnt[j] == 0) continue;

			// 오름 차순 정렬을 위해 - 부호를 붙여서 넣는다.
			pq.push({ -num_cnt[j], -j});
		}

		int idx = 0;
		// 100개의 수 까지만 배열에 다시 담는다.
		while (!pq.empty()) {
			arr[i][idx++] = -pq.top().second;
			if (idx >= 100)
				break;

			arr[i][idx++] = -pq.top().first;
			if (idx >= 100)
				break;
			pq.pop();
		}
		cur_c_len = max(cur_c_len, idx);
	}
}

// C 연산
void c_op() {
	for (int i = 0; i < cur_c_len; i++) {
		priority_queue<pair<int, int>> pq;
		vector<int> num_cnt(MAX, 0);

		// i열에 속한 수의 개수를 센다.
		for (int j = 0; j < cur_r_len; j++) {
			if (arr[j][i] == 0) continue;
			num_cnt[arr[j][i]]++;
			arr[j][i] = 0; // 0으로 초기화 해줘야 함.
		}

		for (int j = 1; j <= 100; j++) {
			if (num_cnt[j] == 0) continue;

			// 오름 차순 정렬을 위해 - 부호를 붙여서 넣는다.
			pq.push({ -num_cnt[j], -j });
		}

		int idx = 0;
		// 100개의 수 까지만 배열에 다시 담는다.
		while (!pq.empty()) {
			arr[idx++][i] = -pq.top().second;
			if (idx >= 100)
				break;

			arr[idx++][i] = -pq.top().first;
			if (idx >= 100)
				break;
			pq.pop();
		}
		cur_r_len = max(cur_r_len, idx);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> c >> k;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> arr[i][j];

	int cnt = 100;
	bool is_success = false;

	// 별도의 작업 없이 성공 가능한 경우
	if (check()) {
		cout << 0;
		return 0;
	}

	// 100번 까지만 실행
	while (cnt--) {
		if (cur_r_len >= cur_c_len)
			r_op();
		else
			c_op();
		
		if (check()) {
			cout << 100 - cnt;
			is_success = true;
			break;
		}
	}

	if (!is_success) {
		cout << -1;
	}

	return 0;
}


/*
<정렬 기준>
- 수의 등장 횟수에 대한 오름차순
- 등장 횟수가 동일하다면, 수의 오름차순

정렬한 뒤에 배열 A에 정렬된 결과를 다시 넣어야 한다.
정렬 결과로는 수와 수의 등장 횟수를 같이 넣어야 하며, (수, 등장 횟수) 형태로 넣는다.

행 또는 열의 크기가 100을 넘으면, 넘는 수들은 버린다.

ex) [3, 1, 1] -> 정렬 -> [3, 1, 1, 2]
ex) [3, 1, 1, 2] -> 정렬 -> [2, 1, 3, 1, 1, 2]

연산 수행 이후에는 최대 열 or 행의 길이에 따라 배열의 크기가 달라진다. (빈 공간에는 0이 채워진다)

** 정렬 연산 시에 0은 무시해야 한다. **

<연산 수행 기준>
행 개수 >= 열 개수 -> 행 연산
행 개수 < 열 개수 -> 열 연산

행, 열 연산은 모든 행과 모든 열에 적용한다.
*/