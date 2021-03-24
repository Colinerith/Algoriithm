#include<iostream>
#include<queue>
using namespace std;

int m, n, a;
int zero; //안익은 토마토의 수. 익게 만들때마다 빼서 0이어야 다익힌거
int graph[1001][1001];
queue<pair<int, int>> q; //'1'의 x,y 위치를 기억하는 벡터
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
//int day;

void bfs() {
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;

		for (int i = 0; i < 4; i++) {
			if ((x + dx[i]) >= 0 && (y + dy[i]) >= 0 &&
				(x + dx[i]) < n && (y + dy[i]) < m &&
				graph[x + dx[i]][y + dy[i]] == 0) {
				graph[x + dx[i]][y + dy[i]] = graph[x][y] + 1;
				q.push({ x + dx[i] , y + dy[i] });
				zero--;
			}
		}
		if (zero == 0) {
			cout << graph[x][y] << "\n";
			return;
		}
		q.pop();
	}
}

int main() {
	bool flag = false; //0이 등장하면 true로 바꾼다. 입력부터 다익어있는지 확인용
	zero = 0;
	cin >> m >> n;
	//day = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a;
			graph[i][j] = a;
			if (a == 0) {
				flag = true;
				zero++;
			}
			else if (a == 1) {
				q.push({ i,j });
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
	//cout << day << "\n";
}
