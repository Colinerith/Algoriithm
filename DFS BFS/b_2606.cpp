/*
첫째 줄에는 컴퓨터의 수가 주어진다.
컴퓨터의 수는 100 이하이고 각 컴퓨터에는 1번 부터 차례대로 번호가 매겨진다.
둘째 줄에는 네트워크 상에서 직접 연결되어 있는 컴퓨터 쌍의 수가 주어진다.
이어서 그 수만큼 한 줄에 한 쌍씩 네트워크 상에서 직접 연결되어 있는
컴퓨터의 번호 쌍이 주어진다.

1번 컴퓨터가 웜 바이러스에 걸렸을 때,
1번 컴퓨터를 통해 웜 바이러스에 걸리게 되는 컴퓨터의 수를 첫째 줄에 출력한다.
*/

#include<iostream>
using namespace std;
int com, n, a, b, sum;
int graph[100][100];
bool visited[1000];

void dfs(int x, int y) {
	sum++;
	visited[x] = 1;
	for (int i = 0; i < com; i++) {
		if (graph[x][i] == 1) {
			graph[x][i] = 0;
			if(visited[i] == 0)
				dfs(i, x);
		}
	}
}

int main() {
	cin >> com >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		graph[a - 1][b - 1] = 1;
		graph[b - 1][a - 1] = 1;
	}
	dfs(0 ,0);
	cout << sum - 1;
}
