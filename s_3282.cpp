#include<iostream>
using namespace std;

int T, test_case;
pair<int, int> arr[101];
int d[101][1001];

int max(int a, int b) {
	return a > b ? a : b;
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int n; // 물건 수
		int k; // 가방 부피
		int v, c; // 물건의 부피, 가치
		cin >> n >> k;
		//arr[0] = { 0,0 };
		for (int i = 1; i <= n; i++) {
			cin >> v >> c;
			arr[i] = { v, c };
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= k; j++){ // k는 부피허용치
				if (arr[i].first > j)
					d[i][j] = d[i - 1][j];
				else
					d[i][j] = max(arr[i].second + d[i - 1][j - arr[i].first], d[i - 1][j]);
			}
		}
		printf("#%d %d\n", test_case, d[n][k]);
	}
	return 0;
}
