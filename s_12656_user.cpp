// 롤러코스터 설계 (라이브러리 사용 가능)
//#include<queue>
//#include<iostream>
//using namespace std;
//priority_queue<int> pq;

int n;
//int x, y, d;
int dx[4][3] = { {-1, -1, -1},{-1, 0, 1 },{1, 1, 1},{1, 0, -1} };
int dy[4][3] = { {-1, 0, 1} ,{1, 1, 1},{-1, 0, 1},{-1, -1, -1} };

int dir[4][3] = { {3, 0, 1},{0, 1, 2},{1, 2, 3},{2, 3, 0} };
//int dx[4][2][3] = {
//					{ {1, 1, 1}, {-1, -1, -1} },
//					{ {1, 0, -1}, {-1, 0, 1 }} ,
//					{ {-1, -1, -1}, {1, 1, 1}},
//					{ {-1, 0, 1 }, {1, 0, -1}}
//				  };
//int dy[4][2][3] = { 
//					{ {1, 0, -1}, {-1, 0, 1} },
//					{ {-1, -1, -1}, {1, 1, 1}, } ,
//					{ {1, 0, -1}, {-1, 0, 1}},
//					{ {1, 1, 1}, {-1, -1, -1}}
//				  };

//struct Tile {
//	int prevX;
//	int prevY;
//	int dx;
//	int dy;
//};

//Tile map[10001][10001];
int map[10001][10001];
//int frontX, frontY, frontD; // 두 개 전 것을 저장
//int rearX, rearY, rearD;

void init(int N){
	n = N; // 3~5000
	//frontX = frontY = rearX = rearY = N;
	//frontD = 1; rearD = 3;
	//x = y = N;
	//d = 1; // 오른쪽
	for (int i = 0; i < 10001; i++) {
		for (int j = 0; j < 10001; j++)
			map[i][j] = -1;
	}
	//map[n][n] = 1;
}

/*
mFront 가 0인 경우 후방 방향으로 레일을 추가한다.
		  1인 경우 전방
mDirection 이 0인 경우 좌회전 레일을 추가한다.
			  1인 경우 직진
			  2인 경우 우회전
*/
void addRail(int mFront, int mDirection){
	int _dx, _dy;
	int curX, curY, curD;

	if (mFront == 0) map[n][n] = 3;
	else map[n][n] = 1;

	curX = curY = n;
	//int tempX;
	while (map[curX][curY] != -1) {
		curD = map[curX][curY];
		//tempX = curX;
		curX = curX + dx[curD][1];
		curY = curY + dy[curD][1];
	}
	map[curX][curY] = dir[curD][mDirection];

	//if (mFront == 0) {
		//map[n][n] = 3;
		//if (map[rearX + dx[3][1]][rearY + dy[3][1]] != -1) {
		//	rearX = rearX + dx[map[rearX][rearY]][1];
		//	rearY = rearY + dy[map[rearX][rearY]][1];
		//	rearD = map[rearX][rearY];
		//}
		//_dx = dx[rearD][mDirection];
		//_dy = dy[rearD][mDirection];

		//map[rearX + _dx][rearY + _dy] = dir[rearD][mDirection];
	//}
	//else {
		//map[n][n] = 1;
		//if (map[frontX + dx[1][1]][frontY + dy[1][1]] != -1) {
		//	frontX = frontX + dx[map[frontX][frontY]][1];
		//	frontY = frontY + dy[map[frontX][frontY]][1];
		//	frontD = map[frontX][frontY];
		//}
		//_dx = dx[frontD][mDirection];
		//_dy = dy[frontD][mDirection];

		//map[frontX + _dx][frontY + _dy] = dir[frontD][mDirection];
	//}
}

int delRail(int mRow, int mCol){
	int cnt = 0;
	int curX, curY, curD;

	curX = mRow; curY = mCol;
	while (curX >= 0 && curX <= n * 2 &&
		   curY >= 0 && curY <= n * 2 &&
		   map[curX][curY] != -1) {

		curD = map[curX][curY];
		map[curX][curY] = -1;
		cnt++;
		curX = curX + dx[curD][1];
		curY = curY + dy[curD][1];
	}

	return cnt;
}
