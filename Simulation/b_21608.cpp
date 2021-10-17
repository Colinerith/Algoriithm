// 상어 초등학교_오전 1번
#include<iostream>
#include<queue>
using namespace std;
int map[20][20];
int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

struct student {
	int num;
	int friends[4];
} st[401];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, a, b, c, d, e;
	int stNum = 0;
	queue<student> students;
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a >> b >> c >> d >> e;
			st[a] = { a, {b,c,d,e} };
			students.push(st[a]);
		}
	}
	map[1][1] = students.front().num;
	students.pop();

	while (!students.empty()) {
		student s = students.front();
		students.pop();
		
		int x = 0; int y = 0;
		int maxFriendCnt = -1; int maxNullCnt = -1;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j] == 0) {
					int nx, ny;
					int tmpFriendCnt = 0; int tmpNullCnt = 0;
					for (int k = 0; k < 4; k++) {
						nx = i + dx[k]; ny = j + dy[k];
						if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
							if (map[nx][ny] == s.friends[0] ||
								map[nx][ny] == s.friends[1] ||
								map[nx][ny] == s.friends[2] ||
								map[nx][ny] == s.friends[3])
								tmpFriendCnt++;
							else if (map[nx][ny] == 0)
								tmpNullCnt++;
						}
					}
					if (tmpFriendCnt > maxFriendCnt) {
						maxFriendCnt = tmpFriendCnt;
						maxNullCnt = tmpNullCnt;
						x = i; y = j;
					}
					else if (tmpFriendCnt == maxFriendCnt &&
						tmpNullCnt > maxNullCnt) {
						maxNullCnt = tmpNullCnt;
						x = i; y = j;
					}
				}
			}
		}
		map[x][y] = s.num;
	}

	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int nx, ny;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				nx = i + dx[k]; ny = j + dy[k];
				if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
					if (map[nx][ny] == st[map[i][j]].friends[0] ||
						map[nx][ny] == st[map[i][j]].friends[1] ||
						map[nx][ny] == st[map[i][j]].friends[2] ||
						map[nx][ny] == st[map[i][j]].friends[3])
						cnt++;
				}
			}
			switch (cnt) {
			case 1: score += 1; break;
			case 2: score += 10; break;
			case 3: score += 100; break;
			case 4: score += 1000; break;
			}
		}
	}
	cout << score;
}
