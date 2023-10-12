#include <bits/stdc++.h>

#define MAX 51

using namespace std;

typedef struct {
	int count, weight, speed, dir;
	int odd, even; // 짝수 방향과 홀수 방향 count
} MAP;

MAP world[MAX][MAX];

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int n, m, k;

vector<vector<int>> fireball_info;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;

		// 파이어볼의 좌표 저장
		fireball_info.push_back({ r - 1, c - 1, m, s, d });
	}

	while (k--) {
		// 초기화 후 시작
		memset(world, 0, sizeof(world));

		//cout << "파이어볼 정보\n";
		// 1. 모든 파이어볼 이동
		while (!fireball_info.empty()) {
			int r = fireball_info.back()[0];
			int c = fireball_info.back()[1];
			int w = fireball_info.back()[2];
			int s = fireball_info.back()[3];
			int d = fireball_info.back()[4];
			fireball_info.pop_back();
			//cout << r << ", " << c << ", " << w << ", " << s << ", " << d << endl;

			// 파이어볼 다음 이동 좌표 계산
			int nr = (r + dx[d] * s) % n;
			int nc = (c + dy[d] * s) % n;

			while (nr < 0) nr += n;
			while (nc < 0) nc += n;

			//cout << "이동: " << nr << ", " << nc << endl;

			// 해당 칸에 위치한 파이어볼의 정보 갱신
			world[nr][nc].count++;
			world[nr][nc].dir = d;
			world[nr][nc].weight += w;
			world[nr][nc].speed += s;

			if (d % 2 == 0) {
				world[nr][nc].even++;
			}
			else {
				world[nr][nc].odd++;
			}
		}

		// 2. 파이어볼 여러 개가 위치한 칸에 대한 갱신
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (world[i][j].count == 0)
					continue;

				if (world[i][j].count == 1) {
					fireball_info.push_back({ i, j, 
						world[i][j].weight, world[i][j].speed, world[i][j].dir });
				}
				else {
					// 질량은 sum / 5, 속력은 sum / cnt
					int w = world[i][j].weight / 5;
					int s = world[i][j].speed / world[i][j].count;

					// 질량이 0이 된 파이어볼은 소멸
					if (w <= 0)
						continue;

					// 모두 짝수거나 홀수 방향인 경우 0, 2, 4, 6 방향으로 파이어볼 분해
					if (world[i][j].odd == world[i][j].count || world[i][j].even == world[i][j].count) {
						fireball_info.push_back({ i, j, w, s, 0 });
						fireball_info.push_back({ i, j, w, s, 2 });
						fireball_info.push_back({ i, j, w, s, 4 });
						fireball_info.push_back({ i, j, w, s, 6 });
					}
					else {
						fireball_info.push_back({ i, j, w, s, 1 });
						fireball_info.push_back({ i, j, w, s, 3 });
						fireball_info.push_back({ i, j, w, s, 5 });
						fireball_info.push_back({ i, j, w, s, 7 });
					}
				}
			}
		}

		
	}

	int answer = 0;

	//cout << fireball_info.size() << endl;

	//cout << "weight info\n";
	for (int i = 0; i < fireball_info.size(); i++) {
		//cout << fireball_info[i][2] << endl;
		answer += fireball_info[i][2];
	}
	cout << answer;

	return 0;
}