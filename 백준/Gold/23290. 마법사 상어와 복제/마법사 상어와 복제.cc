#include <bits/stdc++.h>

#define MAX 5

using namespace std;

int world[MAX][MAX];

int m, s;
int sx, sy; // 상어의 위치 (입력용)

// vector를 활용하되, 물고기 탐색 시간을 줄이는 방식으로 개선해야 한다.
vector<int> fish_info[MAX][MAX];
int fish_smell[MAX][MAX];

queue<vector<int>> fish_q;

// 0 ~ 7: 방향은 문제 참고
int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

bool check(int, int);
void move_fishes();

void pick_shark_move(int);
void move_shark();

void print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << fish_info[i][j].size() << " ";
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			cout << fish_smell[i][j] << " ";
		cout << endl;
	}
}

bool check(int x, int y) {
	return (0 <= x && x < 4 && 0 <= y && y < 4);
}

void copy_map(vector<int> A[][MAX], vector<int> B[][MAX]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			A[i][j] = B[i][j];
		}
	}
}

// (x, y) 위치의 모든 물고기를 한 칸 이동시킨다.
void move_fishes() {
	vector<int> tmp_fish_info[MAX][MAX];

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int i = 0; i < fish_info[x][y].size(); i++) {
				int d = fish_info[x][y][i];
				int cnt = 0;
				int nx = x;
				int ny = y;

				bool is_put = false;

				while (cnt++ < 8) {
					nx = x + dx[d];
					ny = y + dy[d];

					// 방향 전환
					if (!check(nx, ny) || (nx == sx && ny == sy) || fish_smell[nx][ny] > 0) {
						d--;
						if (d < 0) d = 7;

						continue;
					}
					is_put = true;
					tmp_fish_info[nx][ny].push_back(d);
					break;
				}
				if (!is_put)
					tmp_fish_info[x][y].push_back(d);
			}
		}
	}

	copy_map(fish_info, tmp_fish_info);
}

// 상어 이동 구현을 위한 배열
int dir_x[] = { -1, 0, 1, 0 }; // 상, 좌, 하, 우 순으로
int dir_y[] = { 0, -1, 0, 1 };

int res_mv_arr[3];
int tmp_mv_arr[3];
int max_res = -1;

int route_simul() {
	bool visited[MAX][MAX];
	for (int i = 0; i < 4; i++) {
		fill(visited[i], visited[i] + 4, false);
	}
	int eat_cnt = 0;

	int tmp_x = sx;
	int tmp_y = sy;

	for (int i = 0; i < 3; i++) {
		int d = tmp_mv_arr[i];

		tmp_x += dir_x[d];
		tmp_y += dir_y[d];

		if (!check(tmp_x, tmp_y)) return -1;

		if (visited[tmp_x][tmp_y])
			continue;

		visited[tmp_x][tmp_y] = true;
		eat_cnt += fish_info[tmp_x][tmp_y].size();
	}
	return eat_cnt;
}

// 상어 이동 시뮬레이션을 위해 이동 방법 선택
void pick_shark_move(int cnt) {
	if (cnt == 3) {
		int res = route_simul();

		if (max_res < res) {
			max_res = res;
			for (int i = 0; i < 3; i++) {
				res_mv_arr[i] = tmp_mv_arr[i];
				//cout << res_mv_arr[i] << " ";
			}
			//cout << "선택됨 " << res << "\n";
		}

		return;
	}

	for (int i = 0; i < 4; i++) {
		tmp_mv_arr[cnt] = i;
		pick_shark_move(cnt + 1);
	}
}

// move_shark: 상어가 결정된 방법으로 이동
void move_shark() {
	vector<int> tmp_fish_info[MAX][MAX];

	copy_map(tmp_fish_info, fish_info);

	for (int i = 0; i < 3; i++) {
		int d = res_mv_arr[i];

		sx += dir_x[d];
		sy += dir_y[d];

		//cout << "상어가 " << sx << ", " << sy << "로 이동\n";
		if (tmp_fish_info[sx][sy].size() != 0) {
			fish_smell[sx][sy] = 3;
			tmp_fish_info[sx][sy].clear();
		}
	}
	copy_map(fish_info, tmp_fish_info);
	return;
}

// 1회 시뮬 수행
void simulation() {
	// 1. 복제 마법 시전
	vector<int> copy[MAX][MAX];
	copy_map(copy, fish_info);

	// 2. 모든 물고기가 한 칸 이동
	move_fishes();
	//print();

	// 3. 상어 3칸 이동 (가장 효율적인 방법 찾는다.)
	max_res = -1;
	pick_shark_move(0);
	move_shark();

	// 4. 물고기 냄새 1씩 감소시킨다.
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (fish_smell[i][j] > 0) fish_smell[i][j]--;

	// 5. 복제 마법 시전 완료
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < copy[i][j].size(); k++) {
				fish_info[i][j].push_back(copy[i][j][k]);
			}
		}
	}
	//cout << "한 턴 완료\n";
	//print();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> m >> s;
	
	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		fish_info[x - 1][y - 1].push_back(d - 1);
	}

	cin >> sx >> sy;
	sx--; sy--;

	for(int i = 0; i < s; i++)
		simulation();

	int answer = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer += fish_info[i][j].size();
		}
	}

	cout << answer; 
	return 0;
}