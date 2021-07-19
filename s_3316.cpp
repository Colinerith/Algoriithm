#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int d[10000][16];

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin >> T;

	char str[10000];
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%s", str);

		for (int i = 0; i < 10000; i++) {
			for (int j = 1; j < 16; j++) 
				d[i][j] = 0;
		}

		int day = 0; // 날짜를 인덱스로

		//첫날
		if (str[0] == 'A') {
			int a = 0;
			for (int i = 0; i < 16; i++) {
				if (a & 8)
					d[day][i] = 1;
				a++;
			}
		}
		else {
			int a = 0;
			for (int i = 0; i < 16; i++) {
				if ((a & 8) && (a & (1 << (3 - (str[0] - 'A')))))
					d[day][i] = 1;
				a++;
			}
		}

		while (str[day + 1] != '\0') {
			for (int i = 1; i <= 15; i++) {
				for (int j = 1; j <= 15; j++) {
					if(d[day][i] > 0)
						if ((i & j) && (j & (1 << (3 - (str[day + 1] - 'A')))))
							d[day + 1][j] = (d[day + 1][j] + d[day][i]) % 1000000007;
				}
			}
			day++;
		}

		int sum = 0;
		for (int i = 0; i < 16; i++)
			sum = (sum + d[day][i]) % 1000000007;
		
		cout << "#" << test_case << " " << sum % 1000000007 << "\n";
	}
	return 0;
}
