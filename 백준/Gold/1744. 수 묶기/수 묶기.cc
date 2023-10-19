#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	// 1. 숫자를 크기 순으로 정렬
	// 2. 가장 큰 두 개의 숫자를 선택
	// 3. 두 수의 곱이 합보다 큰 경우 곱해서 더한다.
	// 4. 합이 더 큰 경우가 나올때까지 2, 3번 과정 반복
	vector<int> arr(n, 0);
	vector<bool> used(n, false);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.end(), greater<>());

	int answer = 0;
	int idx = 0;
	
	int zero_idx = n - 1;

	for (int i = 0; i < n; i++) {
		if (arr[i] <= 0)
		{
			zero_idx = i - 1;
			break;
		}
	}

	//cout << "0보다 큰 마지막 위치: " << zero_idx << endl;

	if (n == 1) {
		cout << arr[0];
		return 0;
	}

	int prev = arr[0];
	for (int i = 1; i <= zero_idx; i++) {
		int cur = arr[i];

		// 이미 묶인 수는 건너띈다.
		if (used[i - 1]) {
			//cout << i - 1 << "번째 수는 이미 묶여서 " << i << "번째와 비교 X" << endl;
			prev = cur;
			continue;
		}

		//<-- 더하는게 나은 경우 -->
		// 양수, 1의 곱
		else if (prev > 0 && cur == 1) {
			//cout << "양수에서 더하는 케이스 " << endl;
			//cout << prev << " " << cur << endl;

			used[i - 1] = true;
			answer += prev;
			prev = cur;
			continue;
		}
		
		//<-- 묶는게 유리한 경우 -->
		answer += (prev * cur);
		//cout << prev << "와 " << cur << "은 묶는게 유리\n";
		//cout << answer << endl;
		prev = cur;
		used[i] = true;
		used[i - 1] = true;
	}

	if (zero_idx >= 0 && !used[zero_idx]) {
		answer += arr[zero_idx];
	}


	for (int i = n - 1; i > zero_idx; i -= 2) {
		// 이전 원소 조회가 가능한 경우에만
		if (i - 1 > zero_idx) {
			int a = arr[i];
			int b = arr[i - 1];

			// 음수 * 음수 or 음수 * 0 조합은 묶는게 무조건 유리
			answer += (a * b);
			//cout << a <<", " << b << "묶어준다. \n";
		}
		else {
			// 마지막 하나의 0 or 음수는 더할 수 밖에
			answer += arr[i];
		}
	}

	/*for (int i = n - 2; i > zero_idx; i--) {
		int cur = arr[i];

		if (used[i + 1]) {
			prev = cur;
			continue;
		}

		cout << "음수와의 조합은 곱하는게 유리 " << prev << ", " << cur << endl;
		answer += (prev * cur);
		prev = cur;
		used[i + 1] = true;
		used[i] = true;
	}
	if (zero_idx + 1 < n && !used[zero_idx + 1])
		answer += arr[zero_idx + 1];*/

	cout << answer << endl;

	return 0;
}

// 양수, 0 -> 무조건 더하는게 유리 continue
// 양수, 1 -> 무조건 더하는게 유리 continue
// 양수, 음수 -> 무조건 더하는게 유리 continue
// 양수, 양수 (둘 다 1 x) -> 무조건 묶는게 유리 <--

// 음수, 음수 -> 무조건 묶는게 유리 <--
// 음수, 0 -> 무조건 묶는게 유리 <--


// 다만, 음수의 경우 더 작은 쪽부터 살펴야 위 경우가 성립함에 유의하자.
// 이에 따라서 0 ~ 음수는 반대로 탐색해야 한다.