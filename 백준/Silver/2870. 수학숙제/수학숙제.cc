#include <bits/stdc++.h>

using namespace std;

bool str_compare(string& a, string& b) {
	if (a.length() > b.length()) {
		return false;
	}
	else if (a.length() < b.length())
		return true;
	else
	{
		for (int i = 0; i < a.length(); i++) {
			if (a[i] > b[i]) return false;
			else if (a[i] < b[i]) return true;
			else continue;
		}
		return false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	vector<string> arr;

	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;

		string tmp = "";
		bool is_number = false;
		for (int j = 0; j < str.length(); j++) {
			if (str[j] >= '0' && str[j] <= '9') {
				if (tmp == "0") {
					tmp = str[j];
				}
				else
					tmp += str[j];
			}
			else {
				if (tmp != "") {
					arr.push_back(tmp);
					tmp = "";
				}
			}
		}

		if(tmp != "")
			arr.push_back(tmp);
	}
	
	sort(arr.begin(), arr.end(), str_compare);
	for (string a : arr) {
		cout << a << "\n";
	}

	return 0;
}