// 미로_오후 2번
#include<iostream>
#include<vector>
using namespace std;

int n, m, a;
int map[50][50];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	vector<int> balls;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int result = 0;
	int maxSize = n * n - 1; // balls 에 들어갈 공 최대 개수

	pair<int, int> cur = { n / 2,  n / 2 };
	//int curWidth = 1;
	int minR = n / 2 - 1; int maxR = n / 2 + 1;
	int minC = n / 2 - 1; int maxC = n / 2 + 1;
	bool flag = true;
	while (flag) {
		while (flag) { // 왼쪽으로 이동
			cur.second--;
			if (map[cur.first][cur.second] == 0) {
				flag = false;
				break;
			}
			balls.push_back(map[cur.first][cur.second]);
			if (cur.second == minC) break;
		}
		while (flag) { // 아래로 이동
			cur.first++;
			if (map[cur.first][cur.second] == 0) {
				flag = false;
				break;
			}
			balls.push_back(map[cur.first][cur.second]);
			if (cur.first == maxR) break;
		}
		while(flag) { // 오른쪽으로 이동
			cur.second++;
			if (map[cur.first][cur.second] == 0) {
				flag = false;
				break;
			}
			balls.push_back(map[cur.first][cur.second]);
			if (cur.second == maxC) break;
		}
		while (flag) { // 위로 이동
			cur.first--;
			if (map[cur.first][cur.second] == 0) {
				flag = false;
				break;
			}
			balls.push_back(map[cur.first][cur.second]);
			if (cur.first == minC) break;
		}
		minR--; maxR++; minC--; maxC++;
	}

	
	// 구슬 파괴 & 이동
	int d, s;
	for (int i = 0; i < m; i++) {
		cin >> d >> s;
		int idx = 0;
		int toSum;
		switch (d) {
		case 1: idx = 7; toSum = 7; break;
		case 2: idx = 3; toSum = 3; break;
		case 3: idx = 1; toSum = 1; break;
		case 4: idx = 5; toSum = 5; break;
		}

		//삭제는 인덱스 큰 순서로
		int cnt = 1;
		while (cnt < s && idx + toSum - 1 < balls.size()) {
			toSum += 8;
			idx += toSum;
			cnt++;
		}
		while (cnt--) {
			//result += balls[idx - 1];
			balls.erase(balls.begin() + idx - 1);
			idx -= toSum;
			toSum -= 8;
		}

		while(!balls.empty()) {
			// 4개 이상 연속 구슬 삭제 (폭발)
			int prev = 0;
			int cur = 1;
			int cnt = 1;
			vector<pair<int, int>> toDel;
			int bSize = balls.size();
			while (true) {
				// 마지막 원소
				if (cur == bSize - 1) {
					if(cnt >= 4)
						toDel.push_back({ prev, cur + 1 });
					break;
				}

				if (balls[prev] == balls[cur]) {
					cnt++;
				}
				else {
					if (cnt >= 4) {
						// prev부터 이전까지 삭제
						// 인덱스가 밀리니까 저장했다가 나중에 뒤부터 삭제.
						//balls.erase(balls.begin() + prev, balls.begin() + cur); 
						toDel.push_back({ prev, cur });
					}
					prev = cur;
					cnt = 1;
				}
				cur++;
			}
			// 삭제
			if (toDel.empty()) break; // 더이상 폭발할 게 없으면 종료
			for (int k = toDel.size() - 1; k >= 0; k--) {
				// result += (삭제한 구슬의 숫자 * 개수)
				result += balls[toDel[k].first] * (toDel[k].second - toDel[k].first);
				balls.erase(balls.begin() + toDel[k].first, balls.begin() + toDel[k].second);
			}
		}

		if (!balls.empty()) {
			//변화
			int vSize = balls.size();
			int prevNum = balls[0];
			balls.erase(balls.begin() + 0);
			cnt = 1;
			while (vSize--) {
				//마지막이면
				if (vSize == 0) {
					balls.push_back(cnt);
					balls.push_back(prevNum);
					break;
				}

				if (prevNum == balls[0])
					cnt++;
				else {
					balls.push_back(cnt);
					balls.push_back(prevNum);
					prevNum = balls[0];
					cnt = 1;
				}
				balls.erase(balls.begin() + 0);
			}
			// 범위 넘어가는 것들 삭제
			if (balls.size() > maxSize) {
				int c = balls.size() - maxSize;
				balls.erase(balls.begin() + maxSize, balls.begin() + (maxSize + c));
			}
		}
	}

	cout << result;
}
