//숨바꼭질
/*
수빈이는 동생과 숨바꼭질을 하고 있다. 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고,
동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 수빈이는 걷거나 순간이동을 할 수 있다.
만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다.
순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.

첫째 줄에 수빈이가 동생을 찾는 가장 빠른 시간을 출력한다.
둘째 줄에 어떻게 이동해야 하는지 공백으로 구분해 출력한다.
*/
/*
답은 맞았지만, else if (n>k)~ 코드를 넣기 전까진 시간초과 떴음.
큐를 매번 가지고 다니면서 temp2에 복사했다가 다시 넣고 하는 과정이 너무 부담이 큼.
vector를 하나 더 만들어서 그 전의 기록을 내 위치 인덱스의 값으로 저장하는 방법을 쓰면 됨.
ex) 5->10->9->18->17이면, 10에 들어갈 때 v[10]=5, 9에 들어갈 때 v[9]=10,..
그러면 마지막 v[17]=18이므로, 출력할 때 17에서 시작해서 값을 출력하고, 18로 들어가서
v[18]값을 출력하고, v[9]에서 10을 출력하고,.. 반복하면 된다.
여기선 거꾸로 출력되기 때문에 아예 k에서 시작하는 사람도 있고, 출력값을 다시 저장해서
원래 순서대로 출력하는 사람도 있다.
*/
#include<iostream>
#include<queue>
using namespace std;
int n, k;
int visited[200001];

int main() {
	cin >> n >> k;
	if (n == k) {
		cout << 0 << "\n" << k;
		return 0;
	}
	else if (n * 2 == k) {
		cout << 1 << "\n" << n << " " << k;
		return 0;
	}
	else if (n > k) {
		cout << n - k << "\n";
		int j = n;
		for (int i = 0; i <= (n - k); i++) {
			cout << j-- << " ";
		}
		return 0;
	}
	queue<pair<int, queue<int>>> q;
	queue<int> temp;
	temp.push(n);
	q.push({ n, temp });
	visited[n] = 1;
	while (!q.empty()) {
		int cur = q.front().first;
		temp = q.front().second;
		q.pop();
		if ((cur + 1) == k || (cur - 1) == k || (cur * 2) == k) {
			cout << visited[cur] << endl;
			for (int i = 0; i < visited[cur]; i++) {
				cout << temp.front() << " ";
				temp.pop();
			}
			cout << k;
			return 0;
		}
		if (cur < k && visited[cur + 1] == 0) {
			queue<int> temp2 = temp;
			temp2.push(cur + 1);
			q.push({ cur + 1, temp2 });
			visited[cur + 1] = visited[cur] + 1;
		}
		if (cur > 0 && visited[cur - 1] == 0) {
			queue<int> temp2 = temp;
			temp2.push(cur - 1);
			q.push({ cur - 1, temp2 });
			visited[cur - 1] = visited[cur] + 1;
		}
		if (cur < k && visited[cur * 2] == 0) {
			queue<int> temp2 = temp;
			temp2.push(cur * 2);
			q.push({ cur * 2, temp2 });
			visited[cur * 2] = visited[cur] + 1;
		}
	}
	return 0;
}
