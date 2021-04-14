#include<iostream>
using namespace std;

int d[1001][10];

int main() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 10;
		return 0;
	}
	for (int i = 0; i <= 9; i++) d[1][i] = 1;

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = j; k <= 9; k++)
				d[i][j] += d[i - 1][k] % 10007;
		}
		//d[i][9] = d[i - 1][9] % 10007; //계속 9만 뒤에 붙일 수밖에 없음.
	}
	int sum = 0;
	for (int i = 0; i <= 9; i++) sum = (sum + d[n][i]) % 10007;
	cout << sum;
}
