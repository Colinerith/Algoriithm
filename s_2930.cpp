#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define MAX_NUM 100000
using namespace std;

int T, n, a;
int heapSize;

int heap[MAX_NUM];

void init(){
	heapSize = 0;
	for (register int i = 0; i < MAX_NUM; i++) {
		heap[i] = 0;
	}
}

void addUser(int num){
	if (heapSize == 0) {
		heap[0] = num;
		heapSize = 1;
		return;
	}
	int cur = heapSize;
	heap[heapSize++] = num;
	while (cur > 0 && heap[(cur - 1) / 2] < num) {
		// 부모와 교환
		heap[cur] = heap[(cur - 1) / 2];
		heap[(cur - 1) / 2] = num;

		cur = (cur - 1) / 2;
	}
}

int popRoot() {
	int topNum = heap[0];

	if (heapSize == 0) {
		return -1;
	}
	if (heapSize == 1) {
		heap[0] = 0;
		heapSize = 0;
		return topNum;
	}

	heap[0] = heap[heapSize - 1];
	heapSize--;
	int cur = 0;
	while ((cur * 2 + 1) < heapSize) {
		int next;
		//왼쪽 자식만 있는 경우
		if ((cur * 2 + 1) == heapSize - 1)
			next = cur * 2 + 1;
		//둘다 있는 경우
		else 
			next = (heap[cur * 2 + 1] > heap[cur * 2 + 2]) ? cur * 2 + 1 : cur * 2 + 2;

		if (heap[cur] > heap[next])
			break;

		// 자식과 교환
		int temp = heap[cur];
		heap[cur] = heap[next];
		heap[next] = temp;

		cur = next;
	}
	return topNum;
}

int main(int argc, char** argv) {
	//ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	scanf("%d", &T);
	for (register int test_case = 1; test_case <= T; ++test_case) {
		init();
		scanf("%d", &n);
		printf("#%d", test_case);
		while (n--) {
			scanf("%d", &a);
			if (a == 1) {
				scanf("%d", &a);
				addUser(a);
			}
			else {
				printf(" %d", popRoot());
			}
		}
		printf("\n");
	}
	return 0;
}
