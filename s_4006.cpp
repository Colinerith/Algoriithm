// 그래프 #7: 고속도로 건설 - 성공
/* 시간 줄이기
root 번호를 재귀적으로 탐색할 때 거쳐 온 노드들의 부모를 root로 변경.
즉 해당 집합의 모든 노드가 root의 직계 자손이 되도록 함.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int T, test_case, n, m, cost;

struct Edge {
	int start;
	int end;
	int cost;
	Edge* alloc(int s, int e, int c) {
		start = s;
		end = e;
		cost = c;
		return this;
	}
};

Edge edges[200000];
int edgeCnt;

bool comp (Edge* a, Edge* b) {
	return a->cost < b->cost;
};

int parent[50001];

int findSet(int v, int newRoot) {
	if (parent[v] < 0) return v;
	int p = findSet(parent[v], newRoot);
	if (newRoot != -1) // 시간 줄일 수 있는 부분
		parent[v] = newRoot;
	return p;
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d %d", &n, &m);
		int s, e, c;

		for (int i = 1; i <= n; i++) {
			parent[i] = -1;
		}
		cost = 0;
		vector<Edge*> v;
		edgeCnt = 0;

		for (int i = 0; i < m; i++) { // 양쪽 연결
			scanf("%d %d %d", &s, &e, &c);
			v.push_back(edges[edgeCnt++].alloc(s, e, c));
		}
		sort(v.begin(), v.end(), comp);

		int selectCnt = 0;
		int idx = 0;
		while (selectCnt < n - 1) {
			int u = v[idx]->start;
			int vv = v[idx]->end;
			int c = v[idx]->cost;
			idx++;

			//union-set
			int r1 = findSet(u, -1);
			int r2 = findSet(vv, r1);
			if (r1 == r2) continue;
			parent[r1] += parent[r2];
			parent[r2] = r1;

			cost += c;
			selectCnt++;
		}

		printf("#%d %d\n", test_case, cost);
	}
	return 0;
}
