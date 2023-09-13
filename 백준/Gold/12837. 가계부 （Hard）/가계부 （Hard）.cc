#include <bits/stdc++.h>

#define MAX 1000001
#define TREE_MAX 5000001

using namespace std;

int n, q;

long long tree[TREE_MAX];

long long sum(int start, int end, int node, int left, int right) {
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right) + 
		sum(mid + 1, end, node * 2 + 1, left, right);
}

void update(int start, int end, int node, int idx, int diff) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] += diff;
		return;
	}
	
	int mid = (start + end) / 2;
	update(start, mid, node * 2, idx, diff);
	update(mid + 1, end, node * 2 + 1, idx, diff);

	// leaf 부터 update 하는 것이 국룰!
	tree[node] += diff;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < q; i++) {
		int op;
		cin >> op;

		// 내역 추가
		if (op == 1) {
			int day, diff;
			cin >> day >> diff;
			update(1, n, 1, day, diff);
		}
		// 내역 계산
		else {
			int start, end;
			cin >> start >> end;
			cout << sum(1, n, 1, start, end) << "\n";
		}
	}

	return 0;
}