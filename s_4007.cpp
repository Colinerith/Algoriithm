// 7.21 #4
#include <iostream>
#include <queue>
#define MAX_ROOM 50001
#define MAX_ROAD 1000000
using namespace std;

struct Road {
	int roomNum; //도착지
	int weight; //소요시간
	Road* next;
	Road* alloc(int r, int w) {
		roomNum = r;
		weight = w;
		next = nullptr;
		return this;
	}
};

struct comp { // 거리 기준 정렬
	bool operator()(Road a, Road b) {
		return a.weight > b.weight;
	}
};

Road* rooms[MAX_ROOM]; // 각 방과 연결된 길 리스트의 head
Road* reversedRooms[MAX_ROOM];
Road roads[MAX_ROAD]; // 꺼내서 쓰도록
int distances[MAX_ROOM]; // 최단거리 저장
int reversedDistances[MAX_ROOM];
int roadCnt;
int n, m, x, s, e, t;

void init() {
	roadCnt = 0;
	for (int i = 0; i <= n; i++) {
		rooms[i] = nullptr; // head
		reversedRooms[i] = nullptr; // head
	}
}

void addRoad(int start, int end, int time) {
	Road* cur = rooms[start];
	if (cur == NULL) {
		rooms[start] = roads[roadCnt++].alloc(end, time);
	}
	else {
		//head에 넣자
		Road* newNode = roads[roadCnt++].alloc(end, time);
		newNode->next = cur;
		rooms[start] = newNode;
	}

	cur = reversedRooms[end];
	if (cur == NULL) {
		reversedRooms[end] = roads[roadCnt++].alloc(start, time);
	}
	else {
		Road* newNode = roads[roadCnt++].alloc(start, time);
		newNode->next = cur;
		reversedRooms[end] = newNode;
	}
}

priority_queue<Road, vector<Road>, comp> fringeQ;

void minDist(int source) {
	for (int i = 1; i <= n; i++)
		distances[i] = 1000000;

	fringeQ.push({ source, 0 });
	distances[source] = 0;

	while (!fringeQ.empty()) {
		Road curRoad = fringeQ.top();
		int curRoom = curRoad.roomNum;
		int time = curRoad.weight;
		fringeQ.pop();

		if (distances[curRoom] < time)
			continue;

		Road* cur = rooms[curRoom];
		int nextRoom, nextTime;
		while (cur != nullptr) {
			nextRoom = cur->roomNum;
			nextTime = time + cur->weight;
			if (nextTime < distances[nextRoom]) {
				fringeQ.push({ nextRoom, nextTime });
				distances[nextRoom] = nextTime;
			}
			cur = cur->next;
		}
	}
}

void reverse(int source) {
	for (int i = 1; i <= n; i++) // 배열 초기화
		reversedDistances[i] = 1000000;

	fringeQ.push({ source, 0 });
	reversedDistances[source] = 0;

	while (!fringeQ.empty()) {
		Road curRoad = fringeQ.top();
		int curRoom = curRoad.roomNum;
		int time = curRoad.weight;
		fringeQ.pop();

		if (reversedDistances[curRoom] < time)
			continue;
		Road* cur = reversedRooms[curRoom];
		int nextRoom, nextTime;
		while (cur != nullptr) {
			nextRoom = cur->roomNum;
			nextTime = time + cur->weight;
			if (nextTime < reversedDistances[nextRoom]) {
				fringeQ.push({ nextRoom, nextTime });
				reversedDistances[nextRoom] = nextTime;
			}
			cur = cur->next;
		}
	}
}


int test_case;
int T;
int main(int argc, char** argv) {
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d %d %d", &n, &m, &x);
		if (test_case != 1)
			init();

		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &s, &e, &t);
			addRoad(s, e, t);
		}
		int max = 0;
		int time;
		minDist(x);
		reverse(x);
		for (int i = 1; i <= n; i++) {
			time = distances[i] + reversedDistances[i];
			if (time > max)
				max = time;
		}
		printf("#%d %d\n", test_case, max);
	}
	return 0;
}
