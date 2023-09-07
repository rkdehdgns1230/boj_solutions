#include <bits/stdc++.h>

#define GRADE 7

using namespace std;

int student[GRADE][2]; // 0: 여자, 1: 남자
int n, k;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int sex, grade;
		cin >> sex >> grade;

		student[grade][sex]++;
	}
	int ans = 0;
	for (int i = 1; i < GRADE; i++) {
		ans += student[i][0] / k;
		ans += student[i][0] % k == 0 ? 0 : 1;
		ans += (student[i][1] / k);
		ans += student[i][1] % k == 0 ? 0 : 1;
	}

	cout << ans << "\n";

	return 0;
}