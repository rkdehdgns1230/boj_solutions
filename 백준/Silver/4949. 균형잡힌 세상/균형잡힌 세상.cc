/*
	Date: 2022/02/25
	Brief:
	MST (Minimum Spanning Tree) example problem
	Reference:
*/
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
	int i;
	cin.tie(NULL);

	while (1) {
		stack<int> s;
		string str;
		bool passed = true;
		getline(cin, str);

		if (str.size() == 1 && str[0] == '.') {
			break;
		}

		for (i = 0; i < str.size(); i++) {
			if (str[i] == '(') {
				s.push(1);
			}
			else if (str[i] == '[') {
				s.push(2);
			}
			else if (str[i] == ')' && !s.empty()) {
				if (s.top() != 1) {
					passed = false;
					break;
				}
				else {
					s.pop();
				}
			}
			else if (str[i] == ')' && s.empty()) {
				passed = false;
				break;
			}
			else if (str[i] == ']' && !s.empty()) {
				if (s.top() != 2) {
					passed = false;
					break;
				}
				else {
					s.pop();
				}
			}
			else if (str[i] == ']' && s.empty()) {
				passed = false;
				break;
			}
		}
		if (passed && s.empty()) {
			cout << "yes\n";
		}
		else {
			cout << "no\n";
		}

	}

	return 0;
}