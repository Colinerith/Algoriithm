#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
typedef unsigned long long ll;
using namespace std;

int T, test_case, h, w, n, m;
char painting[2000][2000];
char dream[2000][2000];
ll horizontalHash[2000][2000];
ll resultHash[2000][2000];

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> h >> w >> n >> m;
		for (int i = 0; i < h; i++)
			cin >> dream[i];
		
		ll hash2 = 0;
		int p2 = 1;
		for (int i = 0; i < h; i++) {
			int p1 = 1;
			ll hash = 5381;
			for (int j = 0; j < w; j++) {
				hash = hash + dream[i][j] * p1;
				p1 *= 33;
			}
			hash2 = hash2 + hash * p2;
			p2 *= 33;
		}

		for (int i = 0; i < n; i++)
			cin >> painting[i];

		for (int i = 0; i < n; i++) {
			int p = 1;
			ll hash = 5381;
			int k = 0;
			for (; k < w - 1; k++) {
				hash = hash + painting[i][k] * p;
				p *= 33;
			}
			hash = hash + painting[i][k] * p;
			horizontalHash[i][0] = hash;

			for (int j = 1; j < m - w + 1; j++) { // 빠르게
				hash = 5381 + (hash - painting[i][j - 1] - 5381) / 33 + painting[i][j + w - 1] * p;
				//hash = (hash - painting[i][j - 1] * p) * 33 + painting[i][j + w - 1];
				horizontalHash[i][j] = hash;
			}
		}
		for (int i = 0; i < m - w + 1; i++) {
			int p = 1, k = 0;
			ll hash = 0;
			for (; k < h - 1; k++) {
				hash = hash + horizontalHash[k][i] * p;
				p *= 33;
			}
			hash = hash + horizontalHash[k][i] * p;
			resultHash[0][i] = hash;

			for (int j = 1; j < n - h + 1; j++) { // 빠르게
				hash = (hash - horizontalHash[j - 1][i]) / 33 + horizontalHash[j + h - 1][i] * p;
				//hash = (hash - horizontalHash[j - 1][i] * p) * 33 + horizontalHash[j + h - 1][i];
				resultHash[j][i] = hash;
			}
		}

		int cnt = 0;
		for (int i = 0; i < n - h + 1; i++) {
			for (int j = 0; j < m - w + 1; j++) {
				if (resultHash[i][j] == hash2)
					cnt++;
			}
		}
		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}
