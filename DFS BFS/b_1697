//숨바꼭질
/*
수빈이는 동생과 숨바꼭질을 하고 있다. 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고,
동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 수빈이는 걷거나 순간이동을 할 수 있다.
만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다.
순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.

수빈이와 동생의 위치가 주어졌을 때,
수빈이가 동생을 찾을 수 있는 가장 빠른 시간이 몇 초 후인
*/
#include<iostream>
#include<queue>
using namespace std;
int n, k;

int visited[200001];

void bfs() {
	if (n == k) {
		cout << 0 << endl;
		return;
	}
	queue<int> q;
	q.push(n);
	visited[n] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if ((cur + 1) == k || (cur - 1) == k || (cur * 2) == k) {
			cout << visited[cur] << endl;
			return;
		}
		if ((cur + 1) <200000 && visited[cur + 1] == 0) {
			q.push(cur + 1);
			visited[cur + 1] = visited[cur] + 1;
		}
		if ((cur + 1) >= 0 && visited[cur - 1] == 0) {
			q.push(cur - 1);
			visited[cur - 1] = visited[cur] + 1;
		}
		if ((cur * 2) < 200000 && visited[cur * 2] == 0) {
			q.push(cur * 2);
			visited[cur * 2] = visited[cur] + 1;
		}
	}
}

int main() {
	cin >> n >> k;
	bfs();
	return 0;
}
