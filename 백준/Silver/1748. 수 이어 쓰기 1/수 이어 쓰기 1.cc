#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	// 1억회 반복 -> 선형으로 반복해도 시간 초과
	// 입력된 수에 따라 계산을 거쳐 자리수를 계산해야 한다.
	// 1 ~ 9: 길이 1 (9개)
	// 10 ~ 99: 길이 2 (90개)
	// 100 ~ 999: 길이 3 (900개)
	// 1000 ~ 9999: 길이 4 (9000개)
	// 이런 식으로 범위에 따라 더해가야 한다고 생각함

	int length = 0;
	int tmp = n;

	while (tmp != 0) {
		tmp /= 10;
		length++;
	}
	int minus_leading_one = pow(10, length - 1);

	long long answer = (n - minus_leading_one + 1) * length;

	for (int i = 0; i < length - 1; i++) {
		answer += (pow(10, i) * 9) * (i + 1);
	}
	cout << answer;
	
	return 0;
}