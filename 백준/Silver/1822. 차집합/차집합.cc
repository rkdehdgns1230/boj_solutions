#include <bits/stdc++.h>

using namespace std;

int a, b;

vector<int> A;
vector<int> B;

bool binarySearch(int x) {
	int start = 0;
	int end = b - 1;

	int mid;

	while (start < end) {
		mid = (start + end) / 2;

		if (B[mid] < x) {
			start = mid + 1;
		}
		else if (B[mid] > x) {
			end = mid - 1;
		}
		else {
			return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b;

	for (int i = 0; i < a; i++) {
		int tmp;
		cin >> tmp;
		A.push_back(tmp);
	}

	for (int i = 0; i < b; i++) {
		int tmp;
		cin >> tmp;
		B.push_back(tmp);
	}
	// 정렬한 뒤 이분탐색
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	vector<int> answer;

	for (int i = 0; i < a; i++) {
		int tmp = A[i];

		if (!binary_search(B.begin(), B.end(), tmp)) {
			answer.push_back(tmp);
		}
	}

	cout << answer.size() << "\n";
	for (int i : answer) {
		cout << i << " ";
	}

	return 0;
}