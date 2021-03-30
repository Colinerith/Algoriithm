/*
정수 A를 B로 바꾸려고 한다. 가능한 연산은 다음과 같은 두 가지이다.

2를 곱한다.
1을 수의 가장 오른쪽에 추가한다. 
A를 B로 바꾸는데 필요한 연산의 최솟값을 구해보자.

입력
첫째 줄에 A, B (1 ≤ A < B ≤ 109)가 주어진다.

출력
A를 B로 바꾸는데 필요한 연산의 최솟값에 1을 더한 값을 출력한다. 만들 수 없는 경우에는 -1을 출력한다.
*/

#include<iostream>
#include<queue>
using namespace std;

//int graph[1000000000]; //범위가..

void bfs(int a, int b) {
	queue<pair<int, int>> q;

	q.push({ b, 1 });
	while (!q.empty()) {
		int cur = q.front().first;
		int n = q.front().second;
		q.pop();
		//2로 나눠지면 나누기
		if (cur % 2 == 0) {
			if (cur / 2 == a) {
				cout << n + 1;
				return;
			}
			else if (cur / 2 > a)
				q.push({ cur / 2, n + 1 });
		}
		if (cur % 10 == 1) {
			if (cur / 10 == a) {
				cout << n + 1;
				return;
			}
			else if (cur / 10 > a)
				q.push({ cur / 10, n + 1 });
		}
	}
	cout << -1;
}

int main() {
	int a, b;
	cin >> a >> b;
	bfs(a, b);
}
