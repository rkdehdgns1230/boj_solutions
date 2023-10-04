#include <bits/stdc++.h>

#define MAX 9

using namespace std;

int answer;

int n;

int egg_weight[MAX];
int egg_durability[MAX];

void simulation(int idx) {
	if (idx == n) {
		int result = 0;
		// 마지막 계란까지 부딪히기를 끝낸 경우
		for (int i = 0; i < n; i++)
			if (egg_durability[i] <= 0)
				result++;
		//cout << result << " 결과 비교.\n";
		answer = max(answer, result);
		return;
	}
	
	// idx번째 계란을 들고 나머지 계란과 부딪히는 작업을 수행한다.
	// 매번 수행마다 내구도 정보를 넘겨서 확인

	// 박살난 계란은 건너 띈다.
	if (egg_durability[idx] <= 0) {
		simulation(idx + 1);
		return;
	}

	bool canHit = false;
	
	for (int i = 0; i < n; i++) {
		// 현재 계란과 이미 박살난 계란의 경우 건너띈다.
		if (i == idx || egg_durability[i] <= 0)
			continue;

		canHit = true;
		// 계란을 부딪히고, 다음 계란으로 시뮬레이션 이동 (서로의 무게만큼 내구도 깎임)
		egg_durability[idx] -= egg_weight[i];
		egg_durability[i] -= egg_weight[idx];
		//cout << idx << "와 " << i << " 계란을 부딪히자.\n";
		//cout << egg_durability[idx] << ", " << egg_durability[i] << endl;
		simulation(idx + 1);

		egg_durability[idx] += egg_weight[i];
		egg_durability[i] += egg_weight[idx];
	}

	// 나머지 계란이 모두 박살난 경우 건너 띈다.
	if (!canHit) {
		simulation(idx + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> egg_durability[i] >> egg_weight[i];
	}
	
	simulation(0);

	cout << answer;

	return 0;
}