// 수 만들기
// 나머지 빼기 -> 나누기 -> 더할 거 빼기
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
using namespace std;

int T, test_case, n, k;
int A[10];
int nodeCnt;
struct Node {
	int num;
	int sumCnt;
	Node* alloc(int n, int c) {
		num = n;
		sumCnt = c;
		return this;
	}
} nodes[1000000];

struct comp {
	bool operator()(Node* a, Node* b) {
		if (a->sumCnt == b->sumCnt)
			return a->num > b->num;
		return a->sumCnt > b->sumCnt;
	}
};

int main(int argc, char** argv) {
	//ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
		}
		scanf("%d", &k);
		nodeCnt = 0;
		int cnt = 0;

		int num; // 몫
		int sumCnt; // 더한 횟수
		priority_queue<Node*, vector<Node*>, comp> q;
		q.push(nodes[nodeCnt++].alloc(k, 0));
		bool flag = true;
		while (flag) {
			//Node* topNode = q.top();
			num = q.top()->num;
			sumCnt = q.top()->sumCnt;
			q.pop();
			for (int i = 0; i < n; i++) {
				if (num == 0) {
					cnt = sumCnt;
					flag = false;
					break;
				}
				if (num == 1) {
					cnt = sumCnt + 1;
					flag = false;
					break;
				}

				int remainder = num % A[i];
				if ((remainder) == 0) {
					q.push(nodes[nodeCnt++].alloc(num / A[i], sumCnt));
				}
				else {
					q.push(nodes[nodeCnt++].alloc((num - remainder) / A[i], sumCnt + remainder));
				}
			}
		}
		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}

// ex)
// k=16, A= [3]일 때
// 1 + 3*5, sumCnt는 1
// 1 + 3*(1+1+3*1), sumCnt는 3
// num==1이므로 sumCnt는 4
