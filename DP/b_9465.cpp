/*
입력
첫째 줄에 테스트 케이스의 개수 T가 주어진다.
각 테스트 케이스의 첫째 줄에는 n (1 ≤ n ≤ 100,000)이 주어진다.
다음 두 줄에는 n개의 정수가 주어지며, 각 정수는 그 위치에 해당하는 스티커의 점수이다.
연속하는 두 정수 사이에는 빈 칸이 하나 있다.
점수는 0보다 크거나 같고, 100보다 작거나 같은 정수이다.

출력
각 테스트 케이스 마다,
2n개의 스티커 중에서 두 변을 공유하지 않는 스티커 점수의 최댓값을 출력한다.
*/

#include<iostream>
using namespace std;
#define max(a, b) ((a>b)?a:b)

int d[100001][3];
int a[2][100001];

int main() {
	ios::sync_with_stdio(false);
	int t, n;
	cin >> t;
	while (t--) {
		for (int i = 0; i <= 100000; i++) {
			d[i][0] = 0; d[i][1] = 0; d[i][2] = 0;
			a[0][i] = 0; a[1][i] = 0;
		}
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[0][i];
		}
		for (int i = 0; i < n; i++) {
			cin >> a[1][i];
		}
		d[0][0] = 0; d[0][1] = 0; d[0][2] = 0;

		for (int i = 1; i <= n; i++) {
			d[i][0] = max(d[i - 1][0], max(d[i - 1][1], d[i - 1][2]));
			d[i][1] = max(d[i - 1][0], d[i - 1][2]) + a[0][i - 1];
			d[i][2] = max(d[i - 1][0], d[i - 1][1]) + a[1][i - 1];
		}
		cout << max(d[n][0], max(d[n][1], d[n][2]))<<"\n";
	}
}
