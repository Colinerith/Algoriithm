/*
첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)

둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다.
d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을,
3인 경우에는 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로,
각 줄은 서쪽부터 동쪽 순서대로 주어진다.
빈 칸은 0, 벽은 1로 주어진다. 지도의 첫 행, 마지막 행, 첫 열,
마지막 열에 있는 모든 칸은 벽이다.

로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

출력
로봇 청소기가 청소하는 칸의 개수를 출력한다.
*/
//더 효율적으로 하면 좋겠다.. ex) https://www.acmicpc.net/source/8396731


#include<iostream>
using namespace std;

int n, m, r, c, d; //d가 0:북, 1:동, 2:남, 3:서
int space[51][51]; //벽:1, 청소전 빈칸:0, 청소후 빈칸:2

int main() {
	cin >> n >> m;
	cin >> r >> c >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> space[i][j];
		}
	}
	space[r][c] = 2; //현재 위치 청소
	int search;
	int clean = 1;
	while (1) {
		if (d == 0) search = 3;
		else search = d - 1; // 탐색할 방향 (왼쪽)
		if (d == 1) { //현재:동쪽, 왼쪽:북쪽
			//네 칸이 다 청소됐거나 벽이면 한칸 후진 (c)
			if (space[r - 1][c] != 0 && space[r + 1][c] != 0 && space[r][c - 1] != 0 && space[r][c + 1] != 0) {
				if (space[r][c - 1] == 1) { //후진이 벽이면
					break;
				}
				c = c - 1; //되면 후진
				continue;
			}
			else if (space[r - 1][c] == 0) { //왼쪽이 비었으면 회전후 한칸전진, 청소 (a)
				d = search; //회전
				r = r - 1; //한칸전진
				space[r][c] = 2; //청소
				clean++;
				continue;
			}
			else {
				d = search;
				continue;
			}
		}
		else if (d== 0) { //현재:북쪽, 왼쪽:서쪽
			//네 칸이 다 청소됐거나 벽이면 한칸 후진 (c)
			if (space[r - 1][c] != 0 && space[r + 1][c] != 0 && space[r][c - 1] != 0 && space[r][c + 1] != 0) {
				if (space[r + 1][c] == 1){ //후진이 벽이면{
					break;
				}
				r = r + 1; //아래로 내려감
				continue;
			}
			else if (space[r][c-1] == 0) { //왼쪽이 비었으면 회전후 한칸전진, 청소 (a)
				d = search; //회전
				c = c-1; //한칸전진
				space[r][c] = 2; //청소
				clean++;
				continue;
			}
			else {
				d = search;
				continue;
			}
		}
		if (d==2) { //현재:남, 왼쪽:동
			//네 칸이 다 청소됐거나 벽이면 한칸 후진 (c)
			if (space[r - 1][c] != 0 && space[r + 1][c] != 0 && space[r][c - 1] != 0 && space[r][c + 1] != 0) {
				if (space[r - 1][c] == 1) {
					break;
				}
				r = r - 1; //위로
				continue;
			}
			else if (space[r][c+1] == 0) { //왼쪽이 비었으면 회전후 한칸전진, 청소 (a)
				d = search; //회전
				c = c + 1; //한칸전진
				space[r][c] = 2; //청소
				clean++;
				continue;
			}
			else {
				d = search;
				continue;
			}
		}
		if (d==3) { //서, 남
			//네 칸이 다 청소됐거나 벽이면 한칸 후진 (c)
			if (space[r - 1][c] != 0 && space[r + 1][c] != 0 && space[r][c - 1] != 0 && space[r][c + 1] != 0) {
				if (space[r][c + 1] == 1) {
					break;
				}
				c = c + 1; // 오른쪽
				continue;
			}
			else if (space[r + 1][c] == 0) { //왼쪽이 비었으면 회전후 한칸전진, 청소 (a)
				d = search; //회전
				r = r + 1; //한칸전진
				space[r][c] = 2; //청소
				clean++;
				continue;
			}
			else {
				d = search;
				continue;
			}
		}
	}
	cout << clean;
}
