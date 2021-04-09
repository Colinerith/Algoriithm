/*
https://www.acmicpc.net/problem/13913
더 괜찮은 방법으로 다시 푼다.
*/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int n, k;
int visited[200001];
vector<int> v(200001);
vector<int> stack;

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
	queue<int> q;
	q.push(n);
	visited[n] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (cur == k) {
			cout << visited[cur] - 1 << "\n"; // visited[n]=1로 시작하므로 1 뺌
			int temp = v[k];
			cout << n << " ";
			while (temp != n) {
				stack.push_back(temp);
				temp = v[temp];
			}
			while (!stack.empty()) {
				cout << stack.back() << " ";
				stack.pop_back();
			}
			cout << k;
			return 0;
		}
		if (cur < k && cur * 2 <= 200000 && visited[cur * 2] == 0) {
			q.push(cur * 2);
			visited[cur * 2] = visited[cur] + 1;
			v[cur * 2] = cur;
		}
		if (cur < k && visited[cur + 1] == 0) {
			q.push(cur + 1);
			visited[cur + 1] = visited[cur] + 1;
			v[cur + 1] = cur;
		}
		if (cur > 0 && visited[cur - 1] == 0) {
			q.push(cur - 1);
			visited[cur - 1] = visited[cur] + 1;
			v[cur - 1] = cur;
		}
	}
	return 0;
}
