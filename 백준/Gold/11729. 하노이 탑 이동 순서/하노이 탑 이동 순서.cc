#include <bits/stdc++.h>

using namespace std;

int n;

// a번 기둥에서 b번 기둥으로, n개의 원판을 옮기는 방법을 출력하는 함수
void func(int a, int b, int n) {
	if (n == 1) {
		// 1개는 그냥 a번 기둥에서 b번 기둥으로 옮긴다.
		cout << a << " " << b << "\n";
		return;
	}

	// n-1개의 원판을 기둥 a -> 6-a-b(a, b를 제외한 나머지 번호)로 옮긴다.
	func(a, 6 - a - b, n - 1);
	// n번 원판을 a -> b로 옮긴다.
	cout << a << " " << b << "\n";
	// n-1개의 원판을 6-a-b -> b로 옮긴다.
	func(6 - a - b, b, n - 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	cout << (1 << n) - 1 << "\n";
	func(1, 3, n);

	return 0;
}