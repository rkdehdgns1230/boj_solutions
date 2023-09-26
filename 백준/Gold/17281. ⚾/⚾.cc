#include <bits/stdc++.h>

#define MAX 51

using namespace std;

int n;
int inning_info[MAX][9];
bool is_picked[9];
int play_order[9];

int answer;

void play_game() {
	int score = 0;
	
	int idx = 0;

	for (int inning = 0; inning < n; inning++) {
		int cur_out_count = 0;
		bool base[4] = { false, false, false, false };
		while (cur_out_count < 3) {
			base[0] = true;

			int move = inning_info[inning][play_order[idx++]];
			idx %= 9;
			
			// 아웃된 경우
			if (move == 0) {
				cur_out_count++;
				continue;
			}
			// 베이스를 돌며, 안타 루타만큼 주자를 이동 (홈런 포함)
			for (int i = 3; i >= 0; i--) {
				// 해당 베이스에 주자가 없으면, 건너띈다.
				if (!base[i]) continue;
				if (i + move >= 4) 
					score++;
				else 
					base[i + move] = true;
				base[i] = false;
			}
		}
	}

	answer = (answer < score) ? score : answer;
}

void pick_player(int num) {
	if (num == 9) {
		/*for (int i = 0; i < 9; i++) {
			cout << play_order[i] << " ";
		}cout << endl;*/

		play_game();
		return;
	}
	// 가장 좋아하는 선수인 1번 선수는 4번 타자로 고정했으니 건너띈다.
	if (num == 3) {
		pick_player(num + 1);
		return;
	}

	for (int i = 1; i < 9; i++) {
		if (is_picked[i])
			continue;
		play_order[num] = i; // 다음 타순으로 선수 선택
		is_picked[i] = true;
		pick_player(num + 1);
		is_picked[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	// 9명의 선수를 9가지 자리에 배치하는 모든 경우의 수를 시뮬레이션 돌린다면??
	// 8! * 50(N_MAX)
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < 9; j++) 
			cin >> inning_info[i][j];
	
	pick_player(0);
	cout << answer << "\n";

	return 0;
}