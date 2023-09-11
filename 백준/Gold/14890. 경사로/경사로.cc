#include <bits/stdc++.h>

#define MAX 101

using namespace std;

int N, L;
int answer = 0;
int arr[MAX][MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> L;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i][j];

	// 시간 여건 상 101 -> 3차원 for문까지 활용 가능

	// 통행 가능한 길의 조건
	// - 높이가 모두 동일
	// - 경사로 설치해서 통과 가능할 것

	for (int i = 0; i < N; i++) {
		// 하나의 for문을 이용해 row, column을 모두 살펴볼 것

		bool isSame = true;
		int tmp = arr[i][0];
		// 높이가 모두 동일한 케이스
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != tmp)
			{
				isSame = false;
				break;
			}
		}
		if (isSame) {
			//cout << "모든 높이가 같아서 성공" << endl;
			answer++;
			continue;
		}

		int prev = arr[i][0], cur;
		bool isOkay = true;
		bool isSetting = false; // 경사로 설치 중인지 여부 판단
		int runwayCnt = 0;

		bool isRunwaySet[MAX];
		fill(isRunwaySet, isRunwaySet + MAX, false);

		// 내리막길에 대한 판단
		// 높이가 차이나는 경우 경사로 길이만큼 같은 길이가 유지되는지 확인해야 함
		for (int j = 1; j < N; j++) {
			cur = arr[i][j];

			if (abs(prev - cur) > 1) {
				//cout << i << "번째는 경사로 설치 불가" << j << ", 높이는 " << cur << endl;
				isOkay = false;
				break;
			}

			if (isSetting) {
				// 경사로 설치 중인데 다른 높이가 나온 경우 or 이미 설치된 경우
				if (abs(prev - cur) == 1) {
					//cout << i << "번째는 경사로 설치 중 문제 발생\n";
					isOkay = false;
					break;
				}
				else {
					isRunwaySet[j] = true;
					runwayCnt++;

					// 설치가 완료
					if (runwayCnt == L) {
						//cout << i << "-" << j << "번째에서 내리막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}
			// 경사로 설치 중이지 않은 경우
			else {
				// 내리막 설치가 가능한 경우 (설치 시작)
				if (prev - cur == 1) {
					isSetting = true;
					runwayCnt = 1;
					isRunwaySet[j] = true;

					// 경사로 길이가 1인 경우 바로 설치 끝
					if (L == 1) {
						//cout << i << "-" << j << "번째에서 내리막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}

			prev = cur;
		}

		// 이미 실패한 경우 더 볼 필요 없음. (경사로 설치 중 실패한 경우도 포함)
		if (!isOkay || isSetting) {
			//cout << isOkay << " " << isSetting << endl;
			//cout << "이미 실패했거나 경사로 설치 중 종료\n";
			continue;
		}


		prev = arr[i][N - 1];

		// 오르막길에 대한 판단
		for (int j = N - 2; j >= 0; j--) {
			cur = arr[i][j];

			// 오르막 경사로 설치 중인 경우
			if (isSetting) {
				// 경사로 설치 중인데 다른 높이가 나온 경우 or 이미 설치된 경우
				if (abs(prev - cur) == 1 || isRunwaySet[j]) {
					//cout << i << "번째는 경사로 설치 중 문제 발생\n";
					isOkay = false;
					break;
				}
				else {
					isRunwaySet[j] = true;
					runwayCnt++;

					// 설치가 완료
					if (runwayCnt == L) {
						//cout << i << "-" << j << "번째에서 오르막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}
			// 경사로 설치 중이지 않은 경우
			else {
				// 내리막 설치가 가능한 경우 (설치 시작)
				if (prev - cur == 1 && !isRunwaySet[j]) {
					isSetting = true;
					runwayCnt = 1;
					isRunwaySet[j] = true;

					// 경사로 길이가 1인 경우 바로 설치 끝
					if (L == 1) {
						//cout << i << "-" << j << "번째에서 오르막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
				else if (prev - cur == 1 && isRunwaySet[j]) {
					//cout << i << "번째에서 경사로 중복되어 실패\n";
					isOkay = false;
					break;
				}
			}
			
			prev = cur;
		}

		// 경사로 설치에 성공한 경우 성공
		if (isOkay && !isSetting) {
			//cout << i << "번째에서" << endl;
			//cout << "경사로 설치에 성공해서 성공" << endl;
			answer++;
		}
	}

	for (int i = 0; i < N; i++) {
		// 하나의 for문을 이용해 row, column을 모두 살펴볼 것

		bool isSame = true;
		int tmp = arr[0][i];
		// 높이가 모두 동일한 케이스
		for (int j = 0; j < N; j++) {
			if (arr[j][i] != tmp)
			{
				isSame = false;
				break;
			}
		}
		if (isSame) {
			//cout << "모든 높이가 같아서 성공" << endl;
			answer++;
			continue;
		}

		int prev = arr[0][i], cur;
		bool isOkay = true;
		bool isSetting = false; // 경사로 설치 중인지 여부 판단
		int runwayCnt = 0;

		bool isRunwaySet[MAX];
		for (int j = 0; j < N; j++)
			isRunwaySet[j] = false;

		// 내리막길에 대한 판단
		// 높이가 차이나는 경우 경사로 길이만큼 같은 길이가 유지되는지 확인해야 함
		for (int j = 1; j < N; j++) {
			cur = arr[j][i];

			if (abs(prev - cur) > 1) {
				//cout << i << "번째는 경사로 설치 불가" << j << ", 높이는 " << cur << endl;
				isOkay = false;
				break;
			}

			if (isSetting) {
				// 경사로 설치 중인데 다른 높이가 나온 경우 or 이미 설치된 경우
				if (abs(prev - cur) == 1) {
					//cout << i << "번째는 경사로 설치 중 문제 발생\n";
					isOkay = false;
					break;
				}
				else {
					isRunwaySet[j] = true;
					runwayCnt++;

					// 설치가 완료
					if (runwayCnt == L) {
						//cout << i << "-" << j << "번째에서 내리막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}
			// 경사로 설치 중이지 않은 경우
			else {
				// 내리막 설치가 가능한 경우 (설치 시작)
				if (prev - cur == 1) {
					isSetting = true;
					runwayCnt = 1;
					isRunwaySet[j] = true;

					// 경사로 길이가 1인 경우 바로 설치 끝
					if (L == 1) {
						//cout << i << "-" << j << "번째에서 내리막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}

			prev = cur;
		}

		// 이미 실패한 경우 더 볼 필요 없음. (경사로 설치 중 실패한 경우도 포함)
		if (!isOkay || isSetting) {
			//cout << "이미 실패했거나 경사로 설치 중 종료\n";
			continue;
		}


		prev = arr[N - 1][i];

		// 오르막길에 대한 판단
		for (int j = N - 2; j >= 0; j--) {
			cur = arr[j][i];

			// 오르막 경사로 설치 중인 경우
			if (isSetting) {
				// 경사로 설치 중인데 다른 높이가 나온 경우 or 이미 설치된 경우
				if (abs(prev - cur) == 1 || isRunwaySet[j]) {
					//cout << i << "번째는 경사로 설치 중 문제 발생\n";
					isOkay = false;
					break;
				}
				else {
					isRunwaySet[j] = true;
					runwayCnt++;

					// 설치가 완료
					if (runwayCnt == L) {
						//cout << i << "-" << j << "번째에서 오르막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
			}
			// 경사로 설치 중이지 않은 경우
			else {
				// 내리막 설치가 가능한 경우 (설치 시작)
				if (prev - cur == 1 && !isRunwaySet[j]) {
					isSetting = true;
					runwayCnt = 1;
					isRunwaySet[j] = true;

					// 경사로 길이가 1인 경우 바로 설치 끝
					if (L == 1) {
						//cout << i << "-" << j << "번째에서 오르막 설치 성공!\n";
						isSetting = false;
						runwayCnt = 0;
					}
				}
				else if (prev - cur == 1 && isRunwaySet[j]) {
					//cout << i << "번째에서 경사로 중복되어 실패\n";
					isOkay = false;
					break;
				}
			}

			prev = cur;
		}

		// 경사로 설치에 성공한 경우 성공
		if (isOkay && !isSetting) {
			//cout << i << "번째에서" << endl;
			//cout << "경사로 설치에 성공해서 성공" << endl;
			answer++;
		}
	}

	cout << answer;

	return 0;
}