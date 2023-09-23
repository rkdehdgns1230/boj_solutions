#include <bits/stdc++.h>

using namespace std;

int n;

// true: date2가 더 앞의 시간, false: date1이 더 앞의 시간
bool compare_date(int y1, int m1, int d1, int y2, int m2, int d2) {
	if (y1 > y2) 
		return true;
	if (y1 == y2 && m1 > m2)
		return true;
	if (y1 == y2 && m1 == m2 && d1 > d2)
		return true;
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	string max_name, min_name;
	int max_year = 1990, max_month = 1, max_day = 1;
	int min_year = 2010, min_month = 12, min_day = 30;

	for (int i = 0; i < n; i++) {
		string name;
		int year, month, day;

		cin >> name >> day >> month >> year;

		// 가장 나이가 적은 사람 찾는 로직
		if(compare_date(year, month, day, max_year, max_month, max_day)) {
			max_year = year;
			max_month = month;
			max_day = day;
			max_name = name;
		}
		// 가장 나이가 많은 사람 찾는 로직
		if (compare_date(min_year, min_month, min_day, year, month, day)) {
			min_year = year;
			min_month = month;
			min_day = day;
			min_name = name;
		}
	}

	cout << max_name << "\n" << min_name;


	return 0;
}