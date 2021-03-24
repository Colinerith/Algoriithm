#include<iostream>
#include<queue>
using namespace std;

int n, m;
int graph[201][201];
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int bfs(int x, int y) {
	queue < pair<int, int>> q;
	q.push({ x, y });

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; //pair라서
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			//미로찾기 공간을 벗어난 경우 무시
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			//벽인 경우 무시
			if (graph[nx][ny] == 0) continue;
			//해당 노드를 처음 방문하는 경우에만 최단 거리 기록
			if (graph[nx][ny] == 1) {
				graph[nx][ny] = graph[x][y] + 1;
				q.push({ nx,ny });
			}
		}
		return graph[n - 1][m - 1];
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
		}
	}
	cout << bfs(0, 0) << '\n';
	return 0;
}
