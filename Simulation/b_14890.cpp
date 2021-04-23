#include<iostream>
using namespace std;

int d[100][100];

int main(int argc, char** argv) {
	int n, x;
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
				if (j == n - 1 && x != 1) //x는 1 이상
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
				if (i == n - 1 && x != 1) //x는 1 이상
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

	cout << sum;
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
