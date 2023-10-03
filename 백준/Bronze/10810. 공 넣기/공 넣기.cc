#include <bits/stdc++.h>
#define MAX 101

using namespace std;

int n, m;

int basket[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b, num;
		cin >> a >> b >> num;

		for (int j = a; j <= b; j++) {
			basket[j] = num;
		}
	}


	for (int i = 1; i <= n; i++) {
		cout << basket[i] << " ";
	}

	return 0;
}