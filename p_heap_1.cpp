#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
	int answer = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < scoville.size(); i++)
		pq.push(scoville[i]);

	while (pq.top() < K) {
		if (pq.size() == 1)
			return -1;
		answer++;
		int a = pq.top();
		pq.pop();
		a += pq.top()*2;
		pq.pop();
		pq.push(a);
	}

	return answer;
}
