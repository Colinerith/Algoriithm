#include<iostream>
using namespace std;

long long int d[1001];
int a[1001];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	d[1] = a[1];
	for (int i = 2; i <= n; i++) {
		d[i] = a[i]; //최소일 때
		for (int j = 1; j < i; j++) {
			if (a[i] > a[j] && d[j] + a[i] > d[i])
				d[i] = a[i] + d[j];
		}
	}
	int max = 0;
	for (int i = 1; i <= n; i++) {
		if (d[i] > max)
			max = d[i];
	}
	cout << max;
}
