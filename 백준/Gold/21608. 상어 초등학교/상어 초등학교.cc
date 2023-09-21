#include <bits/stdc++.h>

#define MAX 21
#define STUDENT_MAX 401

using namespace std;

int n;

int class_room[MAX][MAX];

queue<int> student_q;
int prefer_students[STUDENT_MAX][4];

int dx[] = { -1 ,1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

// num번 학생을 앉힌다. (조건에 따라)
void set_student(int num) {
	// 1번: 인접한 칸의 좋아하는 학생 수 순으로
	// 2번: 인접한 칸 중 비어있는 자리의 수 순으로
	// 3번: 가장 r, c 좌표가 작은 자리 순

	int res_like = -1;
	int res_empty = -1;

	int res_x = 0, res_y = 0; // 앉을 자리

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			// 이미 누가 앉아있는 경우 건너띈다.
			if (class_room[x][y] != 0)
				continue;

			int cur_like = 0, cur_empty = 0;

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!check(nx, ny))
					continue;

				// 좋아하는 학생인지 여부 판단.
				for (int j = 0; j < 4; j++) {
					if (class_room[nx][ny] == prefer_students[num][j]) {
						cur_like++;
						break;
					}
				}

				// 빈 자리인지 확인
				if (class_room[nx][ny] == 0) {
					cur_empty++;
				}
			}

			// 1번 조건 확인
			if (res_like < cur_like) {
				res_like = cur_like;
				res_empty = cur_empty;

				res_x = x, res_y = y;
			}
			// 2번 조건 확인
			else if (res_like == cur_like && res_empty < cur_empty) {
				res_like = cur_like;
				res_empty = cur_empty;

				res_x = x, res_y = y;
			}
			// 3번 조건 확인
			else if (res_like == cur_like && res_empty == cur_empty && res_x > x) {
				res_like = cur_like;
				res_empty = cur_empty;

				res_x = x, res_y = y;
			}
		}
	}
	//cout << res_x << ", " << res_y << " 좌표에 " << num << "번 학생이 앉습니다!\n";
	class_room[res_x][res_y] = num;
}

int calc_satisfaction() {
	int result = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int cur_like = 0;
			int cur_num = class_room[x][y];

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!check(nx, ny))
					continue;

				// 좋아하는 학생인지 여부 판단.
				for (int j = 0; j < 4; j++) {
					if (class_room[nx][ny] == prefer_students[cur_num][j]) {
						cur_like++;
						break;
					}
				}
			}

			switch (cur_like) {
			case 0:
				result += 0;
				break;
			case 1:
				result += 1;
				break;
			case 2:
				result += 10;
				break;
			case 3:
				result += 100;
				break;
			case 4:
				result += 1000;
				break;
			}
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n * n; i++) {
		int student;
		cin >> student;
		student_q.push(student);

		for (int j = 0; j < 4; j++) {
			cin >> prefer_students[student][j];
		}
	}

	while (!student_q.empty()) {
		int student_num = student_q.front();
		student_q.pop();

		set_student(student_num);
	}

	cout << calc_satisfaction() << "\n";

	return 0;
}