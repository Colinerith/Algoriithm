/* 
// 구간마다 각각의 길이를 구해서 누적 길이를 sizeArr에 저장함.
// 각 구간의 시작점을 광고시간의 시작점으로 설정하고
// 광고 넣을 시간 (시작+l) 의 끝을 각 구간들의 끝과 비교해서
// 'end'가 들어갈 구간을 구한뒤 조건에 맞게 그 앞 구간들의 길이합을 반환.
*/
#include<iostream>
using namespace std;

int T, test_case, l, n;
int s[100000];
int e[100000];
int sizeArr[100000]; // 누적 크기

int binarySearch(int a, int b, int end) { // end의 전 e[idx]인 idx를 반환
	int mid;
	while (a < b) {
		mid = (a + b) / 2;
		if (e[mid] == end)
			return mid;
		else if (end < e[mid])
			b = mid;
		else if (end > e[mid])
			a = mid + 1;
	}
	return (a>b? a:b);
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);

	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> l;
		cin >> n;
		cin >> s[0] >> e[0];
		sizeArr[0] = e[0] - s[0];
		for (int i = 1; i < n; i++) {
			cin >> s[i] >> e[i];
			sizeArr[i] = sizeArr[i-1] + (e[i] - s[i]);
		}

		int start, end, len;
		int maxLen = 0;

		for (int i = 0; i < n; i++) {
			if (i == 37239) {
				int a = 2;
			}
			start = s[i];
			end = s[i] + l;
			len = 0;
			if (end <= e[i]) {
				len = end - s[i];
			}
			else {
				len = e[i] - s[i];
				if (i != n - 1 && s[i + 1] < end) {
					int idx = binarySearch(i + 1, n, end);
					//len += gap[idx];
					if (idx == n || s[idx] >= end) {
						//idx-1을 전부 포함
						len += sizeArr[idx - 1] - sizeArr[i];
					}
					else {
						// idx를 일부 포함 (s[idx] < end)
						len += sizeArr[idx - 1] - sizeArr[i] + (end - s[idx]);
					}
				}
			}
			if (len > maxLen) {
				maxLen = len;
				if (maxLen == l) // 이미 최대 길이 달성하면 뒤에 볼 필요 없음
					break;
			}
		}
		printf("#%d %d\n", test_case, maxLen);
	}
	return 0;
}
