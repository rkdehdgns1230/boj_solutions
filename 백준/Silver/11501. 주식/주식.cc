#include <bits/stdc++.h>

using namespace std;

int t, n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	while (t--) {
		cin >> n;
		vector<int> arr(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		int max_val = arr[n - 1];

		long long ans = 0;
		for (int i = n - 2; i >= 0; i--) {
			if (max_val < arr[i]) {
				max_val = arr[i];
			}
			ans += (max_val - arr[i]);
		}
		cout << ans << "\n";
	}

	return 0;
}