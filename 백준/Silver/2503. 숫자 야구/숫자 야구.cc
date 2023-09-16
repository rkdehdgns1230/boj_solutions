#include <bits/stdc++.h>

using namespace std;

int n;

// false: 판단 해야 함, true: 이미 아님
bool possible_answer[1000]; // 111 ~ 999 범위의 수에서 해당하는 수를 남기기 위한 배열

void init() {
	//// 000 ~ 099 는 어차피 범위 밖
	//fill(not_answer, not_answer + 100, true);

	//// n0x -> 해당 사항 없음
	//for (int i = 100; i <= 900; i += 100) {
	//	fill(not_answer + i, not_answer + i + 10, true);
	//}

	//// nx0 -> 해당 사항 없음
	//for (int i = 0; i < 1000; i++) {
	//	if (i % 10 == 0)
	//		not_answer[i] = true;
	//}

	// 서로 다른 세 자리 수를 선택한 경우를 제외하고 모두 버린다.
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (i == j) continue;
			for (int k = 1; k <= 9; k++) {
				if (k == i || k == j) continue;
				possible_answer[i * 100 + j * 10 + k] = true;
			}
		}
	}
}

void playNumberBaseball(string str, int strike, int ball) {
	for (int i = 0; i < 1000; i++) {
		// 이미 정답 아닌 케이스 건너띈다.
		if (!possible_answer[i]) continue;

		int strike_num = 0;
		vector<int> original_v(10, 0);
		vector<int> ball_v(10, 0);
		int ball_num = 0;
		int tmp = i;

		for (int j = 2; j >= 0; j--) {
			if ((str[j] - '0') == (tmp % 10)) {
				strike_num++;
			}
			else {
				original_v[str[j] - '0']++;
				ball_v[tmp % 10]++;
			}
			tmp /= 10;
		}

		for (int j = 1; j <= 9; j++) {
			if (ball_v[j] <= original_v[j])
				ball_num += ball_v[j];
			else
				ball_num += original_v[j];
		}

		//cout << str << ":" << i << "는 " << strike_num << " 스트라이크 " << ball_num << " 볼 입니다.\n";

		// strike, ball 판정 한 뒤 틀린 경우 제외한다.
		if (strike_num != strike || ball_num != ball)
			possible_answer[i] = false;
	}
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int answer = 0;

	// not_answer = false인 케이스를 111 ~ 999만 남긴다.
	init();

	bool three_strike = false;

	for (int i = 0; i < n; i++) {
		string question;
		int strike, ball;
		cin >> question >> strike >> ball;

		// 3 strike 등장하면 answer = 1
		if (strike == 3) {
			three_strike = true;
		}

		playNumberBaseball(question, strike, ball);
	}

	if (three_strike) {
		cout << "1\n";
		return 0;
	}

	for (int i = 0; i < 1000; i++) {
		if (possible_answer[i]) {
			//cout << i << endl;
			answer++;
		}
	}

	cout << answer;

	return 0;
}