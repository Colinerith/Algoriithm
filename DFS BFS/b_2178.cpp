//미로탈출 bfs dfs 문제

#include<iostream>
#include<queue>
#include<string>
using namespace std;

int a, b;
int maze[100][100];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int bfs() {
	queue<pair<int, int>> q;
	q.push({ 0,0 });
	int x, y, nx, ny;

	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (nx < 0 || nx >= a || ny < 0 || ny >= b)
				continue;
			if (maze[nx][ny] == 1) { //갈수있는
				q.push({ nx,ny });
				maze[nx][ny] = maze[x][y] + 1;
			}
		}
	}
	return maze[a - 1][b - 1];
}
int main() {
	string input;
	cin >> a >> b;
	for (int i = 0; i < a; i++) {
		cin >> input;
		for (int j = 0; j < b; j++) {
			maze[i][j] = input.at(j)-'0';
		}
	}
	cout << bfs() << endl;
}
