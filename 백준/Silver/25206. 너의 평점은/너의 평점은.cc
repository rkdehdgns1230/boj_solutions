#include <bits/stdc++.h>

using namespace std;

double getScore(string grade_alphabet) {
	if (grade_alphabet == "A+")
		return 4.5;
	else if (grade_alphabet == "A0")
		return 4.0;
	else if (grade_alphabet == "B+")
		return 3.5;
	else if (grade_alphabet == "B0")
		return 3.0;
	else if (grade_alphabet == "C+")
		return 2.5;
	else if (grade_alphabet == "C0")
		return 2.0;
	else if (grade_alphabet == "D+")
		return 1.5;
	else if (grade_alphabet == "D0")
		return 1.0;
	else
		return 0.0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	double total_score = 0.0;
	double total_grade = 0.0;

	for (int i = 0; i < 20; i++) {
		string subject_name;
		double grade;
		string grade_alphabet;

		cin >> subject_name >> grade >> grade_alphabet;

		if (grade_alphabet == "P")
			continue;
		total_grade += grade;
		total_score += (grade * getScore(grade_alphabet));
	}

	cout << total_score / total_grade;


	return 0;
}