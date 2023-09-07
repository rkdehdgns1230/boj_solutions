#include <bits/stdc++.h>

#define MAX 100001
#define X_MAX 2000001

using namespace std;

int n, x;
int arr[MAX];
bool occur[X_MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int ans = 0;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cin >> x;

	for (int i = 0; i < n; i++) {
		if (x - arr[i] > 0 && occur[x - arr[i]]) ans++;
		occur[arr[i]] = true;
	}

	cout << ans;

	return 0;
}