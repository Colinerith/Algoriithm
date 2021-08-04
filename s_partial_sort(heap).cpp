#define MAX_NUM 100000

int heapSize;
int incomeTemp[10];

struct Node {
	int uid;
	int inc;
} heap[MAX_NUM];

void init(){
	heapSize = 0;
	for (register int i = 0; i < MAX_NUM; i++) {
		heap[i].uid = 0;
		heap[i].inc = 0;
	}
}

/*
uID : User ID, 0부터 시작하여 순차적으로 증가한다 (0 <= uID < 100000)
income : User의 수입, 클수록 우선순위가 높다
(만약, 수입이 동일한 경우 uID가 작은 User의 우선순위가 높다)
*/
void addUser(int uid, int income){
	if (heapSize == 0) {
		heap[0].uid = uid;
		heap[0].inc = income;
		heapSize = 1;
		return;
	}
	int cur = heapSize;
	heap[heapSize].uid = uid;
	heap[heapSize++].inc = income;
	while (cur > 0 && heap[(cur - 1) / 2].inc <= income) {
		if ((heap[(cur - 1) / 2].inc == income) && heap[(cur - 1) / 2].uid < uid) {
			// 수입이 동일하지만 부모의 uid가 더 작을 경우
			break;
		}
		// 부모와 교환
		heap[cur].uid = heap[(cur - 1) / 2].uid;
		heap[cur].inc = heap[(cur - 1) / 2].inc;
		heap[(cur - 1) / 2].uid = uid;
		heap[(cur - 1) / 2].inc = income;

		cur = (cur - 1) / 2;
	}
}

Node popUser() {
	Node topUser = heap[0];

	if (heapSize == 1) {
		heap[0].uid = 0;
		heap[0].inc = 0;
		heapSize = 0;
		return topUser;
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
		else {
			if (heap[cur * 2 + 1].inc == heap[cur * 2 + 2].inc)
				next = (heap[cur * 2 + 1].uid < heap[cur * 2 + 2].uid) ? cur * 2 + 1 : cur * 2 + 2;
			else
				next = (heap[cur * 2 + 1].inc > heap[cur * 2 + 2].inc) ? cur * 2 + 1 : cur * 2 + 2;
		}

		if (((heap[cur].inc == heap[next].inc) && heap[cur].uid < heap[next].uid)
			|| (heap[cur].inc > heap[next].inc))
			break;

		// 자식과 교환
		int tempUid = heap[cur].uid;
		int tempIncome = heap[cur].inc;
		heap[cur].uid = heap[next].uid;
		heap[cur].inc = heap[next].inc;
		heap[next].uid = tempUid;
		heap[next].inc = tempIncome;

		cur = next;
	}
	return topUser;
}

/*
result[] : income이 큰 순서대로 10개의 uID를 구한다.(내림차순)
result 개수를 반환한다 (1 <= result 개수 <= 10)
*/
int getTop10(int result[10]){
	int resultNum = 0;
	resultNum = (heapSize < 10) ? heapSize : 10;

	for (int i = 0; i < resultNum; i++) {
		Node topUser = popUser();
		result[i] = topUser.uid;
		incomeTemp[i] = topUser.inc;
	}

	for (int i = 0; i < resultNum; i++) {
		addUser(result[i], incomeTemp[i]);
	}
	return resultNum;
}
