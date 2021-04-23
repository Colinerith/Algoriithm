/*
[입력]
입력의 맨 첫 줄에는 총 테스트 케이스의 개수 T 가 주어지고,
그 다음 줄부터 T 개의 테스트 케이스가 주어진다.
각 테스트 케이스의 첫 번째 줄에는 지도의 한 변의 크기인 N 과 경사로의 길이 X 가 주어진다.
다음 N 개의 줄에는 N * N 크기의 지형 정보가 주어진다.

[출력]
테스트 케이스 개수만큼 T 개의 줄에 각각의 테스트 케이스에 대한 답을 출력한다.
각 줄은 "#t" 로 시작하고 공백을 하나 둔 다음 정답을 출력한다. (t는 1 부터 시작하는 테스트 케이스의 번호이다. )
정답은 활주로를 건설할 수 있는 경우의 수이다.
*/
#include<iostream>
using namespace std;

int d[20][20];

int main(int argc, char** argv) {
	int test_case;
	int T, n, x;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n >> x;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> d[i][j];
			}
		}
		int sum = 0;
		int prev;
		//		int cur;
		int count;
		int flag; //0:평지, 1:낮아졌었음, 2:높아졌었음
		int i, j;
		// 가로
		for (int i = 0; i < n; i++) {
			prev = d[i][0];
			count = 1;
			flag = 0;
			for (j = 1; j < n; j++) {
				if (d[i][j] == prev) { //전과 같은높이
					count++;
					if (j == n - 1 && flag == 1 && count < x)
						break;
				}
				else if (d[i][j] == prev - 1) { //한칸 낮아짐
					if (j == n - 1) //x는 2 이상이라 마지막에 한칸 낮아진건 실패임.
						break;

					//flag=0이나 2일때는 괜찮음.
					if ((flag == 1) && (count < x))// 아까 낮아졌음
						break;

					flag = 1;
					count = 1;
				}
				else if (d[i][j] == prev + 1) { // 한칸 높아짐
					if (((flag == 0) && (count < x)) || ((flag == 1) && (count < x * 2)) || ((flag == 2) && (count < x)))
						break;
					flag = 2;
					count = 1;
				}
				else // 두칸이상 높아지거나 낮아짐
					break;
				prev = d[i][j];
			}
			if (j == n)
				sum++;
		}
		// 세로
		for (int j = 0; j < n; j++) {
			prev = d[0][j];
			count = 1;
			flag = 0;
			for (i = 1; i < n; i++) {
				if (d[i][j] == prev) { //전과 같은높이
					count++;
					if (i == n - 1 && flag == 1 && count < x)
						break;
				}
				else if (d[i][j] == prev - 1) { //한칸 낮아짐
					if (i == n - 1) //x는 2 이상이라 마지막에 한칸 낮아진건 실패임.
						break;

					//flag=0이나 2일때는 괜찮음.
					if ((flag == 1) && (count < x))// 아까 낮아졌음
						break;

					flag = 1;
					count = 1;
				}
				else if (d[i][j] == prev + 1) { // 한칸 높아짐
					if (((flag == 0) && (count < x)) || ((flag == 1) && (count < x * 2)) || ((flag == 2) && (count < x)))
						break;
					flag = 2;
					count = 1;
				}
				else // 두칸이상 높아지거나 낮아짐
					break;
				prev = d[i][j];
			}
			if (i == n)
				sum++;
		}
		//cout << sum;

		cout << "#" << test_case << " " << sum <<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
