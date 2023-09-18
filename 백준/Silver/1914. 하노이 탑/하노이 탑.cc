#include <bits/stdc++.h>

using namespace std;

int n;

// 높이 k의 하노이 타워를 a에서 b로 옮긴다.
void moveTower(int k, int a, int b) {
	if (k == 1) {
		cout << a << " " << b << "\n";
		return;
	}

	// k-1 높이의 타워를 6-a-b로 옮기고 k번째 원판을 b로 먼저 옮긴 뒤
	// 다시 k-1 높이의 타워를 b로 옮긴다.
	moveTower(k - 1, a, 6 - a - b);
	cout << a << " " << b << "\n";
	moveTower(k - 1, 6 - a - b, b);
}

string calcMul(string num) {
	string res = "";
	deque<int> dq;

	int upper = 0;

	for (int i = num.length() - 1; i >= 0; i--) {
		dq.push_front(upper);
		upper = 0;
		int tmp = num[i] - '0';
		tmp *= 2;
		
		if (tmp >= 10) {
			upper = 1;
			tmp -= 10;
		}
		int fr = dq.front() + tmp;
		dq.pop_front();
		dq.push_front(fr);
	}

	if (upper == 1) {
		dq.push_front(1);
	}

	for (int num : dq) {
		res += (num + '0');
	}

	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;

	string res = "1";
	for (int i = 0; i < n; i++) {
		res = calcMul(res);
	}

	for (int i = 0; i < res.length(); i++) {
		if (i == res.length() - 1) {
			cout << (char)(res[i] - 1);
			continue;
		}
		cout << res[i];
	}cout << "\n";

	if (n <= 20) {
		moveTower(n, 1, 3);
	}
	return 0;
}