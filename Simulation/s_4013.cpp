/*

*/

#include<iostream>
using namespace std;

int main(int argc, char** argv) {
	int test_case;
	int T;
	int k, c, magnum, clockwise;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int magnets[4][8];
		cin >> k;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> magnets[i][j];
			}
		}

		int sum = 0;
		int top0 = 0;
		int top1 = 0;
		int top2 = 0;
		int top3 = 0;

		while (k--) {
			cin >> magnum >> clockwise;
			int right0 = (top0 + 2) % 8;
			int left1 = (top1 + 6) % 8; int right1 = (top1 + 2) % 8;
			int left2 = (top2 + 6) % 8; int right2 = (top2 + 2) % 8;
			int left3 = (top3 + 6) % 8;
			if (magnum == 1) {
				if (magnets[0][right0] == magnets[1][left1]) //같은극이면
				{
					if (clockwise == 1)
						top0 = (top0 + 7) % 8;
					else
						top0 = (top0 + 1) % 8;
				}
				else if (magnets[1][right1] == magnets[2][left2]) { //앞 두개만 돌아가고 끝남
					if (clockwise == 1) {
						top0 = (top0 + 7) % 8;
						top1 = (top1 + 1) % 8;
					}
					else {
						top0 = (top0 + 1) % 8;
						top1 = (top1 + 7) % 8;
					}
				}
				else if (magnets[2][right2] == magnets[3][left3]) { //앞 세개만 돌아가고 끝남
					if (clockwise == 1) {
						top0 = (top0 + 7) % 8;
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
					}
					else {
						top0 = (top0 + 1) % 8;
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
					}
				}
				else {//넷다 돌아감
					if (clockwise == 1) {
						top0 = (top0 + 7) % 8;
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
						top3 = (top3 + 1) % 8;
					}
					else {
						top0 = (top0 + 1) % 8;
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
						top3 = (top3 + 7) % 8;
					}
				}
			}
			else if (magnum == 2) {
				if (magnets[0][right0] != magnets[1][left1]) //0과 1이 같지 않으면
				{
					if (clockwise == 1)
						top0 = (top0 + 1) % 8;
					else
						top0 = (top0 + 7) % 8;
				}
				if (magnets[1][right1] == magnets[2][left2]) { //2부터는 안돌아감
					if (clockwise == 1) {
						top1 = (top1 + 7) % 8;
					}
					else {
						top1 = (top1 + 1) % 8;
					}
				}
				else if (magnets[2][right2] == magnets[3][left3]) { //3은 안돌아감
					if (clockwise == 1) {
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
					}
					else {
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
					}
				}
				else {//3까지 돌아감
					if (clockwise == 1) {
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
						top3 = (top3 + 7) % 8;
					}
					else {
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
						top3 = (top3 + 1) % 8;
					}
				}
			}
			else if (magnum == 3) {
				if (magnets[2][right2] != magnets[3][left3]) //2, 3 다른극이면
				{
					if (clockwise == 1)
						top3 = (top3 + 1) % 8;
					else
						top3 = (top3 + 7) % 8;
				}
				if (magnets[1][right1] == magnets[2][left2]) { // 1은 안돌아감
					if (clockwise == 1) {
						top2 = (top2 + 7) % 8;
					}
					else {
						top2 = (top2 + 1) % 8;
					}
				}
				else if (magnets[0][right0] == magnets[1][left1]) { //2때문에 1까지만 돌아감
					if (clockwise == 1) {
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
					}
					else {
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
					}
				}
				else {
					// 2때문에 1, 0 다 돌아감
					if (clockwise == 1) {
						top0 = (top0 + 7) % 8;
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
					}
					else {
						top0 = (top0 + 1) % 8;
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
					}
				}
			}
			else if (magnum == 4) {
				if (magnets[2][right2] == magnets[3][left3]) //같은극이면
				{
					if (clockwise == 1)
						top3 = (top3 + 7) % 8;
					else
						top3 = (top3 + 1) % 8;
					//continue; //더이상 계산 안 함
				}
				else if (magnets[1][right1] == magnets[2][left2]) { //뒤 두개만 돌아가고 끝남
					if (clockwise == 1) {
						top2 = (top2 + 1) % 8;
						top3 = (top3 + 7) % 8;
					}
					else {
						top2 = (top2 + 7) % 8;
						top3 = (top3 + 1) % 8;
					}
				}
				else if (magnets[0][right0] == magnets[1][left1]) { //뒤 세 개만 돌아감
					if (clockwise == 1) {
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
						top3 = (top3 + 7) % 8;
					}
					else {
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
						top3 = (top3 + 1) % 8;
					}
				}
				else { //넷다 돌아감
					if (clockwise == 1) {
						top0 = (top0 + 1) % 8;
						top1 = (top1 + 7) % 8;
						top2 = (top2 + 1) % 8;
						top3 = (top3 + 7) % 8;
					}
					else {
						top0 = (top0 - 1) % 8;
						top1 = (top1 + 1) % 8;
						top2 = (top2 + 7) % 8;
						top3 = (top3 + 1) % 8;
					}
				}
			}
		}
		if (magnets[0][top0] == 1)
			sum += 1;
		if (magnets[1][top1] == 1)
			sum += 2;
		if (magnets[2][top2] == 1)
			sum += 4;
		if (magnets[3][top3] == 1)
			sum += 8;

		cout << "#" << test_case << " " << sum << "\n";
	}

	return 0;
}
