#include <bits/stdc++.h>

#define MAX 300001

using namespace std;

int n, p;

int num_arr[MAX];

int calc_pow(int num, int pow) {
	int res = 1;
	for (int i = 0; i < pow; i++) {
		res *= num;
	}
	return res;
}

int calc(int num) {
	int res = 0;

	while (num > 0) {
		res += calc_pow(num % 10, p);
		num /= 10;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int answer = 1;
	int repeat_array = 0;

	cin >> n >> p;

	num_arr[n] = true;


	while (1) {
		int tmp = calc(n);
		//cout << tmp << " ";
		if (++num_arr[tmp] > 2)
			break;
		if (num_arr[tmp] == 2) {
			repeat_array++;
		}
		else {
			answer++;
		}
		n = tmp;
	}
	//cout << endl;

	cout << answer - repeat_array;

	return 0;
}