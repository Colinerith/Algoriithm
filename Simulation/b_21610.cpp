// 비바라기 _ 오후 1번
#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[51][51];
int dr[9] = { 100, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[9] = { 100, -1, -1, 0, 1, 1, 1, 0, -1 };
int dr2[4] = { -1, -1, 1, 1 };
int dc2[4] = { -1, 1, -1, 1 };

bool previous[51][51] = { false, };

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) { // 맵 입력
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	queue<pair<int, int>> clouds;
	clouds.push({ n, 1 });
	clouds.push({ n, 2 });
	clouds.push({ n - 1, 1 });
	clouds.push({ n - 1, 2 });

	int d, s;
	for (int i = 0; i < m; i++) { // 이동 명령
		cin >> d >> s;

		int qCnt = clouds.size();
		while (qCnt--) {
			int r = clouds.front().first;
			int c = clouds.front().second;
			clouds.pop();

			int next_r = ((r + dr[d] * s) + n * 100) % n;
			int next_c = ((c + dc[d] * s) + n * 100) % n;
			if (next_r == 0) next_r += n;
			if (next_c == 0) next_c += n;

			clouds.push({ next_r, next_c });

			map[next_r][next_c]++;
			previous[next_r][next_c] = true;
		}

		while (!clouds.empty()) {
			int r = clouds.front().first;
			int c = clouds.front().second;
			clouds.pop();

			int cnt = 0;
			for (int j = 0; j < 4; j++) {
				if (r + dr2[j] >= 1 && r + dr2[j] <= n &&
					c + dc2[j] >= 1 && c + dc2[j] <= n &&
					map[r+dr2[j]][c+dc2[j]] >= 1)
					cnt++;
			}
			map[r][c] += cnt;
		}

		for (int t = 1; t <= n; t++) {
			for (int k = 1; k <= n; k++) {
				if (map[t][k] >= 2 && previous[t][k] == false) {
					clouds.push({ t,k });
					map[t][k] -= 2;
				}
			}
		}

		for (int t = 1; t <= n; t++) {
			for (int k = 1; k <= n; k++)
				previous[t][k] = false;
		}
	}

	int sum = 0;
	for (int t = 1; t <= n; t++) {
		for (int k = 1; k <= n; k++)
			sum += map[t][k];
	}
	cout << sum;
}
