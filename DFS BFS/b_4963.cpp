/*
입력은 여러 개의 테스트 케이스로 이루어져 있다.
각 테스트 케이스의 첫째 줄에는 지도의 너비 w와 높이 h가 주어진다.
w와 h는 50보다 작거나 같은 양의 정수이다.
둘째 줄부터 h개 줄에는 지도가 주어진다. 1은 땅, 0은 바다이다.
입력의 마지막 줄에는 0이 두 개 주어진다.

각 테스트 케이스에 대해서, 섬의 개수를 출력한다.
대각선도 포함되는거 주의***
*/

#include<iostream>
using namespace std;

bool graph[50][50];
int n, m, c, sum;
int dx[8] = { 1,-1,0,0, 1, 1 , -1, -1};
int dy[8] = { 0,0,1,-1, 1, -1, 1, -1 };

void dfs(int x, int y) {
	graph[x][y] = 0;
	for (int i = 0; i < 8; i++) {
		if ((x + dx[i]) >= 0 && (x + dx[i]) < m && (y + dy[i]) >= 0 && (y + dy[i]) < n &&
			graph[x + dx[i]][y + dy[i]] == 1)
			dfs(x + dx[i], y + dy[i]);
	}
}
int main() {
	while (true) {
		sum = 0;
		cin >> n >> m;
		if (n == 0)
			break;
		for (int i = 0; i < m; i++) {
			for (int j= 0; j < n; j++) {
				cin >> c;
				graph[i][j] = c;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j] == 1) {
					sum++;
					dfs(i, j);
				}
			}
		}
		cout << sum << "\n";
	}
}
