#include<iostream>
#include<queue>
using namespace std;

//dfs와 bfs
//vector<vector<int>> graph(1001, vector<int>(10001, 0)); //0대신 -1넣으면 -1로 초기화됨
bool graph[1001][1001];
bool visited[1001];
bool visited2[1001];
int n, m, start, a, b;

void dfs(int start) {
	visited[start] = true;
	cout << start << " ";
	for (int i = 1; i <= n; i++) {
		if (graph[start][i] == 1) {
			if (!visited[i])
				dfs(i);
		}
	}
}

void bfs(int start) {
	queue<int> q;
	q.push(start);
	int cur;
	visited2[start] = true;

	while (!q.empty()) {
		cur = q.front();
		cout << cur << " ";
		q.pop();
		for (int i = 1; i <= n; i++) {
			if (graph[cur][i] == 1) {
				if (!visited2[i]) {
					visited2[i] = true;
					q.push(i);
				}
			}
		}
	}
}

int main() {
	/// 모든 값이 0으로 초기화된 1000*10000배열

	cin >> n >> m >> start;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

	dfs(start);
	cout << "\n";
	bfs(start);

}
