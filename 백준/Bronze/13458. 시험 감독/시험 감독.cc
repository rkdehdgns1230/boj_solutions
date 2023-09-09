#include <bits/stdc++.h>

#define MAX 1000001

using namespace std;

int n, b, c;
int arr[MAX];

int main() {
	long long answer = 0;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cin >> b >> c;

	for (int i = 0; i < n; i++) {
		answer += 1; 
		if (arr[i] < b)
			continue;

		answer += ((arr[i] - b) / c);
		answer += ((arr[i] - b) % c == 0 ? 0 : 1);
	}

	cout << answer << "\n";

	return 0;
}