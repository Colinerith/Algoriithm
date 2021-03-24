//유기농 배추
/*
입력의 첫 줄에는 테스트 케이스의 개수 T가 주어진다.
그 다음 줄부터 각각의 테스트 케이스에 대해 첫째 줄에는
배추를 심은 배추밭의 가로길이 M(1 ≤ M ≤ 50)과 세로길이 N(1 ≤ N ≤ 50),
그리고 배추가 심어져 있는 위치의 개수 K(1 ≤ K ≤ 2500)이 주어진다.
그 다음 K줄에는 배추의 위치 X(0 ≤ X ≤ M-1), Y(0 ≤ Y ≤ N-1)가 주어진다.

각 테스트 케이스에 대해 필요한 최소의 배추흰지렁이 마리 수를 출력한다.
*/
#include<iostream>
using namespace std;

int t, m, n, k, x, y;
bool graph[51][51];
int sum;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void dfs(int i, int j) {
	graph[i][j] = 0;

	for (int t = 0; t < 4; t++) {
		if ((i+dx[t])>=0 && (i+dx[t])<m && (j+dy[t])>=0 && (j+dy[t])<n && graph[i + dx[t]][j + dy[t]] == 1)
			dfs(i + dx[t], j + dy[t]);
	}
}

int main() {
	cin >> t;
	while (t--) {
		sum = 0;
		cin >> m >> n >> k; //배추밭 가로*세로, 배추개수
		for (int i = 0; i < k; i++) {
			cin >> x >> y;
			graph[x][y] = 1;
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j] == 1) {
					dfs(i, j);
					sum++;
				}
			}
		}
		cout << sum << "\n";
	}
}
