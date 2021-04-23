#include<iostream>
#include<vector>
using namespace std;

int flag[5];
int board[100][100];
int dx[4] = { 1, 0, 0, -1 }; //북 동 서 남
int dy[4] = { 0, -1, 1, 0 }; //북 동 서 남
int holedirection;
//int prevhole;
int t, n;
int x, y;
vector <vector<pair<int, int>>> pairs;

int go(int direction, int sx, int sy, int score, int hole) { //start_x, start_y
	int nx = sx;
	int ny = sy;
	while (1) {
		nx = nx + dx[direction];
		ny = ny + dy[direction];
		if (nx < 0 || ny < 0 || nx >= n || ny >= n || board[nx][ny] == 5) { // 5 블럭이거나, 칸을 벗어났거나
			if (hole != -1) {
				if (flag[hole - 6] == 1)
					flag[hole - 6] = 3;
			}
			return score * 2 + 1;
		}
		else if (board[nx][ny] == 0) {
			if (nx == x && ny == y) {
				if (hole != -1) {
					if (flag[hole - 6] == 1)
						flag[hole - 6] = 3;
				}
				return score;
			}
			continue;
		}
		// 0이 아니면 빠져나옴
		else if (board[nx][ny] == 1) {
			if (direction == 1 || direction == 0)
				direction = (direction + 2) % 4;
			else {
				if (hole != -1) {
					if (flag[hole - 6] == 1)
						flag[hole - 6] = 3;
				}
				return score * 2 + 1;
			}
			score++;
		}
		else if (board[nx][ny] == 2) {
			if (direction == 2 || direction == 0) {
				if (hole != -1) {
					if (flag[hole - 6] == 1)
						flag[hole - 6] = 3;
				}
				return score * 2 + 1;
			}
			direction = (direction + 3) % 4;
			score++;
		}
		else if (board[nx][ny] == 3) {
			if (direction == 2 || direction == 3)
				direction = (direction + 2) % 4;
			else {
				if (hole != -1) {
					if (flag[hole - 6] == 1)
						flag[hole - 6] = 3;
				}
				return score * 2 + 1;
			}
			score++;
		}
		else if (board[nx][ny] == 4) {
			if (direction == 1 || direction == 3) {
				if (hole != -1) {
					if (flag[hole - 6] == 1)
						flag[hole - 6] = 3;
				}
				return score * 2 + 1;
			}
			direction = (direction + 1) % 4;
			score++;
		}
		else if (board[nx][ny] == -1 || (nx == x && ny == y)) { //블랙홀 or 처음자리
			if (hole != -1) {
				if (flag[hole - 6] == 1)
					flag[hole - 6] = 3;
			}
			return score;
		}
		else { //웜홀
			int a = board[nx][ny];
			if (hole != -1) { //이미 홀 타고 온 경우임
				//if (flag[a - 6] == 1) { // 같은hole로 다시 빠져나가는 경우
				//	//flag[a - 6] = 2;
				//	holedirection = direction;
				//	return score;
				//}
				if (hole == a) { // 같은 웜홀로 다시 빠져나가는 경우
					flag[a - 6] = 0; //초기화
					holedirection = direction;
					return score;
				}
				else { // 또 다른 hole 들어가는 경우
					flag[a - 6] = 1; // 그 웜홀엔 처음 들어감
					if (nx == pairs[a - 6][0].first && ny == pairs[a - 6][0].second)
						score = go(direction, pairs[a - 6][1].first, pairs[a - 6][1].second, score, a);
					else
						score = go(direction, pairs[a - 6][0].first, pairs[a - 6][0].second, score, a);
					if (flag[a - 6] == 3) {
						flag[hole - 6] = 3;
						return score;
					}
					direction = holedirection;
				}
			}
			else {
				flag[a - 6] = 1; // 웜홀에 처음 들어감
				//prevhole = a;
				if (nx == pairs[a - 6][0].first && ny == pairs[a - 6][0].second)
					score = go(direction, pairs[a - 6][1].first, pairs[a - 6][1].second, score, a);
				else
					score = go(direction, pairs[a - 6][0].first, pairs[a - 6][0].second, score, a);
				direction = holedirection;

				if (flag[a - 6] == 3) { // 웜홀쪽에서 완전히 끝남
					return score;
				}
			}
		}
	}
}

int main() {
	t = 0; n = 0;
	cin >> t;
	int count = t;
	while (t--) {
		vector<pair<int, int>> pair6;
		vector<pair<int, int>> pair7;
		vector<pair<int, int>> pair8;
		vector<pair<int, int>> pair9;
		vector<pair<int, int>> pair10;
		pairs.push_back(pair6);
		pairs.push_back(pair7);
		pairs.push_back(pair8);
		pairs.push_back(pair9);
		pairs.push_back(pair10);

		cin >> n;
		int a;
		//보드 초기화
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++)
				board[i][j] = 5;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a;
				if (a >= 6)
					pairs[a - 6].push_back({ i, j });
				board[i][j] = a;
			}
		}
		int direction[4] = { 0, 1, 2, 3 }; //동 서 남 북
		int max = 0;
		int score = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == 0) {
					for (int k = 0; k < 4; k++) {
						flag[0] = 0; flag[1] = 0; flag[2] = 0; flag[3] = 0; flag[4] = 0; flag[5] = 0;
						x = i; y = j;
						score = go(direction[k], i, j, 0, -1); //0 4 2 에서 error
						if (max < score)
							max = score;
					}
				}
			}
		}
		cout << "#" << count - t << " " << max << "\n";
		pairs.clear();
	}
	return 0;
}
