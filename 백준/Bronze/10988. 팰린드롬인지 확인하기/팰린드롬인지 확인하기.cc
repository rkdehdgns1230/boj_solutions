#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string str;
	cin >> str;

	int i = 0, j = str.length() - 1;
	bool isPalindrome = true;

	while (i < j) {
		if (str[i++] == str[j--]);
		else {
			isPalindrome = false;
			break;
		}
	}

	if (isPalindrome)
		cout << "1\n";
	else
		cout << "0\n";

	return 0;
}