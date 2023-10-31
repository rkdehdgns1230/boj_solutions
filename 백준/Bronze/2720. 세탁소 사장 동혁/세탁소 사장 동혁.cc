#include <bits/stdc++.h>

using namespace std;

int n, t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;

	int quarter = 25, dime = 10, nickel = 5, penny = 1;

	while (t--) {
		cin >> n;
		int ans[] = { 0, 0, 0, 0 };
		while (n >= quarter) {
			n -= quarter;
			ans[0]++;
		}

		while (n >= dime) {
			n -= dime;
			ans[1]++;
		}

		while (n >= nickel) {
			n -= nickel;
			ans[2]++;
		}

		while (n >= penny) {
			n -= penny;
			ans[3]++;
		}

		cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
	}

	return 0;
}