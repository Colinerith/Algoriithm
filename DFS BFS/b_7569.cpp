//토마토2
#include<iostream>
#include<queue>

using namespace std;

int m, n, h, a;
vector<int> b(3);
int zero; //안익은 토마토의 수. 익게 만들때마다 빼서 0이어야 다익힌거
int graph[101][101][101];
queue<vector<int>> q; //'1'의 x,y,z 위치를 기억하는 벡터
int dx[6] = { 1, -1, 0, 0, 0, 0 };
int dy[6] = { 0, 0, 1, -1, 0, 0 };
int dz[6] = { 0, 0, 0, 0, 1, -1 };
//int day;

void bfs() {

	while (!q.empty()) {
		int x = q.front()[0];
		int y = q.front()[1];
		int z = q.front()[2];

		for (int i = 0; i < 6; i++) {
			if ((x + dx[i]) >= 0 && (y + dy[i]) >= 0 &&
				(x + dx[i]) < n && (y + dy[i]) < m &&
				(z + dz[i]) >= 0 && (z + dz[i]) < h &&
				graph[x + dx[i]][y + dy[i]][z + dz[i]] == 0) {
				graph[x + dx[i]][y + dy[i]][z + dz[i]] = graph[x][y][z] + 1;
				b[0] = x + dx[i]; b[1] = y + dy[i]; b[2] = z + dz[i];
				q.push(b);
				zero--;
			}
		}
		if (zero == 0) {
			cout << graph[x][y][z] << "\n";
			return;
		}
		q.pop();
	}
}

int main() {
	bool flag = false; //0이 등장하면 true로 바꾼다. 입력부터 다익어있는지 확인용
	zero = 0;
	cin >> m >> n >> h;

	for (int z = 0; z < h; z++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a;
				graph[i][j][z] = a;
				if (a == 0) {
					flag = true;
					zero++;
				}
				else if (a == 1) {
					b[0] = i; b[1] = j; b[2] = z;
					q.push(b);
				}
			}
		}
	}
	if (flag == false) {
		cout << 0 << "\n";
		return 0;
	}
	bfs();
	if (zero != 0)
		cout << -1 << "\n";
}
