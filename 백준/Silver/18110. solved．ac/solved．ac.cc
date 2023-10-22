#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;

	vector<int> arr(n, 0);

	int e = round(n * 0.15);

	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.end());

	int sum = 0;
	for (int i = e; i < n - e; i++) {
		sum += arr[i];
		//cout << arr[i] << endl;
	}

	cout << round((double) sum / (n - 2 * e)) << endl;

	return 0;
}