#include<iostream>
#include<algorithm>

using namespace std;

int main(int argc, char** argv) {
	int test_case;
	int T;
	int cnt;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int N;
		cin >> N;
		int n = N;
		
		cnt = 1;
		int value = 0;
		int c, temp;

		while (value != 1023) { // 11 1111 1111이 되면 종료
			temp = n;
			while(temp != 0){
				c = temp % 10;
				temp /= 10;
				value |= (1 << c);
			}
			cnt++;
			n = cnt * N;
		}
		cout << "#" << test_case << " " << (cnt - 1) * N << "\n";
	}
	return 0;
}
