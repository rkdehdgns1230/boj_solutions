#include <bits/stdc++.h>

#define MAX 21

using namespace std;

int n, m;

// 주사위의 좌표
int x, y;
// 명령의 개수
int k;

int board[MAX][MAX];
int dir[1001]; // 명령이 가리키는 방향을 저장하는 배열

// 주사위가 현재 담고 있는 수를 저장하는 배열
vector<int> dice(7);

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < m);
}

// 초기 상태 {0, 1, 2, 3, 4, 5, 6} 기준
// 현재 상태를 기준으로 상대적인 위치 이동에 대해 값을 변경하도록 하면, 각 상태에 따른 주사위 상태 구현 가능
void rollEast() {
	dice = { 0, dice[4], dice[2], dice[1], dice[6], dice[5], dice[3] };
}

void rollWest() {
	dice = { 0 , dice[3], dice[2], dice[6], dice[1], dice[5], dice[4] };
}

void rollNorth() {
	dice = { 0, dice[5], dice[1], dice[3], dice[4], dice[6], dice[2] };
}

void rollSouth() {
	dice = { 0, dice[2], dice[6], dice[3], dice[4], dice[1], dice[5] };
}


void simulation() {
	// 1: 동, 2: 서, 3: 북, 4: 남
	int dx[] = { 0, 0, 0, -1, 1 };
	int dy[] = { 0, 1, -1, 0, 0 };

	// 지도의 0 -> 주사위 값으로 대체, 지도의 N -> 주사위 수로 대체 (지도에는 0)
	// 각 이동칸에서 맨 위의 숫자를 구한다. (출력)
	// 주사위를 기준으로 이동 방향에 따른 면의 정보를 기록하도록 변경


	// index가 가리키는 수가 밑바닥에 있을 때, 반대편이 담고 있는 주사위 index
	int top[] = { 0, 6, 5, 4, 3, 2, 1 };

	for (int i = 0; i < k; i++) {
		int direction = dir[i];

		int nx = x + dx[direction];
		int ny = y + dy[direction];
		
		// 맵을 넘어가는 경우는 생략
		if (!check(nx, ny))
			continue;

		// 현재 이동하는 방향으로 바닥 이동
		if (direction == 1)
			rollEast();
		else if (direction == 2)
			rollWest();
		else if (direction == 3)
			rollNorth();
		else
			rollSouth();

		

		// 0인 경우 현재 주사위의 밑바닥 수 복사
		if(board[nx][ny] == 0){
			board[nx][ny] = dice[6];
		}
		// 0이 아닌 경우 주사위 밑면으로 수 복사
		else {
			dice[6] = board[nx][ny];
			board[nx][ny] = 0;
		}
		cout << dice[1] << "\n";

		x = nx, y = ny;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	cin >> x >> y;

	cin >> k;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			cin >> board[i][j];

	for (int i = 0; i < k; i++)
		cin >> dir[i];

	simulation();

	return 0;
}