#include<iostream>
using namespace std;

long long int d[91][2];

int main() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 1;
		return 0;
	}
	d[1][1] = 1;
	d[1][0] = 1;
//	d[2][1] = 1;

	for (int i = 2; i <= n; i++) {
		d[i][0] = d[i - 1][0] + d[i - 1][1];
		d[i][1] = d[i - 1][0];
	}
	cout << d[n][1];
}
