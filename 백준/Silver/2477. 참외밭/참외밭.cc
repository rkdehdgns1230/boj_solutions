#include <bits/stdc++.h>

#define MAX 2001

using namespace std;

int k;

// 1: 동, 2: 서, 3: 남, 4: 북
int dx[] = { 0, 0, 0, 1, -1 };
int dy[] = { 0, 1, -1, 0, 0 };

int len[12];
int dir[12];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k;

	// 12개 길이의 배열로 만들어 ABAB 패턴을 찾는다. -> 여기가 작은 사각형을 찾을 수 있는 위치
	for (int i = 0; i < 6; i++) {
		cin >> dir[i] >> len[i];
		
		dir[i + 6] = dir[i];
		len[i + 6] = len[i];
	}
	
	for (int i = 3; i < 12; i++) {
		//ABAB 패턴을 찾은 케이스
		if (dir[i] == dir[i - 2] && dir[i - 1] == dir[i - 3]) {
			int big_area = len[i + 1] * len[i + 2];
			int small_area = len[i - 2] * len[i - 1];

			cout << (big_area - small_area) * k << "\n";

			break;
		}
	}


	return 0;
}