// 연결 리스트: 9% 시간초과
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int>> stations(100001); // line 정보를 저장

class Node {
public:
	int st;
	int cnt;
	Node* next;

	Node() {
		st = 0;
		cnt = 0;
		next = nullptr;
	}
	Node(int i) {
		st = i;
		cnt = 0;
		next = nullptr;
	}
	void insert(int i) {
		if (next == nullptr) {
			cnt = 1;
			next = new Node(i);
		}
		else {
			Node* cur = next;
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			cur->next = new Node(i);
			cnt++;
		}
	}
};
Node lines[100001];
//vector<Node> lines(100001);
bool visited[100001];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, l, a;
	cin >> n >> l;
	for (int i = 1; i <= n; i++) {
		lines[i].st = i;
		lines[i].cnt = 0;
		lines[i].next = nullptr;
	}
	for (int i = 1; i <= l;) {
		cin >> a;
		if (a == -1) {
			i++;
			continue;
		}
		stations[a].push_back(i);
		if (stations[a].size() > 1) {
			for (int k = 0; k < stations[a].size() - 1; k++) {
				lines[stations[a][k]].insert(i);
				lines[i].insert(stations[a][k]);
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
		Node* cur = lines[num].next;
		while (cur != nullptr) {
			if (visited[cur->st] == false) {
				q.push({ level + 1, cur->st });
				visited[cur->st] = true;
			}
			cur = cur->next;
		}
	}
	if (fail) cout << -1;
	else cout << level;

	stations.clear();
	//lines.clear();
	destLine.clear();
}
