#include<bits/stdc++.h>

#define MAX 101

using namespace std;

int k;
int math_test[MAX][51];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k;

	for (int i = 1; i <= k; i++) {
		int n;
		cin >> n;

		for (int j = 0; j < n; j++) {
			cin >> math_test[i][j];
		}
		sort(math_test[i], math_test[i] + n);

		int max_num = math_test[i][0];
		int min_num = math_test[i][0];
		int lar_gap = 0;

		int prev = math_test[i][0];
		for (int j = 1; j < n; j++) {
			int cur = math_test[i][j];
			if (cur - prev > lar_gap) {
				lar_gap = cur - prev;
			}
			if (cur > max_num) {
				max_num = cur;
			}
			if (cur < min_num) {
				min_num = cur;
			}
			prev = cur;
		}
		cout << "Class " << i << "\n";
		cout << "Max " << max_num << ", Min " << min_num << ", Largest gap " << lar_gap << "\n";
		
	}




	return 0;
}