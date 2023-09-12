#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string str;
	cin >> str;

	stack<char> S;
	int answer = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(')
			S.push(str[i]);
		// 레이저인 경우 (옳지 않은 입력은 없는 상황을 가정)
		else if (str[i] == ')' && str[i - 1] == '(') {
			S.pop();
			answer += S.size(); // 레이저에 의해 잘려 추가로 생성되는 파이프 개수 count
		}
		// 파이프의 끝을 의미하는 닫는 괄호의 경우
		else {
			S.pop();
			answer++; // 파이프 꼬다리 개수 count
		}
	}

	cout << answer;

	return 0;
}