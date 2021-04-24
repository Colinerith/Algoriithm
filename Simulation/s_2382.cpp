/*
미생물 격리
첫 줄에는 총 테스트 케이스의 개수 T가 주어진다.
그 다음 줄부터 T개의 테스트 케이스가 차례대로 주어진다.
각 테스트 케이스의 첫째 줄에는 구역의 한 변에 있는 셀의 개수 N, 격리 시간 M,
미생물 군집의 개수 K가 순서대로 주어지며, 다음 K줄에 걸쳐서 미생물 군집 K개의 정보가 주어진다.
미생물 군집의 정보는 세로 위치, 가로 위치, 미생물 수, 이동 방향 순으로 4개의 정수가 주어진다.


[출력]
테스트 케이스의 개수 만큼 T개의 줄에 각 테스트 케이스에 대한 답을 출력한다.
각 줄은 “#x”로 시작하고, 공백을 하나 둔 후 정답을 출력한다.
(x는 테스트 케이스의 번호이며, 1번부터 시작한다.)
출력해야 할 정답은 M시간 후 남아 있는 미생물 수의 총 합이다.

*/
#include<iostream>
using namespace std;

int map[100][100][3]; // index, time, max
int micros[1000][5]; //마지막은 몇시간째인지
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int main(int argc, char** argv)
{
	int test_case;
	int T, n, m, k;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n >> m >> k;

		// 맵 초기화 --> 초기화는 완전히 하기!!
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				map[i][j][0] = -1;
				map[i][j][1] = 0;
				map[i][j][2] = 0;
			}
		}
		//for (int i = 1; i < n - 1; i++) {
		//	for (int j = 1; j < n - 1; j++) {
		//		map[i][j] = { -1, 0 };
		//	}
		//}

		//// 약품
		//for (int j = 0; j < n - 1; j++)
		//	map[0][j] = { -1, 0 };
		//for (int j = 0; j < n - 1; j++)
		//	map[n - 1][j] = { -1, 0 };
		//for (int i = 0; i < n - 1; i++)
		//	map[i][0] = { -1, 0 };
		//for (int i = 0; i < n - 1; i++)
		//	map[i][n - 1] = { -1, 0 };

		int x, y, num, dir;
		for (int i = 0; i < k; i++) { //미생물 군집 입력
			cin >> x >> y >> num >> dir;
			micros[i][0] = x; micros[i][1] = y;
			micros[i][2] = num; micros[i][3] = dir;
			map[x][y][0] = i; //인덱스를 저장하는거임
		}
		int nx, ny;
		for (int q = 1; q <= m; q++) {
			for (int i = 0; i < k; i++) {
				if (micros[i][2] != 0) { //남아있는 미생물이 없으면 신경쓰지 않음
					nx = micros[i][0] + dx[micros[i][3] - 1];
					ny = micros[i][1] + dy[micros[i][3] - 1];
					micros[i][0] = nx;
					micros[i][1] = ny;

					if (nx == 0 || nx == n - 1 || ny == 0 || ny == n - 1) { //다음칸이 약품셀이면
						micros[i][2] = micros[i][2] / 2; //수가 반 줄어듦
						if (micros[i][3] == 1 || micros[i][3] == 3) //방향 반대로
							micros[i][3] = micros[i][3] + 1;
						else
							micros[i][3] = micros[i][3] - 1;
						map[nx][ny][0] = i;
						map[nx][ny][1] = q;
						//약품셀에서 합쳐지는 경우는 없다.
					}
					else if (map[nx][ny][0] != -1 && map[nx][ny][1] == q) { // 합쳐져야하면
						//문제점: 하나씩 합치면 마지막게 제일 커도 못들어갈수도 있다..
						// 그 자리가 -1이 아니고(누가 있고), 놓인 시간이 q였으면 (현재와 같으면)
						int otherIdx = map[nx][ny][0];
						if (map[nx][ny][2] > micros[i][2]) { //그전 max가 나보다 크면 내가 죽음
							micros[otherIdx][2] += micros[i][2]; //쟤한테 내 수 더하고
							micros[i][2] = 0; //난 0됨
						}
						else { //아니면 내가 그 자리를 차지함
							map[nx][ny][2] = micros[i][2]; //max 업데이트하고
							micros[i][2] += micros[otherIdx][2]; // 원래 sum을 나한테 더하고
							micros[otherIdx][2] = 0; //쟤는 죽고
							map[nx][ny][0] = i; //맵에 내 정보를 저장
						}
					}
					else {//그냥 이동만 하면 되는 경우
						map[nx][ny][0] = i;
						map[nx][ny][1] = q;
						map[nx][ny][2] = micros[i][2];
					}
				}
			}
		}
		int sum = 0;
		for (int i = 0; i < k; i++) {
			if (micros[i][2] != 0) {
				sum += micros[i][2];
			}
		}
		cout << "#" << test_case << " " << sum << "\n";
	}
	return 0;
}
