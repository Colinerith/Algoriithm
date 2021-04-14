#include<iostream>
using namespace std;

int n, p, temp;
int d[1001];
int pack[1001];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p;
		pack[i] = p;
	}
	d[1] = pack[1];
	if (d[1] * 2 > pack[2])
		d[2] = d[1] * 2;
	else d[2] = pack[2];

	for (int i = 3; i <= n; i++) {
		d[i] = d[1] + d[i - 1];

		for (int j = 2; j <= i / 2; j++) {
			temp = d[j] + d[i - j];
			if (temp > d[i])
				d[i] = temp;
		}

		if (pack[i] > d[i])
			d[i] = pack[i];
	}
	cout << d[n];
}
