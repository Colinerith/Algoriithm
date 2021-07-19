#include<iostream>
using namespace std;

int main(int argc, char** argv){
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case){
		int N, M;
		cin >> N >> M;
		bool flag = true;
		int m = M;

		for (int i = 0; i < N; i++) {
			if (!(m & 1)) {
				flag = false;
				break;
			}
			m >>= 1;
		}
		cout << "#" << test_case << (flag ? " ON" : " OFF") << " " << "\n";
	}
	return 0;
}
