#include <bits/stdc++.h>

#define MAX 201

using namespace std;

// 컨베이어 벨트 한 줄의 칸 (n)
// 내구도 0인 칸 중단 기준 (k)
int n, k;

// 로봇이 있는 칸: 1, 없는 칸: 0
int belt[MAX];
// 각 칸의 내구도 정보 저장
int durability[MAX];

// 단계 진행에 따라 컨베이어 벨트 돌아가게 만듦
void conveyor_belt_move() {
	int last_site = belt[2 * n - 1];
	int last_site_durability = durability[2 * n - 1];

	for (int i = 2 * n - 1; i > 0; i--) {
		belt[i] = belt[i - 1];
		durability[i] = durability[i - 1];
	}
	belt[0] = last_site;
	durability[0] = last_site_durability;

	/*cout << "컨베이어 벨트 이동이옫!!\n";
	for (int i = 0; i < 2 * n; i++) {
		cout << belt[i] << " ";
	}cout << endl;
	for (int i = 0; i < 2 * n; i++) {
		cout << durability[i] << " ";
	}cout << endl;*/
}

void robot_move() {
	for (int i = 2 * n - 1; i > 0; i--) {
		if (belt[i] == 0)
			continue;

		int cur_site = i;
		int next_site = (i + 1) % (2 * n);
		// 로봇이 있는 칸이고, "내리는 위치"에 도달한 경우
		if (belt[cur_site] == 1 && cur_site == n - 1) {
			belt[cur_site] = 0; // 내릴 때는 내구도 감소 없음
			continue;
		}
		// 로봇이 있는 칸이고, 다음 칸이 비어있는 경우
		else if (belt[cur_site] == 1 && belt[next_site] == 0 && durability[next_site] > 0) {
			// 로봇을 옮김
			belt[cur_site] = 0;
			belt[next_site] = 1;
			// 다음 칸의 내구도 감소
			durability[next_site]--;

			// 이동한 칸이 내리는 위치면, 내린다.
			if (next_site == n - 1) {
				belt[next_site] = 0;
			}
		}
	}
	/*cout << "로봇 이동이옫!!\n";
	for (int i = 0; i < 2 * n; i++) {
		cout << belt[i] << " ";
	}cout << endl;
	for (int i = 0; i < 2 * n; i++) {
		cout << durability[i] << " ";
	}cout << endl;*/
}

bool isEnd() {
	int result = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (durability[i] == 0)
			result++;
	}
	return result >= k;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int answer = 0;

	cin >> n >> k;

	for (int i = 0; i < 2 * n; i++) {
		cin >> durability[i];
	}

	while (!isEnd()) {
		// 1번 과정
		conveyor_belt_move();
		// 2번 과정
		robot_move();

		// 4번 과정
		if (durability[0] >= 1 && belt[0] == 0) {
			belt[0] = 1;
			durability[0]--;
		}

		answer++;
	}

	cout << answer;

	return 0;
}