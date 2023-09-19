#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	vector<int> v;

	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}

	if (prev_permutation(v.begin(), v.end())) {
		for (int num : v) {
			cout << num << " ";
		}
	}
	else {
		cout << "-1\n";
	}

	return 0;
}