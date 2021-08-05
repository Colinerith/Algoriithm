#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define MAX_NUM 400000
using namespace std;

int T, n;
int minSize;
int maxSize;

long long int minHeap[MAX_NUM];
long long int maxHeap[MAX_NUM];

void init(){
	minSize = 0;
	maxSize = 0;
}

void addMin(long long int num){
	if (minSize == 0) {
		minHeap[0] = num;
		minSize = 1;
		return;
	}
	int cur = minSize;
	minHeap[minSize++] = num;
	while (cur > 0 && minHeap[(cur - 1) / 2] > num) {
		minHeap[cur] = minHeap[(cur - 1) / 2];
		minHeap[(cur - 1) / 2] = num;
		cur = (cur - 1) / 2;
	}
}
void addMax(long long int num) {
	if (maxSize == 0) {
		maxHeap[0] = num;
		maxSize = 1;
		return;
	}
	int cur = maxSize;
	maxHeap[maxSize++] = num;
	while (cur > 0 && maxHeap[(cur - 1) / 2] < num) {
		maxHeap[cur] = maxHeap[(cur - 1) / 2];
		maxHeap[(cur - 1) / 2] = num;
		cur = (cur - 1) / 2;
	}
}

int popMax() {
	int topNum = maxHeap[0];
	if (maxSize == 1) {
		maxHeap[0] = 0;
		maxSize = 0;
		return topNum;
	}
	maxHeap[0] = maxHeap[maxSize - 1];
	maxSize--;
	int cur = 0;
	while ((cur * 2 + 1) < maxSize) {
		int next;
		if ((cur * 2 + 1) == maxSize - 1) next = cur * 2 + 1;
		else next = (maxHeap[cur * 2 + 1] > maxHeap[cur * 2 + 2]) ? cur * 2 + 1 : cur * 2 + 2;
		if (maxHeap[cur] > maxHeap[next])
			break;
		int temp = maxHeap[cur];
		maxHeap[cur] = maxHeap[next];
		maxHeap[next] = temp;
		cur = next;
	}
	return topNum;
}

int popMin() {
	int topNum = minHeap[0];
	if (minSize == 1) {
		minHeap[0] = 0;
		minSize = 0;
		return topNum;
	}
	minHeap[0] = minHeap[minSize - 1];
	minSize--;
	int cur = 0;
	while ((cur * 2 + 1) < minSize) {
		int next;
		if ((cur * 2 + 1) == minSize - 1) next = cur * 2 + 1;
		else next = (minHeap[cur * 2 + 1] < minHeap[cur * 2 + 2]) ? cur * 2 + 1 : cur * 2 + 2;
		if (minHeap[cur] < minHeap[next])
			break;
		int temp = minHeap[cur];
		minHeap[cur] = minHeap[next];
		minHeap[next] = temp;
		cur = next;
	}
	return topNum;
}

int main(int argc, char** argv) {
	scanf("%d", &T);
	for (register int test_case = 1; test_case <= T; ++test_case) {
		init();
		scanf("%d", &n);
		int firstNum;
		scanf("%d", &firstNum);

		int mid = firstNum;
		long long int sum = 0;
		long long int a, b;
		for(int i=1;i <= n;i++){
			scanf("%lld %lld", &a, &b);
			a < mid ? addMax(a) : addMin(a);
			b < mid ? addMax(b) : addMin(b);

			if (maxSize > minSize) { // ex) [1, 3], '5'
				addMin(mid); // [1, 3], ['5']
				mid = maxHeap[0]; // [1, '3'], [5]
				popMax(); // [1], '3', [5]
			}
			else if (maxSize < minSize){ // ex) '5', [6, 7]
				addMax(mid); // ['5'], [6, 7]
				mid = minHeap[0]; // [5], ['6', 7]
				popMin(); // [5], '6', [7]
			}
			sum += (mid % 20171109);
		}
		printf("#%d %d\n", test_case, sum % 20171109);
	}
	return 0;
}
