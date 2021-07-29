#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int T, test_case, n, p;
int days[200001];
int gap[200001]; // 각 날자 사이의 빈 공간(기간)을 누적으로 저장해둠.
/* p가 해당 인덱스부터 시작하는 날짜의 gap보다 작아지기 직전의 idx를 구해서
   전체 기간에서 적절히 gap을 빼고 p를 더하는 방식. */

int binarySearch(int i, int a, int b, int p) { //gap사이즈가 p 이하인 최대 idx 반환
	int mid;
	while (a <= b) {
		mid = (a + b) / 2;
		//if ((gap[mid] - gap[i]) == p) // 같으면 작아질 때까지 키워야지.
		//	return mid;
		if (p < (gap[mid]-gap[i]))
			b = mid - 1;
		else if (p >= (gap[mid]-gap[i]))
			a = mid + 1;
	}
	return (a < b ? a : b);
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		for (int i = 0; i < 200001; i++) {
			days[i] = 0;
			gap[i] = 0;
		}
		cin >> n >> p;
		cin >> days[0];
		for (int i = 1; i < n; i++) {
			cin >> days[i];
			gap[i] = gap[i - 1] + (days[i] - days[i - 1] - 1); // 누적
		}

		int maxLen = 0;
		for (int i = 0; i < n; i++) {
			//if(gap[])
			int len = 0;

			int idx = binarySearch(i, i, n - 1, p);
			if (gap[idx] == p) {
				len = days[idx] - days[i] + 1;
			}
			else {
				len = (days[idx] - days[i] + 1) + (p - (gap[idx] - gap[i]));
			}
			if (len > maxLen) {
				maxLen = len;
			}
		}

		printf("#%d %d\n", test_case, maxLen);
	}
	return 0;
}
