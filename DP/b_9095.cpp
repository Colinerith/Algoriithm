#include<iostream>
using namespace std;

int d[11];

int main() {
	ios::sync_with_stdio(false);
	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 2; i <= 10; i++) {
			d[i] = 0;
		}
		d[1] = 1; // 1 = 1
		d[2] = 2; // 2 = 1+1 = 2
		d[3] = 4; //3 = 1+1+1 = 1+2 = 2+1 = 3

		for (int i = 4; i <= n; i++) {
			d[i] = d[i - 1] + d[i - 2] + d[i - 3];
		}
		cout << d[n]<<"\n";
	}
}
