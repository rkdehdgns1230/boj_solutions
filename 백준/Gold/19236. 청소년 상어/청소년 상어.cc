#include <bits/stdc++.h>

#define MAX 4

using namespace std;


// 8가지 방향으로 이동할 수 있다. (^ 방향 기준으로 45도 회전하는 방향)
int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

vector<vector<pair<int, int>>> fish_num; // 0: 생선 번호, 1: 이동 방향

vector<pair<int, int>> fish_site;

int answer = 0;
int result = 0;

bool check(int x, int y) {
	return (0 <= x && x < 4 && 0 <= y && y < 4);
}

void print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << fish_num[i][j].first << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << fish_num[i][j].second << " ";
		}
		cout << endl;
	}
}

void move_fish(int x, int y, int shark_x, int shark_y) {
	int num = fish_num[x][y].first;
	int d = fish_num[x][y].second;

	int cnt = 0;
	while (cnt <= 8) {
		int nx = x + dx[d], ny = y + dy[d];

		// 이동할 수 없는 방향(공간 바깥 or 상어)인 경우 45도 회전 (반시계 방향으로)
		if (!check(nx, ny) || (nx == shark_x && ny == shark_y)) {
			d++;
			d %= 8;
			cnt++;
			continue;
		}

		// 이동할 수 있는 경우 해당 위치의 물고기와 정보를 교환한다.
		//cout << num << "번 물고기를 " << x << ", " << y << "에서 " << nx << ", " << ny << "로 이동\n";

		// 비어있는 경우 그냥 움직인다.
		if (fish_num[nx][ny].first == -1) {
			fish_num[nx][ny] = { num, d };
			fish_num[x][y] = { -1, -1 };
			fish_site[num] = { nx, ny };
		}
		// 물고기가 이미 위치한 칸의 경우 위치를 맞바꾼다.
		else {
			fish_site[fish_num[nx][ny].first] = { x, y };
			fish_site[num] = { nx, ny };

			fish_num[x][y] = fish_num[nx][ny];
			fish_num[nx][ny] = { num, d };
		}
		break;
	}
}

void move_fishes(int shark_x, int shark_y) {
	// 물고기를 순서에 맞춰 이동시킨다.
	for (int i = 1; i <= 16; i++) {
		// 상어는 건너띈다. 
		if (fish_site[i].first == shark_x && fish_site[i].second == shark_y) continue;
		// 먹힌 물고기는 건너띈다.
		if (fish_site[i].first == -1 && fish_site[i].second == -1) continue;

		move_fish(fish_site[i].first, fish_site[i].second, shark_x, shark_y);
	}
}

int move_shark(int shark_x, int shark_y, int shark_nx, int shark_ny) {
	// 상어의 현재 이동 방향을 구한다.
	int d = fish_num[shark_x][shark_y].second;

	bool can_move = false;

	//cout << "상어가 " << shark_x << ", " << shark_y << "에서 " << shark_nx << ", " << shark_ny << "로 이동\n";
	
	// 상어가 이동하고 난 자리는 빈 칸 표시로 돌린다.
	int res = fish_num[shark_nx][shark_ny].first;
	//cout << res << "번 물고기 섭취\n";
	fish_site[res] = { -1, -1 };
	// 상어가 이동한 자리와 이동하고 난 자리는 빈 칸으로 표시
	fish_num[shark_x][shark_y] = { -1, -1 };
	fish_num[shark_nx][shark_ny].first = -1; // 방향은 살려야 한다.

	shark_x = shark_nx, shark_y = shark_ny;

	return res; // 상어가 먹은 물고기의 번호를 반환
}

void backtracking(int shark_x, int shark_y) {
	// 1. 물고기를 이동시킨다.
	move_fishes(shark_x, shark_y);

	// 2. 상어 이동
	int d = fish_num[shark_x][shark_y].second;

	int shark_nx = shark_x;
	int shark_ny = shark_y;

	vector<vector<pair<int, int>>> tmp_fish_info = fish_num;
	vector<pair<int, int>> tmp_fish_site = fish_site;

	while (1) {
		shark_nx += dx[d], shark_ny += dy[d];
		// 상어가 더 이상 움직일 수 없는 경우 종료
		if (!check(shark_nx, shark_ny)) {
			break;
		}

		// 물고기가 없는 칸으로는 상어 이동 불가능
		if (fish_num[shark_nx][shark_ny].first == -1) continue;

		int res = move_shark(shark_x, shark_y, shark_nx, shark_ny);
		result += res;
		answer = max(answer, result); 
		//cout << "현재 답은: " << result << ", " << answer << endl; print();
		backtracking(shark_nx, shark_ny);
		fish_num = tmp_fish_info;
		fish_site = tmp_fish_site;
		result -= res;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	fish_num = vector<vector<pair<int, int>>>(4, vector<pair<int, int>>(4, { 0, 0 }));
	fish_site = vector<pair<int, int>>(17, { 0, 0 });

	// 물고기 번호, 방향이 한 번에 입력된다.
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			cin >> fish_num[i][j].first >> fish_num[i][j].second;
			fish_num[i][j].second--; // 1씩 감소
			fish_site[fish_num[i][j].first] = { i, j };
		}

	// 상어의 첫 위치에 해당하는 물고기는 바로 먹힌다.
	int fish = fish_num[0][0].first;
	fish_num[0][0].first = -1;
	fish_site[fish] = { -1, -1 };
	result += fish;

	/*
	move_fishes(0, 0);
	print();
	move_shark(0, 0, 1, 1);
	print();
	move_fishes(0, 0);
	print();
	*/
	backtracking(0, 0);
	
	cout << answer;

	return 0;
}