// 45% 메모리 초과
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int>> stations(100001); // line 정보를 저장
vector<vector<int>> lines(100001);
bool visited[100001];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, l, a;
	cin >> n >> l;
	for (int i = 1; i <= l;) {
		cin >> a;
		if (a == -1) {
			i++;
			continue;
		}
		stations[a].push_back(i);
		if (stations[a].size() > 1) {
			for (int k = 0; k < stations[a].size() - 1; k++) {
				lines[stations[a][k]].push_back(i);
				lines[i].push_back(stations[a][k]);
			}
		}
	}
	int source, dest;
	cin >> source >> dest;
	queue<pair<int, int>> q;
	for (int i : stations[source]) {
		q.push({ 0,i });
		visited[i] = true;
	}
	vector<int> destLine = stations[dest];
	sort(destLine.begin(), destLine.end());
	int level = 0;
	bool fail = true;
	bool flag = false;

	while (!q.empty()) {
		int num = q.front().second;
		level = q.front().first;
		if (binary_search(destLine.begin(), destLine.end(), num)) {
			fail = false;
			flag = true;
			break;
		}
		if (flag) break;

		q.pop();
		for (int i : lines[num]) {
			if (visited[i] == false) {
				q.push({ level + 1, i });
				visited[i] = true;
			}
		}
	}
	if (fail) cout << -1;
	else cout << level;
}
