#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> adj;
int check[100001];
int depth[100001];
int parent[100001][17];
int T, test_case, n;
int vertex[100001]; // 정점 번호들을 bfs 방문 순서대로 저장

int lca(int a, int b) {
	if (depth[a] > depth[b])
		swap(a, b);
	// depth 맞추기
	for (int i = 19; i >= 0; i--) {
		if ((depth[b] - depth[a]) >= (1 << i))
			b = parent[b][i];
	}

	// 부모가 같을 때까지 올라감
	if (a == b) return a;
	for (int i = 16; i >= 0; i--) {
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i]; b = parent[b][i];
		}
	}
	return parent[a][0];
}

int main(int argc, char** argv) {
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		adj.clear();
		scanf("%d", &n);
		adj.resize(n + 1);
		for (int i = 2; i <= n; i++) {
			int a;
			scanf("%d", &a);
			adj[a].push_back(i);
		}
		//memset(parent, -1, sizeof(parent));

		for (int i = 1; i <= n; i++) {
			check[i] = false;
			depth[i] = 0;
			for (int j = 0; j <= 16; j++)
				parent[i][j] = 0;
		}
		//bfs
		queue<int> q;
		depth[1] = 0;
		check[1] = true;
		int idx = 1;
		vertex[0] = 1;

		q.push(1);
		while (!q.empty()) {
			int num = q.front();
			q.pop();
			for (int i : adj[num]) {
				if (check[i] == false) {
					parent[i][0] = num;
					depth[i] = depth[num] + 1;
					check[i] = true;
					vertex[idx++] = i;
					q.push(i);
				}
			}
		}
		// 2^k 깊이 설정
		for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= n; j++)
				parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
		long long int sum = 0;
		for (int i = 0; i < n-1; i++)
			sum += depth[vertex[i]] + depth[vertex[i + 1]] - 2 * depth[lca(vertex[i], vertex[i + 1])];

		cout << "#" << test_case << " " << sum << "\n";
	}
	return 0;
}
