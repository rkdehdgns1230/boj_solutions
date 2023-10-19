#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	int answer = 0;
	cin >> n;

	vector<int> arr(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int prev = arr[n - 1];
	
	for (int i = n - 2; i >= 0; i--) {
		int cur = arr[i];

		if (prev <= cur) {
			answer += (cur - prev + 1);
			arr[i] -= (cur - prev + 1);
		}
		prev = arr[i];
	}

	cout << answer << endl;

	return 0;
}