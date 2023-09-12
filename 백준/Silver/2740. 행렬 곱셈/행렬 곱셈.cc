#include <bits/stdc++.h>

#define MAX 101

using namespace std;

int n, m, k;

int a[MAX][MAX];
int b[MAX][MAX];
int arr[MAX][MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	cin >> m >> k;

	for (int i = 0; i < m; i++) 
		for (int j = 0; j < k; j++)
			cin >> b[i][j];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			// i행 j열의 원소 값을 구하기 위해 sum of (a[i][s] * b[s][j]) 값을 구해야 한다.
			int sum = 0;
			for (int s = 0; s < m; s++) {
				sum += (a[i][s] * b[s][j]);
			}
			arr[i][j] = sum;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << arr[i][j] << " ";
		}cout << "\n";
	}

	return 0;
}