// cnt 배열을 두는 것. 세번 겹치면 3초 걸림
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
pair<int, int> students[400];
int visited[200];

int main(int argc, char** argv) {
	int test_case;
	int T, n, a, b;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		for (int i = 0; i < 200; i++)
			visited[i] = 0;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			if (!(a & 1)) a--; // 짝수면 1 감소
			if (!(b & 1)) b--;
			if (a > b) students[i] = { b / 2, a / 2 };
			else students[i] = { a / 2, b / 2 };
			// 홀수 방과 짝수 방이 마주보고 있으므로,
			// 1->5 와 2->6을 0->2로 같게 처리하는 것.
		}
		for (int i = 0; i < n; i++) {
			for (int j = students[i].first; j <= students[i].second; j++) {
				visited[j]++;
			}
		}
		int max = 0;
		for (int i = 0; i < 200; i++) {
			if (visited[i] > max)
				max = visited[i];
		}
		printf("#%d %d\n", test_case, max);
	}
	return 0;
}
