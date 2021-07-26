#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int T, test_case;
int d_maxPiece[3101][2];
int d[3001][101][4];

int A[3001];
int B[101];

int max(int a, int b) {
	return a > b ? a : b;
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int n, m;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> A[i];
		cin >> m;
		for (int i = 0; i < m; i++) cin >> B[i];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {

			}
		}
	}
	return 0;
}
