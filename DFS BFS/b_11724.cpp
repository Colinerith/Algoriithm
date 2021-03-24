//연결 요소의 개수
/*
방향 없는 그래프가 주어졌을 때,
연결 요소 (Connected Component)의 개수를 구하는 프로그램
첫째 줄에 정점의 개수 N과 간선의 개수 M이 주어진다. (1 ≤ N ≤ 1,000, 0 ≤ M ≤ N×(N-1)/2)
둘째 줄부터 M개의 줄에 간선의 양 끝점 u와 v가 주어진다. (1 ≤ u, v ≤ N, u ≠ v)
같은 간선은 한 번만 주어진다.

첫째 줄에 연결 요소의 개수를 출력한다.

dfs로 풀자
*/

#include<iostream>
using namespace std;

int n, m, u, v;
bool graph[1001][1001];
bool visited[1001];

void dfs(int cur) {
	visited[cur] = 1;
	for (int i = 1; i <= n; i++) {
		if (graph[cur][i] == 1 && visited[i] == 0) {
			dfs(i);
		}
	}
}
int main() {
	cin >> n >> m;
	int sum = 0;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (visited[i] == 0) {
			dfs(i);
			sum++;
		}
	}
	cout << sum << endl;
}
