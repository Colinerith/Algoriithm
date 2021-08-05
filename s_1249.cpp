// 보급로 - 우선순위 큐 (heap)
#include<iostream>
#include<queue>
using namespace std;

int T, test_case, n;
int map[100][100];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int cost[100][100];

struct Node {
	int x;
	int y;
	int time;
	Node(int _x, int _y, int t) {
		x = _x;
		y = _y;
		time = t;
	}
};

struct comp {
	bool operator()(Node a, Node b) {
		if (a.time == b.time) {
			if (a.x == b.x)
				return a.y < b.y;
			return a.x < b.x;
		}
		return a.time > b.time;
	}
};

int main(int argc, char** argv) {
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d", &n);
		char a;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a;
				map[i][j] = (a - '0');
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cost[i][j] = 1000;
			}
		}
		int totalTime;
		priority_queue<Node, vector<Node>, comp> q;
		q.push(Node(0, 0, 0));
		cost[0][0] = 0;
		while (!q.empty()) {
			int x = q.top().x;
			int y = q.top().y;
			int t = q.top().time;
			q.pop();
			if (x == n - 1 && y == n - 1) {
				totalTime = t;
				break;
			}

			for (int i = 0; i < 4; i++) {
				if ((x + dx[i]) >= 0 && (x + dx[i]) < n && (y + dy[i]) >= 0 && (y + dy[i]) < n &&
					(cost[x + dx[i]][y + dy[i]] > t + map[x + dx[i]][y + dy[i]])) {
					q.push(Node(x + dx[i], y + dy[i], t + map[x + dx[i]][y + dy[i]]));
					cost[x + dx[i]][y + dy[i]] = t + map[x + dx[i]][y + dy[i]];
				}
			}
		}
		printf("#%d %d\n", test_case, totalTime);
	}
	return 0;
}
