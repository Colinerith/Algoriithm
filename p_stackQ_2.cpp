// pq 대신 algorithm의 max_element 함수를 쓰는 방법도 있음.
// int max = *max_element(priorities.begin(), priorities.end());

#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
	int answer = 1;
	int number = priorities[location];
	priority_queue<int> pq;
	vector<pair<int, int>> v;

	for (int i = 0; i < priorities.size(); i++) {
		v.push_back({i, priorities[i]});
		pq.push(priorities[i]);
	}

	int idx = 0;
	while (!pq.empty()) {
		if (v[idx].second == pq.top()) {
			if (v[idx].second == number && v[idx].first == location)
				return answer;
			pq.pop();
			answer++;
		}
		else v.push_back({ v[idx].first, v[idx].second });
		idx++;
	}
}

int main() {
	solution({ 1, 1, 9, 1, 1, 1 }, 0);
}
