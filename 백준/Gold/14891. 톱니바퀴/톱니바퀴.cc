#include <bits/stdc++.h>

#define RIGHT_IDX 2
#define LEFT_IDX 6

using namespace std;

// index 2: right, 6: left
string gear[4]; // '0': N, '1': S 의미
int K;

void rotate(int gear_num, int direction) {
	// 시계 방향으로 회전
	if (direction == 1) {
		char last = gear[gear_num][7];

		for (int i = 7; i > 0; i--) {
			gear[gear_num][i] = gear[gear_num][i - 1];
		}
		gear[gear_num][0] = last;
	}
	// 반시계 방향으로 회전
	else {
		char first = gear[gear_num][0];
		for (int i = 0; i < 7; i++) {
			gear[gear_num][i] = gear[gear_num][i + 1];
		}
		gear[gear_num][7] = first;
	}
}

// 현재 톱니바퀴 상태에 따라 점수 계산
int calculate_score() {
	int answer = 0;
	if (gear[0][0] == '1') answer += 1;
	if (gear[1][0] == '1') answer += 2;
	if (gear[2][0] == '1') answer += 4;
	if (gear[3][0] == '1') answer += 8;
	return answer;
}

void simulation(const int gear_num, const int direction) {
	int cur_gear_num = gear_num;
	int left_gear_num = gear_num - 1;
	int current_direction = direction * -1;

	char cur_left_teeth = gear[gear_num][LEFT_IDX];
	char cur_right_teeth = gear[gear_num][RIGHT_IDX];

	bool isRotating = true;
	
	// 해당 톱니바퀴 회전부터 시작
	rotate(gear_num, direction);

	// 왼편의 톱니바퀴와 연동 (방향 전환되어야)
	while (1) {
		if (left_gear_num == -1) break;
		// 이전에 회전하지 않은 경우 중단
		if (!isRotating) break;
		isRotating = false;

		// 돌리기 전에 서로 다른 극인 경우 반대 방향으로 1번 회전
		if (cur_left_teeth != gear[left_gear_num][RIGHT_IDX]) {
			//cout << left_gear_num << "번 톱니 바퀴를 " << current_direction << " 방향으로 회전\n";

			// 왼쪽 톱니바퀴의 왼 톱니로 이동
			cur_left_teeth = gear[left_gear_num][LEFT_IDX];
			// 왼편의 톱니 바퀴를 반대 방향으로 한 바퀴 돌림
			rotate(left_gear_num, current_direction);

			isRotating = true;
		}

		// 한 칸 왼편으로 이동한다.
		cur_gear_num = left_gear_num;
		left_gear_num--;
		current_direction *= -1;
	}

	cur_gear_num = gear_num;
	int right_gear_num = gear_num + 1;
	current_direction = direction * -1;

	isRotating = true;

	while (1) {
		if (right_gear_num == 4) break;
		// 이전에 회전하지 않은 경우 중단
		if (!isRotating) break;
		isRotating = false;
		
		// 돌리기 전에 서로 다른 극인 경우 반대 방향으로 1번 회전
		if (cur_right_teeth != gear[right_gear_num][LEFT_IDX]) {
			//cout << right_gear_num << "번 톱니 바퀴를 " << current_direction << " 방향으로 회전\n";

			// 오른쪽 톱니바퀴의 오른 톱니로 이동
			cur_right_teeth = gear[right_gear_num][RIGHT_IDX];
			// 왼편의 톱니 바퀴를 반대 방향으로 한 바퀴 돌림
			rotate(right_gear_num, current_direction);

			isRotating = true;
		}

		// 한 칸 왼편으로 이동한다.
		cur_gear_num = right_gear_num;
		right_gear_num++;
		current_direction *= -1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 4; i++)
		cin >> gear[i];

	cin >> K;

	for (int i = 0; i < K; i++) {
		int gear_num, dir;
		cin >> gear_num >> dir;

		simulation(gear_num - 1, dir);
	}

	cout << calculate_score() << "\n";
	return 0;
}