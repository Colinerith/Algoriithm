#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int T, test_case, n, a, minLen, maxCore, coreCnt;
int **map;
pair<int, int> core[12];

void dfs(int idx, int len, int coreNum, int** map) {
	if (idx == coreCnt) {
		if (coreNum > maxCore) {
			minLen = len;
			maxCore = coreNum;
		}
		else if (coreNum == maxCore) {
			if (len < minLen) {
				minLen = len;
				maxCore = coreNum;
			}
		}
		return;
	}

	if (core[idx].first == 0 || core[idx].first == n - 1 ||
		core[idx].second == 0 || core[idx].second == n - 1) { // 모서리
		dfs(idx + 1, len, coreNum + 1, map);
	}
	else {
		int **tempMap = (int**)malloc(sizeof(int*) * n); //int* 사이즈 3개 메모리 할당
		for (int i = 0; i < n; i++)
			tempMap[i] = (int*)malloc(sizeof(int) * n); //int 사이즈 2개 메모리 할당

		// 위
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tempMap[i][j] = map[i][j];
		}
		int i = 0;
		for (i; i < core[idx].first; i++) {
			if (tempMap[i][core[idx].second] == 1) {
				break;
			}
			tempMap[i][core[idx].second] = 1;
		}
		if (i == core[idx].first) { // 위로 연결 가능
			dfs(idx + 1, len + core[idx].first, coreNum + 1, tempMap);
		}

		//아래
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tempMap[i][j] = map[i][j];
		}
		i = core[idx].first + 1;
		for (i; i < n; i++) {
			if (tempMap[i][core[idx].second] == 1) {
				break;
			}
			tempMap[i][core[idx].second] = 1;
		}
		if (i == n) { // 연결 가능
			dfs(idx + 1, len + (n - core[idx].first - 1), coreNum + 1, tempMap);
		}

		// 왼쪽
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tempMap[i][j] = map[i][j];
		}
		i = 0;
		for (i; i < core[idx].second; i++) {
			if (tempMap[core[idx].first][i] == 1) {
				break;
			}
			tempMap[core[idx].first][i] = 1;
		}
		if (i == core[idx].second) { // 위로 연결 가능
			dfs(idx + 1, len + core[idx].second, coreNum + 1, tempMap);
		}

		// 오른쪽
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tempMap[i][j] = map[i][j];
		}
		i = core[idx].second + 1;
		for (i; i < n; i++) {
			if (tempMap[core[idx].first][i] == 1) {
				break;
			}
			tempMap[core[idx].first][i] = 1;
		}
		if (i == n) { // 연결 가능
			dfs(idx + 1, len + (n - core[idx].second - 1), coreNum + 1, tempMap);
		}

		// 연결하지 않는 경우
		if (maxCore < coreCnt)
			dfs(idx + 1, len, coreNum, map);
	}
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n;
		int coreIdx = 0;
		map = (int**)malloc(sizeof(int*) * n);
		for (int i = 0; i < n; i++)
			map[i] = (int*)malloc(sizeof(int) * n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) { //코어만 따로 저장
					core[coreIdx++] = { i, j };
				}
			}
		}
		coreCnt = coreIdx;
		minLen = 10000000;
		maxCore = -1;

		dfs(0, 0, 0, map);

		printf("#%d %d\n", test_case, minLen);
	}
	return 0;
}
