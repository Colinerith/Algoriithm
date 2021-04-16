/*
첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 20),
주사위를 놓은 곳의 좌표 x y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1),
그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.

둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로,
각 줄은 서쪽부터 동쪽 순서대로 주어진다. 주사위를 놓은 칸에 쓰여 있는 수는 항상 0이다.
지도의 각 칸에 쓰여 있는 수는 10을 넘지 않는 자연수 또는 0이다.

마지막 줄에는 이동하는 명령이 순서대로 주어진다.
동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.

출력
이동할 때마다 주사위의 윗 면에 쓰여 있는 수를 출력한다.
만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.
*/
#include<iostream>
using namespace std;

int dice[7];
int board[20][20];

int main() {
	int n, m, x, y, k; //n-세로크기, m-가로크기
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cin >> board[i][j];
	}
	//int cur = 1; //지금 주사위 밑면
	//1자리가 항상 밑면!
	int a;
	int temp1, temp2, temp3, temp4, temp5, temp6;

	for (int i = 0; i < k; i++) {
		cin >> a;
		if (a == 1) { //동
			if (y == m - 1) //범위끝이면
				continue;
			y++;
			//주사위 구르기
			temp1 = dice[3];
			//temp2 = dice[2];
			temp3 = dice[6];
			temp4 = dice[1];
			//temp5 = dice[5];
			temp6 = dice[4];

			dice[1] = temp1;
			dice[3] = temp3;
			dice[4] = temp4;
			dice[6] = temp6;

			if (board[x][y] == 0) { //칸의 수가 0이면
				board[x][y] = dice[1]; //주사위수 복사
			}
			else {
				dice[1] = board[x][y]; //주사위바닥에 칸의 수 복사
				board[x][y] = 0; //0이 됨
			}
			//주사위 상단의 값 출력
			cout << dice[6] << "\n";
		}
		else if (a == 2) { //서
			if (y == 0)
				continue;
			y--;
			temp1 = dice[4];
			//temp2 = dice[2];
			temp3 = dice[1];
			temp4 = dice[6];
			//temp5 = dice[5];
			temp6 = dice[3];

			dice[1] = temp1;
			dice[3] = temp3;
			dice[4] = temp4;
			dice[6] = temp6;

			if (board[x][y] == 0) { //칸의 수가 0이면
				board[x][y] = dice[1]; //주사위수 복사
			}
			else {
				dice[1] = board[x][y]; //주사위바닥에 칸의 수 복사
				board[x][y] = 0; //0이 됨
			}
			//주사위 상단의 값 출력
			cout << dice[6] << "\n";
		}
		else if (a == 3) { //북
			if (x == 0)
				continue;
			x--;
			temp1 = dice[5];
			temp2 = dice[1];
			//temp3 = dice[6];
			//temp4 = dice[1];
			temp5 = dice[6];
			temp6 = dice[2];

			dice[1] = temp1;
			dice[2] = temp2;
			dice[5] = temp5;
			dice[6] = temp6;

			if (board[x][y] == 0) { //칸의 수가 0이면
				board[x][y] = dice[1]; //주사위수 복사
			}
			else {
				dice[1] = board[x][y]; //주사위바닥에 칸의 수 복사
				board[x][y] = 0; //0이 됨
			}
			//주사위 상단의 값 출력
			cout << dice[6] << "\n";
		}
		else { //남
			if (x == n - 1)
				continue;
			x++;
			temp1 = dice[2];
			temp2 = dice[6];
			//temp3 = dice[6];
			//temp4 = dice[1];
			temp5 = dice[1];
			temp6 = dice[5];

			dice[1] = temp1;
			dice[2] = temp2;
			dice[5] = temp5;
			dice[6] = temp6;

			if (board[x][y] == 0) { //칸의 수가 0이면
				board[x][y] = dice[1]; //주사위수 복사
			}
			else {
				dice[1] = board[x][y]; //주사위바닥에 칸의 수 복사
				board[x][y] = 0; //0이 됨
			}
			//주사위 상단의 값 출력
			cout << dice[6] << "\n";
		}
	}
}
