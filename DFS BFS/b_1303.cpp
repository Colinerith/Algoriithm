#include<iostream>
using namespace std;

/*
첫째 줄에는 전쟁터의 가로 크기 N, 세로 크기 M(1 ≤ N, M ≤ 100)이 주어진다.
그 다음 두 번째 줄에서 M+1번째 줄에는 각각 (X, Y)에 있는 병사들의 옷색이
띄어쓰기 없이 주어진다. 모든 자리에는 병사가 한 명 있다.
(B는 파랑, W는 흰색이다.)

첫 번째 줄에 당신의 병사의 위력의 합과 적국의 병사의 위력의 합을 출력한다.
*/
int n, m, x, y, sumo, sumy, scoreo, scorey;
bool our[100][100];
bool your[100][100];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void dfs_our(int x, int y) {
	our[x][y] = 0;
	sumo++;
	for (int i = 0; i < 4; i++) {
		if ((x + dx[i]) >= 0 && (x + dx[i]) < m && (y + dy[i]) >= 0 && (y + dy[i]) < n &&
			our[x + dx[i]][y + dy[i]] == 1) {
			dfs_our(x + dx[i], y + dy[i]);
		}
	}
}
void dfs_your(int x, int y) {
	your[x][y] = 0;
	sumy++;
	for (int i = 0; i < 4; i++) {
		if ((x + dx[i]) >= 0 && (x + dx[i]) < m && (y + dy[i]) >= 0 && (y + dy[i]) < n &&
			your[x + dx[i]][y + dy[i]] == 1) {
			dfs_your(x + dx[i], y + dy[i]);
		}
	}
}

int main() {
	cin >> n >> m;
	char c;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> c;
			if (c == 'W')
				our[i][j] = 1;
			else
				your[i][j] = 1;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (our[i][j] == 1) {
				sumo = 0;
				dfs_our(i, j);
				scoreo += sumo * sumo;
			}
			else if (your[i][j] == 1) {
				sumy = 0;
				dfs_your(i, j);
				scorey += sumy * sumy;
			}
		}
	}
	cout << scoreo << " " << scorey << "\n";
}
