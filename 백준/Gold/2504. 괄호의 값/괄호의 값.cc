#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	stack<char> S;
	string str;

	cin >> str;

	bool isValid = true;

	int num = 1; // 곱을 위한 수
	int sum = 0; // 합을 위한 수

	for(int i = 0; i < str.length(); i++){
		if (str[i] == '('){
			num *= 2; // 소괄호가 나오면 곱해질 값 2배 증가
			S.push(str[i]);
		}
		else if (str[i] == '[') {
			num *= 3; // 대괄호가 나오면 곱해질 값 3배 증가
			S.push(str[i]);
		}
		else if (str[i] == ')') {
			if (S.empty() || S.top() != '(') {
				isValid = false;
				break;
			}
			// 더하기 연산을 해야 하는 경우 -> ()
			if (str[i - 1] == '(') {
				sum += num;
			}
			num /= 2;
			S.pop();
		}
		else if (str[i] == ']') {
			if (S.empty() || S.top() != '[') {
				isValid = false;
				break;
			}

			// 더하기 연산을 해야 하는 경우 -> []
			if (str[i - 1] == '[') {
				sum += num;
			}
			num /= 3;
			S.pop();
		}
	}

	if (isValid && S.empty())
		cout << sum;
	else
		cout << 0;
	return 0;
}