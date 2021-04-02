/*
숨바꼭질 2
수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고, 동생은 점 K(0 ≤ K ≤ 100,000)에 있다.
수빈이는 걷거나 순간이동을 할 수 있다.
만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다.
순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.
수빈이와 동생의 위치가 주어졌을 때, 수빈이가 동생을 찾는 가장 빠른 시간이 몇 초 후인지 그리고,
가장 빠른 시간으로 찾는 방법이 몇 가지 인지 구하는 프로그램을 작성하시오.

첫 번째 줄에 수빈이가 있는 위치 N과 동생이 있는 위치 K가 주어진다. N과 K는 정수이다.

첫째 줄에 수빈이가 동생을 찾는 가장 빠른 시간을 출력한다.
둘째 줄에는 가장 빠른 시간으로 수빈이가 동생을 찾는 방법의 수를 출력한다.
(동생이 뒤에 있을 수도 있음)
*/
#include<iostream>
#include<queue>
using namespace std;

bool visited[200000];

int main() {
	int n, k, min{ 100000 }, count{ 0 };
	cin >> n >> k;
	if (n == k) {
		cout << 0 << "\n" << 1;
		return 0;
	}
	else if (n > k) {
		cout << n - k << "\n" << 1;
		return 0;
	}

	queue<pair<int, int>> q;
	q.push({ n, 0 });
//	visited[n] = true;
	while (!q.empty()) {
		int cur = q.front().first;
		int times = q.front().second;
		q.pop();
		visited[cur] = true; //시간이 같은 것들을 다 체크해야 하므로 뺄 때 방문표시!!
		if (cur + 1 == k || cur - 1 == k || cur * 2 == k) {
			if (times == min)  //최소 시간인 경우
				count++;
			else if (times < min) {  //최소 시간 갱신
				count = 1;
				min = times;
			}
			continue;
		}
		if (cur < k && visited[cur + 1] == false) {
			if (times < min)
				q.push({ cur + 1,times + 1 });
		}
		if (cur > 0 && visited[cur - 1] == false) {
			if (times < min)
				q.push({ cur - 1, times + 1 });
		}
		if (cur < k && visited[cur * 2] == false) {
			if (times < min)
				q.push({ cur * 2, times + 1 });
		}
	}
	cout << min + 1 << "\n" << count;
}
