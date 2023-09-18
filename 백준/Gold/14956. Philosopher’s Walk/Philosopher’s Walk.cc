#include <bits/stdc++.h>

using namespace std;

int n, m;

// 변의 길이, 걸어간 길이로 x, y 좌표를 재귀적으로 계산한다.
pair<int, int> philo(int side, int walk) {
	if (side == 2) {
		switch (walk) {
		case 1:
			return { 1, 1 };
		case 2:
			return { 1, 2 };
		case 3:
			return { 2, 2 };
		case 4:
			return { 2, 1 };
		}
	}

	int half_side = side / 2;
	int section = half_side * half_side; // 한 구간에서 걷는 거리를 계산

	// 남은 걸음 수로 section 구분
	if (walk <= section) {
		pair<int, int> site = philo(half_side, walk);
		return { site.second, site.first };
	}
	else if (walk <= 2 * section) {
		pair<int, int> site = philo(half_side, walk - section);
		return { site.first, half_side + site.second };
	}
	else if (walk <= 3 * section) {
		pair<int, int> site = philo(half_side, walk - 2 * section);
		return { half_side + site.first, half_side + site.second };
	}
	else {
		pair<int, int> site = philo(half_side, walk - 3 * section);
		return { side - site.second + 1, half_side - site.first + 1 };
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	pair<int, int> res = philo(n, m);
	cout << res.first << " " << res.second;

	return 0;
}