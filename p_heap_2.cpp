#include <string>
#include <vector>
#include <queue>
#include<iostream>

using namespace std;

struct comp1 { // 도착시각 순
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.first == b.first)
			return a.second > b.second;
		return a.first > b.first;
	}
};

struct comp2 { // 소요시간 순
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.second == b.second)
			return a.first > b.first;
		return a.second > b.second;
	}
};

int solution(vector<vector<int>> jobs) {
	int answer = 0;
	int cur = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp1> pq1;
	for (int i = 0; i < jobs.size(); i++) {
		pq1.push({ jobs[i][0], jobs[i][1] });
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp2> pq2;
	while (true) {
		while (!pq1.empty() && pq1.top().first <= cur) { // 현재 시점에 가능한 것들 넣기
			pq2.push(pq1.top());
			pq1.pop();
		}

		if (pq2.empty()) { // 가능한 게 없으면
			if (pq1.empty()) { // 전부 계산했으면
				break;
			}
			// 시간만 증가
			cur++;
		}
		else {
			answer += pq2.top().second + (cur - pq2.top().first);
			cur += pq2.top().second; // 현재 시각 업데이트
			pq2.pop();
		}
	}
	return answer / jobs.size();
}

int main() {
	vector<vector<int>> jobs = { {0, 3},{1, 9},{2, 6}};
	cout << solution(jobs);
}
