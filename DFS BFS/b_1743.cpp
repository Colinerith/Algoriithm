/*
첫째 줄에 통로의 세로 길이 N(1 ≤ N ≤ 100)과 가로 길이 M(1 ≤ M ≤ 100)
그리고 음식물 쓰레기의 개수 K(1 ≤ K ≤ 10,000)이 주어진다.
다음 K개의 줄에 음식물이 떨어진 좌표 (r, c)가 주어진다.

좌표 (r, c)의 r은 위에서부터, c는 왼쪽에서부터가 기준이다.

첫째 줄에 음식물 중 가장 큰 음식물의 크기를 출력하라.
*/

#include<iostream>
using namespace std;

bool graph[100][100];
int n, m, k, r, c, sum;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void dfs(int x, int y) {
	graph[x][y] = 0;
	sum++;
	for (int i = 0; i < 4; i++) {
		if ((x + dx[i]) >= 0 && (x + dx[i]) < n && (y + dy[i]) >= 0 && (y + dy[i]) < m &&
			graph[x + dx[i]][y + dy[i]] == 1)
			dfs(x + dx[i], y + dy[i]);
	}
}
int main() {
	cin >> n >> m >> k;
	int max = 0;
	while (k--) {
		cin >> r >> c;
		graph[r - 1][c - 1] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (graph[i][j] == 1) {
				sum = 0;
				dfs(i, j);
				if (sum > max)
					max = sum;
			}
		}
	}
	cout << max << "\n";
}
