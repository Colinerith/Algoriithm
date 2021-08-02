// 그래프 #4: 파핑파핑 지뢰찾기
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int T, test_case, n, cnt;
int map[300][300];
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void numbering() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == -1)
				continue;
			for (int k = 0; k < 8; k++) {
				if (i + dx[k] >= 0 && i + dx[k] < n && j + dy[k] >= 0 && j + dy[k] < n && map[i + dx[k]][j + dy[k]] == -1)
					map[i][j]++;
			}
		}
	}
}

void popping(int x, int y) { // 0 주변 터뜨리기
	map[x][y] = -3;
	for (int k = 0; k < 8; k++) {
		if (x + dx[k] >= 0 && x + dx[k] < n && y + dy[k] >= 0 && y + dy[k] < n) {
			if (map[x + dx[k]][y + dy[k]] == 0)
				popping(x + dx[k], y + dy[k]);
			else if (map[x + dx[k]][y + dy[k]] >= 0)
				map[x + dx[k]][y + dy[k]] = -2;
		}
	}
}

void counting() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0) {
				popping(i, j);
				cnt++;
			}
		}
	}
	// 남은 숫자 세기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > 0)
				cnt++;
		}
	}
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n;
		cnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				map[i][j] = 0;
		}
		char a;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a;
				if(a=='*')
					map[i][j] = -1; // 지뢰
			}
		}
		numbering();
		counting();
		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}
