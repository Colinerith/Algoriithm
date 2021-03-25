//나이트의 이동 https://www.acmicpc.net/problem/7562
/*
입력의 첫째 줄에는 테스트 케이스의 개수가 주어진다.
각 테스트 케이스는 세 줄로 이루어져 있다.
첫째 줄에는 체스판의 한 변의 길이 l(4 ≤ l ≤ 300)이 주어진다.
체스판의 크기는 l × l이다.
체스판의 각 칸은 두 수의 쌍 {0, ..., l-1} × {0, ..., l-1}로 나타낼 수 있다.
둘째 줄과 셋째 줄에는 나이트가 현재 있는 칸,
나이트가 이동하려고 하는 칸이 주어진다.

각 테스트 케이스마다 나이트가 최소 몇 번만에 이동할 수 있는지 출력한다.
*/

#include<iostream>
#include<queue>

using namespace std;
int l, ax, ay, bx, by, sum;
int graph[300][300];

// 나이트의 이동 가능 범위
int dx[8] = { 1, 1, 2, 2, -1, -1, -2, -2 };
int dy[8] = { 2, -2, 1, -1, 2, -2, 1, -1 };

// 최단거리니까 bfs
void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });

	while (!q.empty()) {
		int nx = q.front().first;
		int ny = q.front().second;
		q.pop();
		if (nx == bx && ny == by) {
			cout << graph[nx][ny] - 1 << "\n";;
			return;
		}
		for (int i = 0; i < 8; i++) {
			if ((nx + dx[i]) >= 0 && (nx + dx[i]) < l &&
				(ny + dy[i]) >= 0 && (ny + dy[i]) < l &&
				graph[nx + dx[i]][ny + dy[i]] == 0) {
				q.push({ nx + dx[i], ny + dy[i] });
				graph[nx + dx[i]][ny + dy[i]] = graph[nx][ny] + 1;
			}
		}
	}
}

int main(){
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 300; i++) {
			for (int j = 0; j < 300; j++) {
				graph[i][j] = 0;
			}
		}
		cin >> l;
		cin >> ax >> ay;
		cin >> bx >> by;
		graph[ax][ay] = 1;
		bfs(ax, ay);
	}
}
