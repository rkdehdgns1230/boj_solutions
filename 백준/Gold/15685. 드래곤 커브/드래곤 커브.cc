#include <bits/stdc++.h>

#define MAX 101

using namespace std;

int board[MAX][MAX]; // 배열의 한 칸 한 칸을 좌표로 생각

// 그리려는 dragon curve의 시작 좌표, 시작 방향, 세대를 의미
void draw_dragon_curve(int x, int y, int dir, int gen) {
	vector<int> dir_list;

	//cout << "0세대에 대해서\n";
	dir_list.push_back(dir);
	board[x][y] = 1;

	while (gen--) {
		int cur_size = dir_list.size();

		// 90도 틀어서 vector에 다시 넣는 작업 수행
		for (int i = cur_size - 1; i >= 0; i--) {
			int tmp_dir = dir_list[i];
			dir_list.push_back((tmp_dir + 1) % 4);
		}
	}
	
	for (int i = 0; i < dir_list.size(); i++) {
		int dir = dir_list[i];

		if (dir == 0) 
			x++;
		else if (dir == 1) 
			y--;
		else if (dir == 2)
			x--;
		else
			y++;
		// 이동한 점의 좌표를 표기한다.
		board[x][y] = 1;
	}

	// 세대를 누적시키는 방법 
	// -> 그린 순서대로 queue에 담음 (이때, 90도 회전시켜서 담아도 됨)
	// -> 똑같은 순서대로 90도씩 회전한 뒤 그린다.
	// 진행 좌표에 대한 정보는 누적해서 사용해야 한다.
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int answer = 0;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int x, y, dir, gen;
		cin >> x >> y >> dir >> gen;

		draw_dragon_curve(x, y, dir, gen);
	}

	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i][j + 1] == 1 && board[i + 1][j + 1] == 1)
				answer++;
		}
	}

	cout << answer;
	return 0;
}