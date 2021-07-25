#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

int T, test_case, length;
string a, b;
int d[1001][1001];

int max(int a, int b) {
	return (a > b ? a : b);
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		length = 0;
		cin >> a >> b;
		
		for (int i = 1; i <= a.length(); i++) {
			for (int j = 1; j <= b.length(); j++) {
				d[i][j] = 0;
			}
		}

		for (int i = 1; i <= a.length(); i++) {
			for (int j = 1; j <= b.length(); j++) {
				if (a[i - 1] == b[j - 1]) {
					d[i][j] = d[i - 1][j - 1] + 1;
				}
				else
 					d[i][j] = max(d[i-1][j], d[i][j - 1]);
			}
		}

		printf("#%d %d\n",test_case, d[a.length()][b.length()]);
	}
	return 0;
}
