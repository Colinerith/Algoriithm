/*
0과 1로만 이루어져 있어야 한다.
1이 적어도 하나 있어야 한다.
수의 길이가 100 이하이다.
수가 0으로 시작하지 않는다.
자연수 N이 주어졌을 때, N의 배수 중에서 구사과가 좋아하는 수를 구하는.

첫째 줄에 테스트 케이스의 개수 T(T < 1,000)가 주어진다.

둘째 줄부터 T개의 줄에는 자연수 N이 한 줄에 하나씩 주어진다.
N은 20,000보다 작거나 같은 자연수이다.
각각의 테스트 케이스마다 N의 배수이면서, 구사과가 좋아하는 수를 아무거나 출력한다.
만약, 그러한 수가 없다면 BRAK을 출력한다.
*/

//혼자 힘으로 다시 풀어보기 !!!

#include<iostream>
#include<queue>
#include<string>
using namespace std;

bool visited[20000];
void calc(int n) {
	queue<pair<int, string>> q;
	q.push({ 1, "1" });

	while (!q.empty()) {
		int x = q.front().first;
		string s = q.front().second;
		if (x == 0) {
			cout << s << "\n";
		}
		q.pop();
		if (visited[(x * 10) % n] == 0) {
			q.push({ (x * 10) % n, s + "0"});
			visited[(x * 10) % n] = 1;
		}
		if (visited[(x * 10 + 1) % n] == 0) {
			q.push({ (x * 10 + 1) % n, s + "1" });
			visited[(x * 10 + 1) % n] = 1;
		}
	}
}

int main() {
	int t, n;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 20000; i++)
			visited[i] = 0;

		cin >> n;
		calc(n);
	}
}
