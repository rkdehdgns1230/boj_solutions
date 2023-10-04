#include <bits/stdc++.h>

#define MAX 500

using namespace std;

int n;
int outer_send;
int send_info[MAX][MAX];

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

bool check(int x, int y) {
	return (0 <= x && x < n && 0 <= y && y < n);
}

void spread_send(int x, int y, int nx, int ny, int send, double ratio) {
	int calc_send = send * ratio;
	if (check(nx, ny)) {
		send_info[nx][ny] += calc_send;
		//cout << "{" << nx << ", " << ny << "}: " << calc_send << "만큼 모레가 증가\n";
	}
	else {
		outer_send += calc_send;
		//cout << "{" << nx << ", " << ny << "}: " << calc_send << "로 모레가 바깥으로 이동\n";
	}
	//cout << "{" << x << ", " << y << "}: " << calc_send << "만큼 모레가 감소\n";

	send_info[x][y] -= calc_send;
}

// 토네이도의 중심이 (x, y) -> (nx, ny) 이동
void spread_send_simul(int x, int y, int nx, int ny, int dir) {
	int cur_send = send_info[nx][ny];

	// 4가지 방향에 따라서 모레가 흩뿌려지는 방향이 다름을 고려해야 한다.
	// 현재 모레의 45%를 바깥으로 흩뿌린다.
	if (dir == 0) {
		// 7%
		spread_send(nx, ny, nx + 1, ny, cur_send, 0.07);
		spread_send(nx, ny, nx - 1, ny, cur_send, 0.07);

		// 1%
		spread_send(nx, ny, nx + 1, ny + 1, cur_send, 0.01);
		spread_send(nx, ny, nx - 1, ny + 1, cur_send, 0.01);

		// 2%
		spread_send(nx, ny, nx + 2, ny, cur_send, 0.02);
		spread_send(nx, ny, nx - 2, ny, cur_send, 0.02);

		// 10%
		spread_send(nx, ny, nx - 1, ny - 1, cur_send, 0.1);
		spread_send(nx, ny, nx + 1, ny - 1, cur_send, 0.1);

		// 5%
		spread_send(nx, ny, nx, ny - 2, cur_send, 0.05);

		// 남은 모레 전부 이동
		spread_send(nx, ny, nx, ny - 1, send_info[nx][ny], 1);
	}
	else if (dir == 1) {
		// 7%
		spread_send(nx, ny, nx, ny + 1, cur_send, 0.07);
		spread_send(nx, ny, nx, ny - 1, cur_send, 0.07);

		// 1%
		spread_send(nx, ny, nx - 1, ny + 1, cur_send, 0.01);
		spread_send(nx, ny, nx - 1, ny - 1, cur_send, 0.01);

		// 2%
		spread_send(nx, ny, nx, ny + 2, cur_send, 0.02);
		spread_send(nx, ny, nx, ny - 2, cur_send, 0.02);

		// 10%
		spread_send(nx, ny, nx + 1, ny - 1, cur_send, 0.1);
		spread_send(nx, ny, nx + 1, ny + 1, cur_send, 0.1);

		// 5%
		spread_send(nx, ny, nx + 2, ny, cur_send, 0.05);

		// 남은 모레 전부 이동
		spread_send(nx, ny, nx + 1, ny, send_info[nx][ny], 1);
	}
	else if (dir == 2) {
		// 7%
		spread_send(nx, ny, nx + 1, ny, cur_send, 0.07);
		spread_send(nx, ny, nx - 1, ny, cur_send, 0.07);

		// 1%
		spread_send(nx, ny, nx + 1, ny - 1, cur_send, 0.01);
		spread_send(nx, ny, nx - 1, ny - 1, cur_send, 0.01);

		// 2%
		spread_send(nx, ny, nx + 2, ny, cur_send, 0.02);
		spread_send(nx, ny, nx - 2, ny, cur_send, 0.02);

		// 10%
		spread_send(nx, ny, nx - 1, ny + 1, cur_send, 0.1);
		spread_send(nx, ny, nx + 1, ny + 1, cur_send, 0.1);

		// 5%
		spread_send(nx, ny, nx, ny + 2, cur_send, 0.05);

		// 남은 모레 전부 이동
		spread_send(nx, ny, nx, ny + 1, send_info[nx][ny], 1);
	}
	else {
		// 7%
		spread_send(nx, ny, nx, ny + 1, cur_send, 0.07);
		spread_send(nx, ny, nx, ny - 1, cur_send, 0.07);

		// 1%
		spread_send(nx, ny, nx + 1, ny + 1, cur_send, 0.01);
		spread_send(nx, ny, nx + 1, ny - 1, cur_send, 0.01);

		// 2%
		spread_send(nx, ny, nx, ny + 2, cur_send, 0.02);
		spread_send(nx, ny, nx, ny - 2, cur_send, 0.02);

		// 10%
		spread_send(nx, ny, nx - 1, ny - 1, cur_send, 0.1);
		spread_send(nx, ny, nx - 1, ny + 1, cur_send, 0.1);

		// 5%
		spread_send(nx, ny, nx - 2, ny, cur_send, 0.05);

		// 남은 모레 전부 이동
		spread_send(nx, ny, nx - 1, ny, send_info[nx][ny], 1);
	}
}

void tornado_simul() {
	// n은 홀수인 경우만 존재한다.
	int x = n / 2;
	int y = n / 2;

	// 2번 이동 -> 이동 거리 + 1
	// 이동 거리 n에 도달하면 종료
	int cnt = 0;
	int dis = 0;
	int dir = 0;

	//cout << "{" << x << ", " << y << "} 좌표에서 시작!\n";

	while (1) {
		// 짝수 번째일 시 이동 거리 증가
		if (cnt % 2 == 0)
			dis++;

		// 이동 거리 n에 도달하기 전까지 반복
		if (dis == n)
			break;

		//cout << "distance: " << dis << endl;
		for (int i = 0; i < dis; i++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			//cout << "{" << nx << ", " << ny << "} 좌표로 이동합니다.\n";
			spread_send_simul(x, y, nx, ny, dir);
			x = nx; y = ny;
		}

		// 다음 방향으로 이동
		dir++;
		dir %= 4;
		// 이동 횟수 증가
		cnt++;
	}

	for (int i = 0; i < n - 1; i++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		//cout << "{" << nx << ", " << ny << "} 좌표로 이동합니다.\n";
		spread_send_simul(x, y, nx, ny, dir);
		x = nx; y = ny;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> send_info[i][j];

	/*spread_send_simul(2, 0, 2, 1, 2);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << send_info[i][j] << " ";
		cout << endl;
	}*/

	tornado_simul();

	cout << outer_send;
	return 0;
}

// 겪자 밖으로 나간 모래의 총량을 구해야 한다. -> 범위 밖으로 나가는 모래를 따로 계산해야 한다.