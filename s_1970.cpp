#include<iostream>
using namespace std;
int money[8] = { 50000, 10000, 5000, 1000, 500, 100, 50, 10 };

int main(int argc, char** argv){
	int test_case;
	int T, n;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case){
		cin >> n;
		int cnt = 0;

		printf("#%d\n", test_case);
		for (int i = 0; i < 8; i++) {
			if (n >= money[i]) {
				cnt = n / money[i];
				n -= cnt * money[i];
			}
			printf("%d ", cnt);
			cnt = 0;
		}
		printf("\n");
	}
	return 0;
}
