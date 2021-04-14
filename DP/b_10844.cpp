
#include<iostream>
using namespace std;

int d[101][10]; //길이, 마지막자리 수

int main() {
	for (int i = 1; i <= 9; i++) d[1][i] = 1;
	int n;
	cin >> n;
	if (n == 1) {
		cout << 9;
		return 0;
	}

	for (int i = 2; i <= n; i++) {
		d[i][0] = d[i - 1][1] % 1000000000;
		for (int j = 1; j <= 8; j++) {
			d[i][j] = (d[i - 1][j - 1] + d[i - 1][j + 1]) % 1000000000;
		}
		d[i][9] = d[i - 1][8] % 1000000000;
	}
	int num = 0;
	for (int i = 0; i <= 9; i++) num = (num + d[n][i]) % 1000000000;
	cout << num;

}
