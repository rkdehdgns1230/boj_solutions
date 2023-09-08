#include <bits/stdc++.h>

#define MAX 500001

using namespace std;

int arr[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	stack<int> S;
	vector<int> V(MAX, 0);
	int n;

	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	for(int i = n; i >= 1; i--) {
		int currentTower = arr[i];
			
		while (!S.empty() && arr[S.top()] < currentTower) {
			int top = S.top();
			S.pop();
			//L.push_front(i);
			V[top] = i;
		}

		S.push(i);
	}


	for (int i = 1; i <= n; i++) {
		cout << V[i] << " ";
	}

	return 0;
}