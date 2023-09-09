#include <bits/stdc++.h>

using namespace std;

int n, k;
int L;
int board[101][101];

int answer = 0;

vector<pair<int, char>> dir_v;

bool check(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

void simulation() {
	// main 함수에서 입력받은 정보를 이용해 시간의 흐름에 따라 뱀의 움직임을 시뮬레이션

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	int x = 1, y = 1;
	int cur_time = 0; // 시뮬레이션 상황에서 현재 시간을 저장

	// 방향 정보 인덱스
	int idx = 0;
	
	// 덱을 이용해 뱀의 좌표를 저장
	deque<pair<int, int>> d;
	d.push_back({ 1, 1 });
	board[1][1] = 1; // 현재 뱀이 점유하고 있는 좌표는 1로 표시

	int change_idx = 0;

	// 방향 정보와 제한 시간
	char change_dir_info = dir_v[change_idx].second;
	int change_dir_time = dir_v[change_idx].first;

	// 방향 변경되는 시간까지 현재 방향으로 직진한다.
	while(1) {
		// 방향 변경 정보 갱신
		if (cur_time == change_dir_time) {
			// 방향 설정
			if (change_dir_info == 'L') {
				// 왼쪽으로 머리를 튼다.
				idx--;
				if (idx == -1) idx = 3;
			}
			else if (change_dir_info == 'D') {
				idx++;
				idx %= 4;
			}

			//cout << "현재 시간: " << cur_time << ", " <<  change_dir_info << " 방향으로 방향 변경합니다.\n";

			// 이동 방향 변경 정보 불러오기
			if (change_idx < dir_v.size() - 1) {
				change_dir_info = dir_v[++change_idx].second;
				change_dir_time = dir_v[change_idx].first;
			}
		}

		x += dx[idx];
		y += dy[idx];
		cur_time++;

		//cout << "현재위치 x: " << x << ", y: " << y << "입니다.\n";
		//cout << "이동 방향: " << idx << "\n";

		// 벽에 부딪히면 게임 끝
		if (!check(x, y) || board[x][y] == 1) {
			//cout << "벽에 박아서 게임 끝납니다.\n";
			answer = cur_time;
			return;
		}

		// 새로운 칸으로 뱀의 몸통이 이동
		d.push_back({ x, y });

		// 사과를 먹은 경우 꼬리는 줄어들지 않는다.
		if (board[x][y] == -1) {
			//cout << "사과를 먹었습니다.\n";
			board[x][y] = 1; // 뱀의 몸통으로 추가
			continue;
		}

		// 빼주고 체크해야 한다.
		int tail_x = d.front().first;
		int tail_y = d.front().second;
		board[tail_x][tail_y] = 0;
		//cout << "꼬리 정보: " << tail_x << ", " << tail_y << "\n";
		board[x][y] = 1;

		d.pop_front();

		// 자기 몸통에 닿는 경우
		/*if (board[x][y] == 1) {
			cout << "몸통에 도달해서 게임 끝납니다.\n";
			answer = cur_time;
			return;
		}*/
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	cin >> k;

	for (int i = 0; i < k; i++) {
		int r, c;
		cin >> r >> c;

		// (r, c) 위치에 사과를 배치 => -1 값 부여
		board[r][c] = -1;
	}

	cin >> L;

	// 방향 전환 정보를 입력 받는다.
	for (int i = 0; i < L; i++) {
		int x;
		char c;
		cin >> x >> c;
		dir_v.push_back({ x, c });
	}

	simulation();

	cout << answer;

	return 0;
}