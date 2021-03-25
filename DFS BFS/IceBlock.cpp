#include<iostream>
#include<vector>
using namespace std;

int n, m;
int graph[1001][1001];

//dfs로 전부 훑는데, 전의 시도에서 이미 방문됐으면 같은 묶음인거니까 false를 리턴하게 됨
//전에 방문된 적 없으면 새로운 묶음이니까 걔네는 true가 됨

bool dfs(int x, int y) {
	if (x <= -1 || x >= n || y <= -1 || y >= m) {
		return false;
	}
	if (graph[x][y] == 0) {
		graph[x][y] = 1;
		dfs(x - 1, y);
		dfs(x, y - 1);
		dfs(x + 1, y);
		dfs(x, y + 1);
		return true;
	}
	return false;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dfs(i, j)) { //true면 개수 증가
				result += 1;
			}
		}
	}
	cout << result << '\n';
}
