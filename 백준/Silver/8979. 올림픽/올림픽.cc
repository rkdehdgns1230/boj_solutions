#include <bits/stdc++.h>

#define MAX 1001
#define SCORE_MAX 
using namespace std;

int n, k;

int gold[MAX];
int silver[MAX];
int bronze[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		cin >> gold[num] >> silver[num] >> bronze[num];
	}

	int my_rank = 1;

	for (int i = 1; i <= n; i++) {
		if (gold[i] > gold[k]) {
			my_rank++;
		}
		else if (gold[i] == gold[k]) {
			if (silver[i] > silver[k])
				my_rank++;
			else if (silver[i] == silver[k] && bronze[i] > bronze[k])
				my_rank++;
		}
	}
	cout << my_rank;

	return 0;
}