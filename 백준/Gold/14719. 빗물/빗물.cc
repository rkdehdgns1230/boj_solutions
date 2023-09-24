#include <bits/stdc++.h>

#define MAX 501

using namespace std;

int h, w;
int floor_level[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int answer = 0;
	cin >> h >> w;

	for (int i = 0; i < w; i++) {
		cin >> floor_level[i];
	}
	
	int prev = floor_level[0]; // 현재 칸에 물이 고일 때, 이전 벽의 높이 (수위 기준 선)
	
	int result = 0;
	for (int i = 1; i < w; i++) {
		int cur = floor_level[i];

		// 이전에 설정된 벽 (물을 채운다.)
		if (cur < prev) {
			result += (prev - cur);
		}
		// 새로운 칸의 바닥 높이가 기존 벽보다 높은 경우
		else if (cur >= prev) {
			prev = cur;
			answer += result;
			//cout << result << " 만큼 물이 차오릅니다.\n";
			result = 0;
		}
	}

	result = 0;
	prev = floor_level[w - 1];
	for (int i = w - 2; i >= 0; i--) {
		int cur = floor_level[i];

		// 이전에 설정된 벽 (물을 채운다.)
		if (cur < prev) {
			result += (prev - cur);
		}
		// 새로운 칸의 바닥 높이가 기존 벽보다 높은 경우
		else if (cur > prev) {
			prev = cur;
			answer += result;
			//cout << result << " 만큼 물이 차오릅니다.\n";
			result = 0;
		}
	}

	cout << answer << endl;

	return 0;
}